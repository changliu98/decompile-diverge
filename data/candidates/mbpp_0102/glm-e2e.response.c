char *func0(char *input, char *output) {
    int i = 0;
    int j = 0;
    int flag = 1;

    while (input[i] != '\0') {
        if (input[i] == '_') {
            flag = 1;
        } else if (flag) {
            output[j++] = toupper(input[i]);
            flag = 0;
        } else {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
    return output;
}