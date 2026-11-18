char *func0(char **argv, int argc) {
    static char buf[100];
    int i;

    strcpy(buf, "");
    for (i = 0; i < argc; i++) {
        double d1 = atof(argv[i]);
        double d2 = atof(argv[i + 1]);
        sprintf(buf + strlen(buf), "0x%08x 0x%08x ", (int)d1, (int)d2);
        if (i < argc - 2)
            strcat(buf, ",");
    }
    strcat(buf, "\n");
    return buf;
}