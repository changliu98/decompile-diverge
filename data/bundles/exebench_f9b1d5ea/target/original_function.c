int descape( int in[], int out[] )
{
 if( in[ 0 ] == '\\' )
 {
  switch( in[ 1 ] )
  {
   case 'a':
    out[ 1 ] = '\a';
    return 1;
   case 'b':
    out[ 1 ] = '\b';
    return 1;
   case 'f':
    out[ 1 ] = '\f';
    return 1;
   case 'n':
    out[ 1 ] = '\n';
    return 1;
   case 'r':
    out[ 1 ] = '\r';
    return 1;
   case 't':
    out[ 1 ] = '\t';
    return 1;
   case 'v':
    out[ 1 ] = '\v';
    return 1;
   case '?':
    out[ 1 ] = '\?';
    return 1;
   case '\'':
    out[ 1 ] = '\'';
    return 1;
   case '"':
    out[ 1 ] = '\"';
    return 1;
  }
 }

 out[ 0 ] = in[ 0 ]; out[ 1 ] = in[ 1 ];
 return 0;
}