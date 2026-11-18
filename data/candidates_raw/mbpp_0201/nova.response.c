int func0(char **argv, int start) {
    int i;
    int match;

    i = 1;
    match = 1;
    while (match) {
        if (i >= start) {
            if (strcmp(argv[i], argv[0]) == 0) {
                match = 0;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }
    return (i);
}