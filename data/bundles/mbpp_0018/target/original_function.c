char *func0(char *string, char *second_string) {
  int *count = get_char_count_array(second_string);
  int ip_ind = 0, res_ind = 0;
  char *str_list = str_to_list(string);
  while (str_list[ip_ind] != '\0') {
    char temp = str_list[ip_ind];
    if (count[(int)temp] == 0) {
      str_list[res_ind++] = temp;
    }
    ip_ind++;
  }
  return lst_to_string(str_list, res_ind);
}