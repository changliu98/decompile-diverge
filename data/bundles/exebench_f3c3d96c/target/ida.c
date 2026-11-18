void __cdecl nist_increment_block(unsigned int *V)
{
  unsigned int x; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  for ( i = 3; i >= 0; --i )
  {
    x = ntohl(V[i]) + 1;
    V[i] = htonl(x);
    if ( x )
      break;
  }
}