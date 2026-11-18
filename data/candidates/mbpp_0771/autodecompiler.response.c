int func0(char *s) {
 int len = strlen(s);
 if (len % 2 != 0) {
  return 0;
 }

 char stack[100];
 int top = -1;

 int i;
 char c, last_open;
 for (i = 0; i < len; i++) {
  c = s[i];

  if (c == '(' || c == '{' || c == '[') {
   stack[++top] = c;
  } else if (c == ')' || c == '}' || c == ']') {
   if (top == -1) {
    return 0;
   }
   last_open = stack[top--];
   if (!(last_open == '(' && c == ')' ||
         last_open == '{' && c == '}' ||
         last_open == '[' && c == ']')) {
    return 0;
   }
  }
 }

 return top == -1;
}