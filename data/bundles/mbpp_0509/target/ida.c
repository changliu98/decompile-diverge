int __cdecl func0(int n)
{
  int count; // [rsp+0h] [rbp-10h]
  int sm; // [rsp+4h] [rbp-Ch]
  int na; // [rsp+8h] [rbp-8h]

  na = n;
  if ( n % 2 )
  {
    sm = 0;
    count = 0;
    while ( na >= 1 )
    {
      ++count;
      sm += na;
      na -= 2;
    }
    return sm / count;
  }
  else
  {
    printf("Invalid Input\n");
    return -1;
  }
}