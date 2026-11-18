__attribute__((noinline))
static void SetBpfStringFromFile(char *filename)
{
    char *bpf_filter = NULL;
    char *bpf_comment_tmp = NULL;
    char *bpf_comment_start =  NULL;
    uint32_t bpf_len = 0;
    SCStat st;
    FILE *fp = NULL;
    size_t nm = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        SCLogError("Failed to open file %s", filename);
        exit(EXIT_FAILURE);
    }

    if (SCFstatFn(fileno(fp), &st) != 0) {
        SCLogError("Failed to stat file %s", filename);
        exit(EXIT_FAILURE);
    }
    bpf_len = st.st_size + 1;

    bpf_filter = SCCalloc(1, bpf_len);
    if (unlikely(bpf_filter == NULL)) {
        SCLogError("Failed to allocate buffer for bpf filter in file %s", filename);
        exit(EXIT_FAILURE);
    }

    nm = fread(bpf_filter, 1, bpf_len - 1, fp);
    if ((ferror(fp) != 0) || (nm != (bpf_len - 1))) {
        SCLogError("Failed to read complete BPF file %s", filename);
        SCFree(bpf_filter);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    bpf_filter[nm] = '\0';

    if(strlen(bpf_filter) > 0) {
        /*replace comments with space*/
        bpf_comment_start = bpf_filter;
        while((bpf_comment_tmp = strchr(bpf_comment_start, '#')) != NULL) {
            while((*bpf_comment_tmp !='\0') &&
                (*bpf_comment_tmp != '\r') && (*bpf_comment_tmp != '\n'))
            {
                *bpf_comment_tmp++ = ' ';
            }
            bpf_comment_start = bpf_comment_tmp;
        }
        /*remove remaining '\r' and '\n' */
        while((bpf_comment_tmp = strchr(bpf_filter, '\r')) != NULL) {
            *bpf_comment_tmp = ' ';
        }
        while((bpf_comment_tmp = strchr(bpf_filter, '\n')) != NULL) {
            *bpf_comment_tmp = ' ';
        }
        /* cut trailing spaces */
        while (strlen(bpf_filter) > 0 &&
                bpf_filter[strlen(bpf_filter)-1] == ' ')
        {
            bpf_filter[strlen(bpf_filter)-1] = '\0';
        }
        if (strlen(bpf_filter) > 0) {
            if (ConfSetFinal("bpf-filter", bpf_filter) != 1) {
                SCFree(bpf_filter);
                FatalError("failed to set bpf filter");
            }
        }
    }
    SCFree(bpf_filter);
}