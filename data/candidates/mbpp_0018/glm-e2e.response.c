char* func0(char* s, char* t) {
    int* char_count = get_char_count_array(t);
    int i = 0;
    int j = 0;
    char* list = str_to_list(s);
    
    while (list[i] != '\0') {
        char c = list[i];
        if (char_count[(int)c] == 0) {
            list[j] = c;
            j++;
        }
        i++;
    }
    
    return lst_to_string(list, j);
}