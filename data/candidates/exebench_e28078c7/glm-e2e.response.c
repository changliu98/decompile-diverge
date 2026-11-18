int parse_int(char *str, int *result) {
    int i = 0;
    int val = 1;
    char c = '\0';
    int digit;
    int is_negative;
    int ret;

    *result = 0;
    
    is_negative = (str[i] == '-');
    if (is_negative) {
        i++;
    }
    
    int j = 1;
    while (str[j] != c) {
        val *= 10;
        j++;
    }
    
    while (str[i] != c) {
        digit = str[i] - '0';
        if (digit >= 0 && digit <= 9) {
            if (i > 0) {
                val /= 10;
            }
            *result += val * digit;
        } else {
            result = 0;
            ret = 0;
            return ret;
        }
        i++;
    }
    
    if (is_negative) {
        *result *= -1;
    }
    
    ret = 1;
    return ret;
}