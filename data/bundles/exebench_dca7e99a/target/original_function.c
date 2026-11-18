int _socket_close_(int *sockfd) {
 int res;
 int temp = *sockfd;
 *sockfd = ((int)(~0));



 res = close(temp);

 return res;
}