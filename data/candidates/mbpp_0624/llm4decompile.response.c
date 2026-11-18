char *func0(const char *str)
{
 int i;
 for (i = 0; str[i]; i++)
  func0::result[i] = toupper((unsigned char)str[i]);
 func0::result[i] = 0;
 return func0::result;
}