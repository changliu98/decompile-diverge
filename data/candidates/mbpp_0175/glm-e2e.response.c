#include <string.h>
#include <stdbool.h>

bool func0(const char *s) {
    char stack[100];
    int top = -1;
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top == -1) {
                return false;
            }
            char open = stack[top--];
            if (c == ')' && open != '(') {
                return false;
            }
            if (c == '}' && open != '{') {
                return false;
            }
            if (c == ']' && open != '[') {
                return false;
            }
        }
    }
    return top == -1;
}