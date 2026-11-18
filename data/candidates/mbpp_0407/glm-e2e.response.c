int func0(int num) {
    char str[20];
    sprintf(str, "%d", num);
    int len = strlen(str);
    
    for (int i = len - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            char temp[20];
            strcpy(temp, str + i);
            int temp_len = strlen(temp);
            char min_char = temp[1];
            
            for (int j = 1; j < temp_len; j++) {
                if (temp[j] > temp[0] && temp[j] < min_char) {
                    min_char = temp[j];
                }
            }
            
            for (int j = 0; j < temp_len; j++) {
                if (temp[j] == min_char) {
                    for (int k = j; k < temp_len - 1; k++) {
                        temp[k] = temp[k + 1];
                    }
                    temp[temp_len - 1] = '\0';
                    break;
                }
            }
            
            char *ptr = temp;
            qsort(&ptr, 1, sizeof(char *), cmp);
            
            str[i] = min_char;
            strcpy(str + i + 1, temp);
            return atoi(str);
        }
    }
    return 0;
}