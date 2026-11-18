bool __cdecl func0(int x)
{
  int v1; // eax
  int v2; // eax
  int j; // [rsp+0h] [rbp-1C0h]
  int i; // [rsp+4h] [rbp-1BCh]
  int next_term; // [rsp+8h] [rbp-1B8h]
  int temp_0; // [rsp+Ch] [rbp-1B4h]
  int right; // [rsp+10h] [rbp-1B0h]
  int left; // [rsp+14h] [rbp-1ACh]
  int n; // [rsp+18h] [rbp-1A8h]
  int temp; // [rsp+1Ch] [rbp-1A4h]
  int terms[100]; // [rsp+20h] [rbp-1A0h]
  int xa; // [rsp+1BCh] [rbp-4h]

  xa = x;
  temp = x;
  n = 0;
  while ( temp > 0 )
  {
    v1 = n++;
    terms[v1] = temp % 10;
    temp /= 10;
  }
  left = 0;
  for ( right = n - 1; left < right; --right )
  {
    temp_0 = terms[left];
    terms[left] = terms[right];
    terms[right] = temp_0;
    ++left;
  }
  next_term = 0;
  i = n;
  while ( next_term < xa )
  {
    next_term = 0;
    for ( j = 1; j <= n; ++j )
      next_term += terms[i - j];
    v2 = i++;
    terms[v2] = next_term;
  }
  return next_term == xa;
}