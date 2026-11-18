void SetBpfStringFromFile(const char *filename)
{
    FILE *fp;
    char *bpf_filter;
    int res;
    int bpf_len;
    char *bpf_comment_start;
    char *bpf_comment_tmp;
    struct stat st;
    size_t read_len;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        vb_log_stub("Failed to open file %s", filename);
        exit(1);
    }

    res = fstat(fileno(fp), &st);
    if (res != 0) {
        vb_log_stub("Failed to stat file %s", filename);
        exit(1);
    }

    bpf_filter = calloc(1, st.st_size + 1);
    if (bpf_filter == NULL) {
        vb_log_stub("Failed to allocate buffer for bpf filter in file %s", filename);
        exit(1);
    }

    read_len = fread(bpf_filter, 1, st.st_size, fp);
    if (!ferror(fp) && read_len == (size_t)st.st_size) {
        fclose(fp);
        bpf_filter[read_len] = '\0';
    } else {
        vb_log_stub("Failed to read complete BPF file %s", filename);
        free(bpf_filter);
        fclose(fp);
        exit(1);
    }


    if (strlen(bpf_filter) == 0) {
        free(bpf_filter);
        return;
    }


    bpf_comment_start = bpf_filter;
    while ((bpf_comment_tmp = strchr(bpf_comment_start, '#')) != NULL) {
        while (*bpf_comment_tmp != '\0' && *bpf_comment_tmp != '\r' && *bpf_comment_tmp != '\n') {
            *bpf_comment_tmp = ' ';
            bpf_comment_tmp++;
        }
        bpf_comment_start = bpf_comment_tmp;
    }


    while ((bpf_comment_tmp = strchr(bpf_filter, '\r')) != NULL) {
        *bpf_comment_tmp = ' ';
    }
    while ((bpf_comment_tmp = strchr(bpf_filter, '\n')) != NULL) {
        *bpf_comment_tmp = ' ';
    }


    while (strlen(bpf_filter) > 0 && bpf_filter[strlen(bpf_filter) - 1] == ' ') {
        bpf_filter[strlen(bpf_filter) - 1] = '\0';
    }


    if (strlen(bpf_filter) > 0) {
        res = ConfSetFinal("bpf-filter", bpf_filter);
        if (res != 1) {
            free(bpf_filter);
            vb_log_stub("failed to set bpf filter");
            exit(1);
        }
    }

    free(bpf_filter);
}