int inet_close(int *sockfd)
{
  close(*sockfd);
  *sockfd = 0;
  return 0;
}