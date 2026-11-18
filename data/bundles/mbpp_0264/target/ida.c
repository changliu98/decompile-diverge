double __cdecl func0(int h_age)
{
  if ( h_age < 0 )
    exit(1);
  if ( h_age > 2 )
    return (double)(4 * (h_age - 2) + 21);
  else
    return (double)h_age * 10.5;
}