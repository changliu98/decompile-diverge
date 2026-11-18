char   *func0(char *filelist[], int n) {
    static char filename[200];
    static int  i = 0;

    strcpy(filename, "../data/");
    for (; i < n;) {
        strcat(filename, filelist[i]);
        i++;
        break;
    }
    return (filename);
}