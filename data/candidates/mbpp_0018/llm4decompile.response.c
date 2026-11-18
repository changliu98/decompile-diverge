char *func0(char *string, char *second_string)
{
    int *count = get_char_count_array(second_string);
    int ip_ind = 0;
    int res_ind = 0;
    char *str_list = str_to_list(string);
    while (str_list[ip_ind] != '\0')
    {
        if (count[str_list[ip_ind]] == 0)
        {
            str_list[res_ind] = str_list[ip_ind];
            res_ind++;
        }
        ip_ind++;
    }
    char *res = lst_to_string(str_list, res_ind);
    return res;
}