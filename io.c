
#include <errno.h>
#include <unistd.h>
#include "io.h"


/* Reads next char from stdin. If no more characters, it returns EOF */
int read_char() {

  char c;
  ssize_t readResult = read(STDIN_FILENO, &c, 1);

  if(readResult== 1) {
    return c;
  } else if(readResult == 0) {
    return EOF;
  }
  return EOF;
}


/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int write_char(char c) {
  ssize_t readResult = write(STDOUT_FILENO, &c, 1);
  if (readResult ==1) {
    return 0;
  }
  return EOF;
}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0, otherwise EOF */
int write_string(char* s) {
  ssize_t length = 0;


  while (s[length] != '\0') {
    length++;
  }

  ssize_t writeResult = write(STDOUT_FILENO, s, length);
  if(writeResult == length) {
    return 0;
  }
  return EOF;
}

/* Writes n to stdout (without any formatting).
 * If no errors occur, it returns 0, otherwise EOF
 */
int write_int(int n) {
  char buffer[10];
  ssize_t length = 0;

  if(n == 0) {
    buffer[length++] = '0';
  }
  else {
    int temp = n;
    int isNegative = (temp < 0) ? 1 : 0;

    if(isNegative) {
      buffer[length++] = '-';
      temp = -temp;
    }
    int numberLength = 0;
    char tempBuffer[10];

    while (temp > 0) {
      tempBuffer[numberLength++] = (temp % 10) + '0';
      temp /= 10;
    }

    for (int i = numberLength - 1; i >= 0; i--) {
      buffer[length++] = tempBuffer[i];
    }
  }
  ssize_t writeResult = write(STDOUT_FILENO, buffer, length);
  if(writeResult == length) {
    return 0;
  }
  return EOF;
}

