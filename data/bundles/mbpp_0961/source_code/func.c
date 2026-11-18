

#include <stdio.h>

#include <assert.h>

#include <string.h>



int func0(char *s) {
  int rom_val[256] = {0};
  rom_val['I'] = 1;
  rom_val['V'] = 5;
  rom_val['X'] = 10;
  rom_val['L'] = 50;
  rom_val['C'] = 100;
  rom_val['D'] = 500;
  rom_val['M'] = 1000;
  int int_val = 0;
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (i > 0 && rom_val[s[i]] > rom_val[s[i - 1]]) {
      int_val += rom_val[s[i]] - 2 * rom_val[s[i - 1]];
    } else {
      int_val += rom_val[s[i]];
    }
  }
  return int_val;
}
