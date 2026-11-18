int __cdecl socket_close_(int *sockfd)
{
  int temp; // [rsp+0h] [rbp-10h]

  temp = *sockfd;
  *sockfd = -1;
  return close(temp);
}