int sock_connect(int *sockfd, char *ip, int port)
{
 struct sockaddr_in address;
 int ret;

 if ((*sockfd = socket(2, 1, 0)) == -1) {
  ret = -1;
  goto _out;
 }

 address.sin_family = 2;
 address.sin_addr.s_addr = inet_addr(ip);
 address.sin_port = htons((unsigned short)port);

 if (connect(*sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
  close(*sockfd);
  ret = -1;
  goto _out;
 }

 ret = 0;
_out:
 return ret;
}