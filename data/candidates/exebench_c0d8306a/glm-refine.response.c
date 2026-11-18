int __cdecl file_getversion(int *version)
{
  // Sets the output version to 10 and always returns success (0)
  if (version)
    *version = 10;
  return 0;
}