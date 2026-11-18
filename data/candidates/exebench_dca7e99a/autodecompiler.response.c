int _socket_close_( int *socket )
{
 int ret;
 int s = *socket;

 *socket = -1;
 ret = close( s );
 return ret;
}