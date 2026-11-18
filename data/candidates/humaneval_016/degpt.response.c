int func0(char *str)

{
  uint uVar1;
  ushort **ppuVar2;
  char ch;
  int index;
  int char_map [256];
  int count;
  char *str_local;
  
  count = 0;
  memset(char_map,0,0x400);
  for (index = 0; str[index] != '\0'; index = index + 1) {
    uVar1 = tolower((uint)(byte)str[index]);
    if (char_map[(char)uVar1] == 0) {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)(uVar1 & 0xff)] & 0x400) != 0) {
        char_map[(char)uVar1] = 1;
        count = count + 1;
      }
    }
  }
  return count;
}