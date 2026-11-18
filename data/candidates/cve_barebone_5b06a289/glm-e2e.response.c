void SetBpfStringFromFile(const char *file_path) {
    char *buf = NULL;
    char *p = NULL;
    char *p_start = NULL;
    size_t read_len = 0;
    int file_size = 0;
    FILE *fp = NULL;
    struct stat st;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        vb_log_stub("Failed to open BPF file '%s'", file_path);
        exit(1);
    }

    if (fstat(fileno(fp), &st) != 0) {
        vb_log_stub("Failed to stat BPF file '%s'", file_path);
        exit(1);
    }

    file_size = st.st_size + 1;
    buf = calloc(1, file_size);
    if (buf == NULL) {
        vb_log_stub("Failed to allocate memory for BPF file '%s'", file_path);
        exit(1);
    }

    read_len = fread(buf, 1, file_size - 1, fp);
    if (ferror(fp) || read_len != file_size - 1) {
        vb_log_stub("Failed to read BPF file '%s'", file_path);
        free(buf);
        fclose(fp);
        exit(1);
    }

    fclose(fp);
    buf[read_len] = '\0';

    if (strlen(buf) > 0) {
        p_start = buf;
        p = strchr(p_start, '#');
        while (p != NULL) {
            while (*p != '\0' && *p != '\r' && *p != '\n') {
                *p = ' ';
                p++;
            }
            p_start = p;
            p = strchr(p_start, '#');
        }

        while ((p = strchr(buf, '\r')) != NULL) {
            *p = ' ';
        }

        while ((p = strchr(buf, '\n')) != NULL) {
            *p = ' ';
        }

        while (strlen(buf) > 0 && buf[strlen(buf) - 1] == ' ') {
            buf[strlen(buf) - 1] = '\0';
        }

        if (strlen(buf) > 0) {
            if (ConfSetFinal("sc_filter_bpf", buf) != 1) {
                free(buf);
                vb_log_stub("Failed to set BPF filter in configuration");
                exit(1);
            }
        }
    }

    free(buf);
}