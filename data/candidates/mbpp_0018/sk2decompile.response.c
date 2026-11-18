char *func0(char *str, char *remove) {
  int *count = get_char_count_array(remove);
  int i = 0, j = 0;
  char *list = str_to_list(str);
  while (list[i] != '\0') {
    char c = list[i];
    if (count[c] == 0) {
      list[j++] = c;
    }
    i++;
  }
  return lst_to_string(list, j);
}