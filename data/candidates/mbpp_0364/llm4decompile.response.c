int func0(char *str)
{
 int ret;

 if (get_flip_with_starting_character(str, '0') < get_flip_with_starting_character(str, '1'))
  ret = get_flip_with_starting_character(str, '0');
 else
  ret = get_flip_with_starting_character(str, '1');

 return ret;
}