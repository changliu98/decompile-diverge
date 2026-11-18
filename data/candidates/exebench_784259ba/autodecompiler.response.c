int inet_close( int *sock ){
 close( *sock & ~0xff );
 *sock = 0;
 return 0;
}