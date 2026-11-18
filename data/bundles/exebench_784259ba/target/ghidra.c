int inet_close(int *sk)

{
  int *sk_local;
  
  close(*sk);
  *sk = 0;
  return 0;
}