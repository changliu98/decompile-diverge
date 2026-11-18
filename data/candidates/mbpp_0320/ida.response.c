int __cdecl func0(int n)
{
  int num; // [rsp+0h] [rbp-10h]
  int squareofsum; // [rsp+4h] [rbp-Ch]
  int sumofsquares; // [rsp+8h] [rbp-8h]

  sumofsquares = 0;
  squareofsum = 0;
  for ( num = 1; num <= n; ++num )
  {
    sumofsquares += num * num;
    squareofsum += num;
  }
  return squareofsum * squareofsum - sumofsquares;
}