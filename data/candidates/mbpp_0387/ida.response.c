char *__cdecl func0(const char *N)
{
  int l; // [rsp+Ch] [rbp-14h]

  l = strlen(N);
  if ( N[l - 1] == 48
    || N[l - 1] == 50
    || N[l - 1] == 52
    || N[l - 1] == 54
    || N[l - 1] == 56
    || N[l - 1] == 65
    || N[l - 1] == 67
    || N[l - 1] == 69 )
  {
    return "Even";
  }
  else
  {
    return "Odd";
  }
}