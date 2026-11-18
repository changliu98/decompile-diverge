int func0(char **argv, char *arg, int argc) {
    int i = 0;
    char found = 0;
    while (!found && i < argc) {
        if (strstr(argv[i], arg))
            found = 1;
        i++;
    }
    return found;
}