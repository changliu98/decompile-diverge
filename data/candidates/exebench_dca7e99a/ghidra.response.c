int _socket_close_(int *sockfd)

{
  int iVar1;
  int temp;
  int res;
  int *sockfd_local;
  
  iVar1 = *sockfd;
  *sockfd = -1;
  iVar1 = close(iVar1);
  return iVar1;
}