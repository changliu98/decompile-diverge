int get_flip_with_starting_number(char *str)
{
  int flip_with_starting_0 = get_flip_with_starting_character(str, '0');
  int flip_with_starting_1 = get_flip_with_starting_character(str, '1');
  if (flip_with_starting_0 < flip_with_starting_1)
    return flip_with_starting_0;
  else
    return flip_with_starting_1;
}