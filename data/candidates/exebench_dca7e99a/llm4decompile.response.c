int _socket_close_(int *sockfd)
{
 int fd = *sockfd;
 *sockfd = -1;
 return close(fd);
}