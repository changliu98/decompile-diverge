vout_window_t *func0(int fd, char *(*readline)(int))
{
    int i = 0, j = 0;
    for (;;) {
        char *line = readline(fd);
        if (line[0] == '\0')
            break;

        if (isdigit(line[0])) {
            int found = 0;
            for (int k = 0; k < i; k++) {
                if (strcmp(vout_windows[k].name, line) == 0) {
                    vout_windows[k].references++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(vout_windows[i].name, line);
                vout_windows[i].references = 1;
                i++;
            }
        } else {
            char name[80];
            int found = 0;
            for (int k = 0; k < i; k++) {
                if (vout_windows[k].references > j) {
                    j = vout_windows[k].references;
                    strcpy(name, vout_windows[k].name);
                    found = k;
                }
            }
            return &vout_windows[found];
        }
    }
    return NULL;
}