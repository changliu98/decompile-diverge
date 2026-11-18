char * func0(char *string)

{
  int iVar1;
  int i;
  char *string_local;
  
  for (i = 0; string[i] != '\0'; i = i + 1) {
    iVar1 = toupper((uint)(byte)string[i]);
    func0::result[i] = (char)iVar1;
  }
  func0::result[i] = '\0';
  return func0::result;
}