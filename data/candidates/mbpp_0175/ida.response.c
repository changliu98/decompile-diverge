bool __cdecl func0(char *str1)
{
  int v1; // eax
  char popped; // [rsp+16h] [rbp-8Ah]
  char parenthese; // [rsp+17h] [rbp-89h]
  int i; // [rsp+18h] [rbp-88h]
  int top; // [rsp+1Ch] [rbp-84h]
  char stack[100]; // [rsp+20h] [rbp-80h]
  char *str1a; // [rsp+90h] [rbp-10h]

  str1a = str1;
  top = -1;
  for ( i = 0; i < strlen(str1a); ++i )
  {
    parenthese = str1a[i];
    if ( parenthese == 40 || parenthese == 123 || parenthese == 91 )
    {
      stack[++top] = parenthese;
    }
    else
    {
      if ( top == -1 )
        return 0;
      v1 = top--;
      popped = stack[v1];
      if ( parenthese == 41 && popped != 40 || parenthese == 125 && popped != 123 || parenthese == 93 && popped != 91 )
        return 0;
    }
  }
  return top == -1;
}