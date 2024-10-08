#!/bin/bash

# Simple test of the command interpreter

in="abbabaq"
out="Count: 6
Collection: 0,3,5"

[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "Test Case 1: PASSED" || echo "Test Case 1: FAILED"

# Test Case 2
in="abccbaabcqaaaccbba"
out="Count: 9
Collection: 5"
[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "Test Case 2: PASSED" || echo "Test Case 2: FAILED"

# Test Case 3
in="aabcaacalbbbaq"
out="Count: 8
Collection: 0,4,7"
[[ $(./cmd_int <<< "$in") == "$out"* ]] && echo "Test Case 3: PASSED" || echo "Test Case 3: FAILED"


