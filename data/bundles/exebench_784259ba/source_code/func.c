
int
inet_close(int *sk)
{
 close(*sk);
 return (*sk = 0);
}
