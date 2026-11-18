char * func0(char *string,char *second_string)

{
  int *piVar1;
  char *pcVar2;
  char temp;
  char *str_list;
  int res_ind;
  int ip_ind;
  int *count;
  char *second_string_local;
  char *string_local;
  
  piVar1 = get_char_count_array(second_string);
  ip_ind = 0;
  res_ind = 0;
  pcVar2 = str_to_list(string);
  for (; pcVar2[ip_ind] != '\0'; ip_ind = ip_ind + 1) {
    if (piVar1[(int)pcVar2[ip_ind]] == 0) {
      pcVar2[res_ind] = pcVar2[ip_ind];
      res_ind = res_ind + 1;
    }
  }
  pcVar2 = lst_to_string(pcVar2,res_ind);
  return pcVar2;
}