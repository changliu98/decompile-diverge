int func0(char *s)

{
  int iVar1;
  size_t sVar2;
  int i;
  int len;
  int int_val;
  int rom_val [256];
  char *s_local;
  
  memset(rom_val,0,0x400);
  rom_val[0x49] = 1;
  rom_val[0x56] = 5;
  rom_val[0x58] = 10;
  rom_val[0x4c] = 0x32;
  rom_val[0x43] = 100;
  rom_val[0x44] = 500;
  rom_val[0x4d] = 1000;
  int_val = 0;
  sVar2 = strlen(s);
  for (i = 0; i < (int)sVar2; i = i + 1) {
    if ((i < 1) || (rom_val[s[i]] <= rom_val[s[i + -1]])) {
      iVar1 = rom_val[s[i]];
    }
    else {
      iVar1 = rom_val[s[i]] + rom_val[s[i + -1]] * -2;
    }
    int_val = iVar1 + int_val;
  }
  return int_val;
}