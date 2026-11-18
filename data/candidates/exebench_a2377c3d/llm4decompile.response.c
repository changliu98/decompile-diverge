void swap2int(int *a,int *b)
{
  if( *a != *b )
    {
      *a ^= *b;
      *b ^= *a;
      *a ^= *b;
    }
}