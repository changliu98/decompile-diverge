int WINS_CloseSocket( int *sock ){
 close( *sock & ~0xff );
 *sock = 0;
 return 0;
}