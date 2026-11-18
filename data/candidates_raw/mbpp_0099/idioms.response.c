char *to_binary(int n)
{
  int i = 0;
  while ( n > 0 )
  {
    to_binary_binary[i++] = (char)(n % 2 + '0');
    n /= 2;
  }
  to_binary_binary[i] = '\0';
  int start = 0;
  int end = i - 1;
  char temp;
  while ( start < end )
  {
    temp = to_binary_binary[start];
    to_binary_binary[start] = to_binary_binary[end];
    to_binary_binary[end] = temp;
    start++;
    end--;
  }
  return to_binary_binary;
}