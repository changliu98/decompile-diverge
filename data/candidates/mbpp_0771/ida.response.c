bool __cdecl func0(const char *exp)
{
  int v1; // eax
  char last_open; // [rsp+6h] [rbp-8Ah]
  char ch_0; // [rsp+7h] [rbp-89h]
  int i; // [rsp+8h] [rbp-88h]
  int top; // [rsp+Ch] [rbp-84h]
  char stack[100]; // [rsp+10h] [rbp-80h]
  int len; // [rsp+7Ch] [rbp-14h]
  const char *expa; // [rsp+80h] [rbp-10h]

  expa = exp;
  len = strlen(exp);
  if ( len % 2 )
  {
    return 0;
  }
  else
  {
    top = -1;
    for ( i = 0; i < len; ++i )
    {
      ch_0 = expa[i];
      if ( ch_0 == 40 || ch_0 == 123 || ch_0 == 91 )
      {
        stack[++top] = ch_0;
      }
      else if ( ch_0 == 41 || ch_0 == 125 || ch_0 == 93 )
      {
        if ( top == -1 )
          return 0;
        v1 = top--;
        last_open = stack[v1];
        if ( last_open == 40 && ch_0 != 41 )
          return 0;
        if ( last_open == 123 && ch_0 != 125 || last_open == 91 && ch_0 != 93 )
          return 0;
      }
    }
    return top == -1;
  }
}