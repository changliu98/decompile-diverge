void func0(char *str, int key) {
    int i = 0;
    while (str[i]!= '\0') {
        if (str[i] == '-') {
            str[i] ='';
        } else {
            int temp = str[i] - 'a';
            temp = (temp + key) % 26;
            str[i] = (char)(temp + 'a');
        }
        i++;
    }
}