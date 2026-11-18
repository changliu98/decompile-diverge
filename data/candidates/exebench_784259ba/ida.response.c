int __cdecl inet_close(int *sk)
{
  close(*sk);
  *sk = 0;
  return 0;
}