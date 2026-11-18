char *remove_chars(char *str, char *chars)
{
  int *char_count = get_char_count_array(chars);
  int i = 0;
  int j = 0;
  char *str_list = str_to_list(str);
  char temp;
  while (str_list[i] != '\0')
  {
    temp = str_list[i];
    if (char_count[temp] == 0)
    {
      str_list[j++] = temp;
    }
    i++;
  }
  return lst_to_string(str_list, j);
}