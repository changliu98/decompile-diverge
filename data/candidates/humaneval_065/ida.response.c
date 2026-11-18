char *__cdecl func0(int x, int shift)
{
  char temp_0[50]; // [rsp+10h] [rbp-50h] BYREF
  char temp; // [rsp+4Fh] [rbp-11h]
  int i; // [rsp+50h] [rbp-10h]
  int len; // [rsp+54h] [rbp-Ch]
  int shifta; // [rsp+58h] [rbp-8h]
  int xa; // [rsp+5Ch] [rbp-4h]

  xa = x;
  shifta = shift;
  sprintf(func0_xs, "%d", (unsigned int)x);
  len = strlen(func0_xs);
  if ( len >= shift )
  {
    strcpy(temp_0, &func0_xs[len - shifta]);
    temp_0[shifta] = 0;
    strncat(temp_0, func0_xs, len - shifta);
    strcpy(func0_xs, temp_0);
  }
  else
  {
    for ( i = 0; i < len / 2; ++i )
    {
      temp = func0_xs[i];
      func0_xs[i] = func0_xs[len - 1 - i];
      func0_xs[len - 1 - i] = temp;
    }
  }
  return func0_xs;
}