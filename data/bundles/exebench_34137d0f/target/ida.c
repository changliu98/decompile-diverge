int __cdecl sha_init(int *hash)
{
  *hash = 1732584193;
  hash[1] = -271733879;
  hash[2] = -1732584194;
  hash[3] = 271733878;
  hash[4] = -1009589776;
  return 0;
}