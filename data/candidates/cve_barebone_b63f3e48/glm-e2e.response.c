void DoCommand(const char *filename, int verbose) {
    char temp[0x4030];
    char cmd[0x1010];
    struct stat temp_st;
    struct stat file_st;
    struct utimbuf ub;
    int has_output_redirect = 0;
    int cmd_len = 0;
    int len = strlen(filename) - 1;

    // Strip trailing slashes from filename
    while (len > 0 && filename[len - 1] != '/') {
        len--;
    }

    memcpy(temp, filename, len);
    strcpy(temp + len, "XXXXXX"); // 0xac2 offset points to "XXXXXX"

    if (mktemp(temp) == NULL || temp[0] == '\0') {
        ErrFatal("mktemp failed"); // 0xaa4 offset
    }

    len = 0;
    while (ApplyCommand[len] == '&') {
        if (ApplyCommand[len + 1] == 'i') {
            cmd_len += shellescape(cmd + cmd_len, filename);
            len += 2;
        } else if (ApplyCommand[len + 1] == 'o') {
            cmd_len += shellescape(cmd + cmd_len, temp);
            len += 2;
            has_output_redirect = 1;
        } else {
            break;
        }
    }

    while (ApplyCommand[len] != '\0') {
        cmd[cmd_len++] = ApplyCommand[len++];
    }

    if (verbose) {
        printf("DoCommand: %s\n", cmd); // 0x99e offset
    }

    errno = 0;
    int ret = system(cmd);
    if (ret != 0 || errno != 0) {
        if (errno != 0) {
            perror("system() failed"); // 0x958 offset
        }
        ErrFatal("Cannot execute command"); // 0x953 offset
    }

    if (has_output_redirect) {
        if (stat(temp, &temp_st) != 0) {
            ErrFatal("output file not created"); // 0x8c6 offset
        }

        int old_stat_ret = stat(filename, &file_st);
        unlink(filename);
        rename(temp, filename);

        if (old_stat_ret == 0) {
            chmod(filename, file_st.st_mode);
            ub.actime = file_st.st_atim.tv_sec;
            ub.modtime = file_st.st_mtim.tv_sec;
            utime(filename, &ub);
        }
    }
}