char *__cdecl func0(int n)
{
  char temp;
  int end;
  int start = 0;
  int index = 0;

  // Convert integer to binary string (LSB first)
  while (n > 0)
  {
    func0_binary[index++] = (n % 2) + '0';
    n /= 2;
  }
  func0_binary[index] = '\0';

  // Reverse the string to get MSB first
  for (end = index - 1; start < end; --end)
  {
    temp = func0_binary[start];
    func0_binary[start] = func0_binary[end];
    func0_binary[end] = temp;
    ++start;
  }

  return func0_binary;
}