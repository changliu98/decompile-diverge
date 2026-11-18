char* get_middle_str(int num1, int num2) {
    char *str;
    if(num1 > num2) {
        str = "-1";
    } else {
        int sum = (num2 + num1) / 2;
        str = (char *)malloc(sizeof(char)*33);
        strcpy(str, "");
        int index = 32;
        str[index--] = '\0';
        do {
            str[index--] = sum % 2 + '0';
            sum /= 2;
        } while(sum > 0);
        str = &str[index+1];
    }
    return str;
}