_Bool isParenthesisBalanced(char *str)
{
  char *str1 = str;
  char stack[100];
  int top = -1;
  int i;
  for(i = 0; i < strlen(str1); i++)
  {
    char ch = str1[i];
    if(ch == '(' || ch == '{' || ch == '[')
    {
      stack[++top] = ch;
    }
    else
    {
      if(top == -1)
        return 0;
      char popped = stack[top--];
      if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
        return 0;
    }
  }
  if(top == -1)
    return 1;
  return 0;
}
char *str1;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str1); i++)
{
  char ch = str1[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str); i++)
{
  char ch = str[i];
  if(ch == '(' || ch == '{' || ch == '[')
  {
    stack[++top] = ch;
  }
  else
  {
    if(top == -1)
      return 0;
    char popped = stack[top--];
    if((ch == ')' && popped != '(') || (ch == '}' && popped != '{') || (ch == ']' && popped != '['))
      return 0;
  }
}
if(top == -1)
  return 1;
return 0;
}
char *str;
char stack[100];
int top = -1;
int i;
for(i = 0; i < strlen(str);