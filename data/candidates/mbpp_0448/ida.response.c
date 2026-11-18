int __cdecl func0(int n)
{
  int d; // [rsp+0h] [rbp-1Ch]
  int sum; // [rsp+4h] [rbp-18h]
  int c; // [rsp+8h] [rbp-14h]
  int b; // [rsp+Ch] [rbp-10h]
  int a; // [rsp+10h] [rbp-Ch]
  int na; // [rsp+14h] [rbp-8h]

  na = n;
  a = 3;
  b = 0;
  c = 2;
  switch ( n )
  {
    case 0:
      return 3;
    case 1:
      return 3;
    case 2:
      return 5;
  }
  sum = 5;
  while ( na > 2 )
  {
    d = b + a;
    sum += b + a;
    a = b;
    b = c;
    c = d;
    --na;
  }
  return sum;
}