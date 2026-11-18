static void special_keys(char *filename) {
    FILE *fp = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char buf[256];
    while ((read = getline(&line, &len, fp))!= -1) {
        char *p = strtok(line, "-");
        int i = 0;
        while (p) {
            char *q = strchr(p, '-');
            if (q)
                *q = 0;
            int c = p[0];
            switch (c) {
            case 'A':
                buf[i++] = c;
                break;
            case 'C':
                buf[i++] = c;
                break;
            case 'G':
                buf[i++] = c;
                break;
            case 'T':
                buf[i++] = c;
                break;
            }
            p = q? q + 1 : NULL;
            if (p)
                buf[i++] = '-';
        }
        if (strlen(line) + i < sizeof(buf))
            strcpy(buf + i, line);
        line = NULL;
        len = 0;
        fwrite(buf, sizeof(buf), 1, stdout);
    }
    fclose(fp);
}