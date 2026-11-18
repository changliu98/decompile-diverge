int roman_to_int(char *s)
{
  char *p = s;
  int i; int len; int val; int int_val;
  int rom_val[256];
  memset(rom_val, 0, sizeof(rom_val));
  rom_val['I'] = 1;
  rom_val['V'] = 5;
  rom_val['X'] = 10;
  rom_val['L'] = 50;
  rom_val['C'] = 100;
  rom_val['D'] = 500;
  rom_val['M'] = 1000;
  int_val = 0;
  len = strlen(p);
  for (i = 0; i < len; i++) {
    if (i > 0 && rom_val[p[i]] > rom_val[p[i - 1]]) {
      int_val += (rom_val[p[i]] - 2 * rom_val[p[i - 1]]);
    } else {
      int_val += rom_val[p[i]];
    }
  }
  return int_val;
}