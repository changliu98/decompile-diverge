int findMax(char *str) {
    char num[255];
    int max = 0;
    int index = 0;
    for(int i = 0; str[i] != '\0'; ++i) {
        if(str[i] >= '0' && str[i] <= '9') {
            num[index++] = str[i];
        } else {
            if(index > 0) {
                num[index] = '\0';
                int n = atoi(num);
                if(n > max) max = n;
                index = 0;
            }
        }
    }

    if(index > 0) {
        num[index] = '\0';
        int n = atoi(num);
        if(n > max) max = n;
    }
    return max;
}