int __cdecl func0(const char *str)
{
  int count_0 = get_flip_with_starting_character(str, '0');
  int count_1 = get_flip_with_starting_character(str, '1');
  
  return count_0 < count_1 ? count_1 : count_0;
}