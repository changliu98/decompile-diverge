

#include <stdio.h>

#include <stdbool.h>

#include <assert.h>

#include <string.h>



bool func0(const char *exp) {
  int len = strlen(exp);
  if (len % 2 != 0) {
    return false;
  }
  char stack[100];
  int top = -1;
  for (int i = 0; i < len; i++) {
    char ch = exp[i];
    if (ch == '(' || ch == '{' || ch == '[') {
      stack[++top] = ch;
    } else if (ch == ')' || ch == '}' || ch == ']') {
      if (top == -1) {
        return false;
      }
      char last_open = stack[top--];
      if ((last_open == '(' && ch != ')') ||
          (last_open == '{' && ch != '}') ||
          (last_open == '[' && ch != ']')) {
        return false;
      }
    }
  }
  return top == -1;
}
