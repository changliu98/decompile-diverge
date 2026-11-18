int func0(char *(*dict) [2],int size)

{
  char *pcVar1;
  ushort **ppuVar2;
  int j;
  char *key;
  int i;
  int has_upper;
  int has_lower;
  int size_local;
  char *(*dict_local) [2];
  int local_c;
  
  if (size == 0) {
    local_c = 0;
  }
  else {
    has_lower = 0;
    has_upper = 0;
    for (i = 0; i < size; i = i + 1) {
      pcVar1 = dict[i][0];
      for (j = 0; pcVar1[j] != '\0'; j = j + 1) {
        ppuVar2 = __ctype_b_loc();
        if (((*ppuVar2)[(int)(uint)(byte)pcVar1[j]] & 0x400) == 0) {
          return 0;
        }
        ppuVar2 = __ctype_b_loc();
        if (((*ppuVar2)[(int)(uint)(byte)pcVar1[j]] & 0x100) != 0) {
          has_upper = 1;
        }
        ppuVar2 = __ctype_b_loc();
        if (((*ppuVar2)[(int)(uint)(byte)pcVar1[j]] & 0x200) != 0) {
          has_lower = 1;
        }
        if (has_upper + has_lower == 2) {
          return 0;
        }
      }
    }
    local_c = 1;
  }
  return local_c;
}