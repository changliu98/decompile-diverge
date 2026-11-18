int func0(char *string, char c) {
    int length = strlen(string);
    int i;
    int position = -1;
    for (i = 0; i < length; i++) {
        if (string[i] == c) {
            position = i;
        }
    }
    if (position == -1) {
        return -1;
    } else {
        return position + 1;
    }
}