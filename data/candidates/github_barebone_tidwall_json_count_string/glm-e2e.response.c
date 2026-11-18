size_t count_string(const char *str, const char *end, int *out_count) {
    size_t length = end - str;
    size_t i = 1;
    int count = 0;
    unsigned char flag = 0;

    while (1) {
        // Process chunks of 8 characters
        if (i + 8 <= length) {
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
            
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
        } else {
            // Process remaining characters one by one
            if (i + 1 > length) {
                break;
            }
            if (table[(unsigned char)str[i]]) break;
            flag = 0;
            i++;
        }
        
        // Handle quotes and escape sequences
        if (str[i] == '"') {
            i++;
            if (!flag) {
                break;
            }
            flag = 0;
        } else if (str[i] == '\\') {
            count |= 1;
            flag = ~flag & 1;
            i++;
        } else {
            i++;
        }
    }

    *out_count = count;
    return i;
}