void reverse(char *str, int encode) {
    int str_len = strlen(str);
    int num_chars = (str_len + 2) / 3;
    char temp[3];
    for(int i = 0; i < num_chars; i++) {
        int chars_to_read = (i*3 + 3 <= str_len) ? 3 : str_len - i*3;
        int chars_read = strncpy(temp, str + i*3, chars_to_read);
        temp[chars_read] = '\0';
        if(chars_read == 3) {
            if(encode) {
                char tmp = temp[2];
                temp[2] = temp[1];
                temp[1] = temp[0];
                temp[0] = tmp;
            } else {
                char tmp = temp[0];
                temp[0] = temp[1];
                temp[1] = temp[2];
                temp[2] = tmp;
            }
        }
        strncpy(str + i*3, temp, chars_read);
    }
}