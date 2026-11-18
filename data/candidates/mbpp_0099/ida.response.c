char *__cdecl func0(int n)
{
  int v1; // eax
  char temp; // [rsp+1h] [rbp-11h]
  int end; // [rsp+2h] [rbp-10h]
  int start; // [rsp+6h] [rbp-Ch]
  int index; // [rsp+Ah] [rbp-8h]

  index = 0;
  while ( n > 0 )
  {
    v1 = index++;
    func0_binary[v1] = n % 2 + 48;
    n /= 2;
  }
  func0_binary[index] = 0;
  start = 0;
  for ( end = index - 1; start < end; --end )
  {
    temp = func0_binary[start];
    func0_binary[start] = func0_binary[end];
    func0_binary[end] = temp;
    ++start;
  }
  return func0_binary;
}