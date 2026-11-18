char * func0(char *string)

{
  int iVar1;
  ushort **ppuVar2;
  int i;
  char *string_local;
  
  strcpy(func0::toggled_string,string);
  for (i = 0; func0::toggled_string[i] != '\0'; i = i + 1) {
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)func0::toggled_string[i]] & 0x100) == 0) {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)func0::toggled_string[i]] & 0x200) != 0) {
        iVar1 = toupper((int)func0::toggled_string[i]);
        func0::toggled_string[i] = (char)iVar1;
      }
    }
    else {
      iVar1 = tolower((int)func0::toggled_string[i]);
      func0::toggled_string[i] = (char)iVar1;
    }
  }
  return func0::toggled_string;
}