void func0(char *string,char *uppercase_characters,char *lowercase_characters,
          char *numerical_characters,char *special_characters)

{
  size_t sVar1;
  ushort **ppuVar2;
  int i;
  int len;
  int special_idx;
  int num_idx;
  int lower_idx;
  int upper_idx;
  char *special_characters_local;
  char *numerical_characters_local;
  char *lowercase_characters_local;
  char *uppercase_characters_local;
  char *string_local;
  
  upper_idx = 0;
  lower_idx = 0;
  num_idx = 0;
  special_idx = 0;
  sVar1 = strlen(string);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)string[i]] & 0x100) == 0) {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)string[i]] & 0x200) == 0) {
        ppuVar2 = __ctype_b_loc();
        if (((*ppuVar2)[(int)string[i]] & 0x800) == 0) {
          if ((((string[i] == ',') || (string[i] == '.')) || (string[i] == '!')) ||
             (string[i] == '?')) {
            special_characters[special_idx] = string[i];
            special_idx = special_idx + 1;
          }
        }
        else {
          numerical_characters[num_idx] = string[i];
          num_idx = num_idx + 1;
        }
      }
      else {
        lowercase_characters[lower_idx] = string[i];
        lower_idx = lower_idx + 1;
      }
    }
    else {
      uppercase_characters[upper_idx] = string[i];
      upper_idx = upper_idx + 1;
    }
  }
  uppercase_characters[upper_idx] = '\0';
  lowercase_characters[lower_idx] = '\0';
  numerical_characters[num_idx] = '\0';
  special_characters[special_idx] = '\0';
  return;
}