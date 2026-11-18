void __cdecl reverse(char *li)
{
  char *v1; // rax
  char t; // [rsp+1h] [rbp-19h]
  char *right; // [rsp+2h] [rbp-18h]
  char *righta; // [rsp+2h] [rbp-18h]
  char *left; // [rsp+Ah] [rbp-10h]

  right = li;
  left = li;
  do
    v1 = right++;
  while ( *v1 );
  for ( righta = right - 2; left < righta; --righta )
  {
    t = *left;
    *left = *righta;
    *righta = t;
    ++left;
  }
}