int inet_close(struct socket *sock)
{
 close(sock->fd);
 sock->fd = 0;
 return 0;
}