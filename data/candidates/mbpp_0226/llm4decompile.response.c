char *func0(char *str)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < strlen(str); i++) {
        if (i % 2 == 0) {
            func0::result[j] = str[i];
            j++;
        }
    }
    func0::result[j] = '\0';
    return func0::result;
}