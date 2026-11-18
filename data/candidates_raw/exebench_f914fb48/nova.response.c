void func0(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        if (str[i]!= '\0' && str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
        else if (str[i]!= '\0' && str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
}