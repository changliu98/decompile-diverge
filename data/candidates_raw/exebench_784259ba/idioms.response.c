int close_socket(int *sockfd)
{
  close(*sockfd);
  *sockfd = 0;
  return 0;
}