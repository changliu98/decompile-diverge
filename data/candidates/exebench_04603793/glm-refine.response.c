void __cdecl itoa(unsigned __int64 value, char *buffer)
{
  unsigned __int64 temp;
  unsigned __int64 current_val;

  current_val = value;
  temp = value;

  // First pass: find where the string will end by counting digits
  do
  {
    ++buffer;
    temp /= 10;
  }
  while (temp);

  // Null-terminate the string at the end
  *buffer = '\0';

  // Second pass: work backwards, filling in the digits
  do
  {
    *(--buffer) = current_val % 10 + '0';
    current_val /= 10;
  }
  while (current_val);
}