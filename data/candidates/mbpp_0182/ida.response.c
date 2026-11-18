void __cdecl func0(
        char *string,
        char *uppercase_characters,
        char *lowercase_characters,
        char *numerical_characters,
        char *special_characters)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int i; // [rsp+0h] [rbp-40h]
  int len; // [rsp+4h] [rbp-3Ch]
  int special_idx; // [rsp+8h] [rbp-38h]
  int num_idx; // [rsp+Ch] [rbp-34h]
  int lower_idx; // [rsp+10h] [rbp-30h]
  int upper_idx; // [rsp+14h] [rbp-2Ch]

  upper_idx = 0;
  lower_idx = 0;
  num_idx = 0;
  special_idx = 0;
  len = strlen(string);
  for ( i = 0; i < len; ++i )
  {
    if ( ((*__ctype_b_loc())[string[i]] & 0x100) != 0 )
    {
      v5 = upper_idx++;
      uppercase_characters[v5] = string[i];
    }
    else if ( ((*__ctype_b_loc())[string[i]] & 0x200) != 0 )
    {
      v6 = lower_idx++;
      lowercase_characters[v6] = string[i];
    }
    else if ( ((*__ctype_b_loc())[string[i]] & 0x800) != 0 )
    {
      v7 = num_idx++;
      numerical_characters[v7] = string[i];
    }
    else if ( string[i] == 44 || string[i] == 46 || string[i] == 33 || string[i] == 63 )
    {
      v8 = special_idx++;
      special_characters[v8] = string[i];
    }
  }
  uppercase_characters[upper_idx] = 0;
  lowercase_characters[lower_idx] = 0;
  numerical_characters[num_idx] = 0;
  special_characters[special_idx] = 0;
}