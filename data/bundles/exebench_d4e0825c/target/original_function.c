static __inline__ int unix_socketpair( int d, int type, int protocol, int sv[2] )
{
 return socketpair( d, type, protocol, sv );
}