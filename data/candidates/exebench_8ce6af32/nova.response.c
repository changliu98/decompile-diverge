static int endStrider(char *buf, int *state) {
    return (strstr(buf, "<HTML>")!= NULL)? 1 : 0;
}