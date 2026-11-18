char *__cdecl func0(char *string, char *second_string)
{
  int v2; // ecx
  char temp; // [rsp+7h] [rbp-29h]
  char *str_list; // [rsp+8h] [rbp-28h]
  int res_ind; // [rsp+10h] [rbp-20h]
  int ip_ind; // [rsp+14h] [rbp-1Ch]
  int *count; // [rsp+18h] [rbp-18h]

  count = get_char_count_array(second_string);
  ip_ind = 0;
  res_ind = 0;
  str_list = str_to_list(string);
  while ( str_list[ip_ind] )
  {
    temp = str_list[ip_ind];
    if ( !count[temp] )
    {
      v2 = res_ind++;
      str_list[v2] = temp;
    }
    ++ip_ind;
  }
  return lst_to_string(str_list, res_ind);
}