int parse_device(int64_t *pdev, void *archive, char *str) {
    int64_t dev = 0;
    int64_t nums[3];
    char *p;
    void *pack;
    int count = 0;
    int ret = 0;
    char *token;

    memset(pdev, 0, 8);

    p = strchr(str, ',');
    if (p != NULL) {
        *p = '\0';
        p++;

        pack = pack_find(str);
        if (pack == NULL) {
            archive_set_error(archive, 22, "Unknown pack format `%s'", str);
            ret = -20;
            goto end;
        }

        while ((token = la_strsep(&p, " ")) != NULL) {
            if (*token == '\0') {
                archive_set_error(archive, 22, "Missing field in device specification");
                ret = -20;
                goto end;
            }

            nums[count] = mtree_atol(&token);
            count++;

            if (count > 3) {
                archive_set_error(archive, 22, "Too many fields in device specification");
                ret = -20;
                goto end;
            }
        }

        if (count < 2) {
            archive_set_error(archive, 22, "Not enough fields in device specification");
            ret = -20;
            goto end;
        }

        // pack is a function pointer based on the `call *%rax` instruction
        dev = ((int64_t (*)(int, int64_t[], int64_t *))pack)(count, nums, &dev);
        
        if (dev != 0) {
            archive_set_error(archive, 22, "Failed to parse device specification: %s", (char *)dev);
            ret = -20;
            goto end;
        }
    } else {
        dev = mtree_atol(&str);
    }

    *pdev = dev;

end:
    return ret;
}