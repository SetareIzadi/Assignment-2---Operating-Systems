/**
 * @file   mm.c
 * @Author 02335 team
 * @date   September, 2024
 * @brief  Memory management skeleton.
 * 
 */

#include <stdint.h>
#include "mm.h"

/* Proposed data structure elements */

typedef struct header {
  struct header * next;     // Bit 0 is used to indicate free block
  uint64_t user_block[0];   // Standard trick: Empty array to make sure start of user block is aligned
} BlockHeader;

/* Macros to handle the free flag at bit 0 of the next pointer of header pointed at by p */
#define GET_NEXT(p)    (void *) ( ((uintptr_t)(p->next)) & ~((uintptr_t) 0x1) )
#define SET_NEXT(p,n)  p->next = (void *) ( ((uintptr_t)(n) & ~((uintptr_t)0x1)) | ((uintptr_t)(p->next) & 0x1) )
#define GET_FREE(p)    (uint8_t) ( (uintptr_t) (p->next) & 0x1 )
#define SET_FREE(p,f)  p->next = (void *) ( ((uintptr_t)(p->next) & ~((uintptr_t)0x1)) | ((uintptr_t)(f) & 0x1) )
#define SIZE(p)        ( ((uintptr_t)GET_NEXT(p) > (uintptr_t)(p)) ? ((uintptr_t)GET_NEXT(p) - (uintptr_t)(p) - sizeof(BlockHeader)): 0 )
#define MIN_SIZE     (8)   // A block should have at least 8 bytes available for the user

static BlockHeader * first = NULL;
static BlockHeader * current = NULL;

/**
 * @name    simple_init
 * @brief   Initialize the block structure within the available memory
 *
 */
void simple_init() {
  uintptr_t aligned_memory_start = (memory_start + 7) & ~((uintptr_t) 0x7);  /* Alignment */
  uintptr_t aligned_memory_end   = memory_end & ~((uintptr_t) 0x7);           /* Alignment */
  BlockHeader * last;

  /* Already initialized ? */
  if (first == NULL) {
    /* Check that we have room for at least one free block and an end header */
    if (aligned_memory_start + 2*sizeof(BlockHeader) + MIN_SIZE <= aligned_memory_end) {
      /* Place first and last blocks and set links and free flags properly */
      first = (BlockHeader *) aligned_memory_start;
      last = (BlockHeader *) (aligned_memory_end - sizeof(BlockHeader));

      /* Set up first block */
      SET_NEXT(first, last);
      SET_FREE(first, 1); // Free

      /* Set up last (dummy) block */
      last->next = (void *) first;
      SET_FREE(last, 0); // Allocated

      current = first;
    }
  }
}

/**
 * @name    simple_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a pointer to the first byte.
 *
 * This function should behave similar to a normal malloc implementation.
 *
 * @param size_t size Number of bytes to allocate.
 * @retval Pointer to the start of the allocated memory or NULL if not possible.
 *
 */
void* simple_malloc(size_t size) {

  if (first == NULL) {
    simple_init();
    if (first == NULL) return NULL;
  }

  size_t aligned_size = (size + 7) & ~((size_t)0x7);  /* Alignment */

  /* Search for a free block */
  BlockHeader * search_start = current;
  do {

    if (GET_FREE(current)) {

      /* Possibly coalesce consecutive free blocks here */
      // Coalesce current block with subsequent free blocks
      BlockHeader * next_block = GET_NEXT(current);
      while (GET_FREE(next_block) && next_block != first) {
        // Merge current and next_block
        SET_NEXT(current, GET_NEXT(next_block));
        next_block = GET_NEXT(current);
      }

      /* Check if free block is large enough */
      if (SIZE(current) >= aligned_size) {
        /* Will the remainder be large enough for a new block? */
        if (SIZE(current) - aligned_size < sizeof(BlockHeader) + MIN_SIZE) {
          /* Use block as is, marking it non-free */
          SET_FREE(current, 0);
          BlockHeader * allocated_block = current;
          current = GET_NEXT(current);
          return (void *) (allocated_block->user_block);
        } else {
          /* Carve aligned_size from block and allocate new free block for the rest */
          BlockHeader * allocated_block = current;
          uintptr_t allocated_block_addr = (uintptr_t) allocated_block;
          uintptr_t allocated_user_block_addr = allocated_block_addr + sizeof(BlockHeader);
          uintptr_t new_block_addr = allocated_user_block_addr + aligned_size;

          BlockHeader * new_block = (BlockHeader *) new_block_addr;
          /* Ensure new_block is within memory bounds */
          if ((uintptr_t)new_block + sizeof(BlockHeader) > memory_end) {
            /* Cannot split, use block as is */
            SET_FREE(current, 0);
            BlockHeader * allocated_block = current;
            current = GET_NEXT(current);
            return (void *) (allocated_block->user_block);
          }

          /* Set new_block's next pointer to allocated_block's next */
          SET_NEXT(new_block, GET_NEXT(allocated_block));
          SET_FREE(new_block, 1); // Free

          /* Update allocated_block's next pointer to new_block */
          SET_NEXT(allocated_block, new_block);

          /* Mark allocated_block as allocated */
          SET_FREE(allocated_block, 0);

          /* Advance current */
          current = GET_NEXT(allocated_block);

          /* Return pointer to allocated_block's user_block */
          return (void *) allocated_block->user_block;
        }
      }
    }
    current = GET_NEXT(current);
  } while (current != search_start);

 /* None found */
  return NULL;
}

/**
 * @name    simple_free
 * @brief   Frees previously allocated memory and makes it available for subsequent calls to simple_malloc
 *
 * This function should behave similar to a normal free implementation.
 *
 * @param void *ptr Pointer to the memory to free.
 *
 */
void simple_free(void * ptr) {
  BlockHeader * block = (BlockHeader *) ( (uintptr_t) ptr - sizeof(BlockHeader) ); /* Find block corresponding to ptr */
  if (GET_FREE(block)) {
    /* Block is not in use -- probably an error */
    return;
  }
  /* Free block */
  SET_FREE(block, 1);

  /* Possibly coalesce consecutive free blocks here */
  BlockHeader * next_block = GET_NEXT(block);
  while (GET_FREE(next_block) && next_block != first) {
    // Merge block and next_block
    SET_NEXT(block, GET_NEXT(next_block));
    next_block = GET_NEXT(block);
  }

  /* Coalesce with previous block */
  BlockHeader * p = first;
  do {
    if (GET_NEXT(p) == block) {
      if (GET_FREE(p)) {
        // Merge p and block
        SET_NEXT(p, GET_NEXT(block));
      }
      break;
    }
    p = GET_NEXT(p);
  } while (p != first);
}
#include "mm_aux.c"
