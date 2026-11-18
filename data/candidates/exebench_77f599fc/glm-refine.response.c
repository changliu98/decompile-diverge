void __cdecl uppercaser(char *string)
{
  if (!string)
    return;

  for (size_t i = 0; string[i] != '\0'; ++i)
  {
    if (string[i] >= 'a' && string[i] <= 'z')
      string[i] -= 'a' - 'A'; // Equivalent to -= 32
  }
}