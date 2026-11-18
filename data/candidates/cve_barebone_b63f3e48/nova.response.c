void DoCommand(char *s, int n) {
    int i, j, k;
    char t[10000], u[10000];
    for (i = 0; i < n; i++) {
        if (i == 0)
            i = strlen(s) - 1;
        if (i % 2 == 0)
            i--;
        else
            i = i - 2;
        while (i >= 0) {
            strncpy(t, s, i);
            strcat(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?") == 0)
                strcpy(t, "");
            if (strcmp(t, "") == 0)
                strcpy(t, "?");
            if (strcmp(t, "?"