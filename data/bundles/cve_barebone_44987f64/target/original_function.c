int redis_check_aof_main(int argc, char **argv) {
    char *filepath;
    char temp_filepath[PATH_MAX + 1];
    char *dirpath;
    int fix = 0;

    if (argc < 2) {
        goto invalid_args;
    } else if (argc == 2) {
        if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
            sds version = getVersion();
            printf("redis-check-aof %s\n", version);
            sdsfree(version);
            exit(0);
        }

        filepath = argv[1];
    } else if (argc == 3) {
        if (!strcmp(argv[1], "--fix")) {
            filepath = argv[2];
            fix = 1;
        } else {
            goto invalid_args;
        }
    } else if (argc == 4) {
        if (!strcmp(argv[1], "--truncate-to-timestamp")) {
            char *endptr;
            errno = 0;
            to_timestamp = strtol(argv[2], &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                printf("Invalid timestamp, aborting...\n");
                exit(1);
            }
            filepath = argv[3];
        } else {
            goto invalid_args;
        }
    } else {
        goto invalid_args;
    }

    /* In the glibc implementation dirname may modify their argument. */
    memcpy(temp_filepath, filepath, strlen(filepath) + 1);
    dirpath = dirname(temp_filepath);

    /* Select the corresponding verification method according to the input file type. */
    input_file_type type = getInputFileType(filepath);
    switch (type) {
    case AOF_MULTI_PART:
        checkMultiPartAof(dirpath, filepath, fix);
        break;
    case AOF_RESP:
        checkOldStyleAof(filepath, fix, 0);
        break;
    case AOF_RDB_PREAMBLE:
        checkOldStyleAof(filepath, fix, 1);
        break;
    }

    exit(0);

invalid_args:
    printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n",
        argv[0]);
    exit(1);
}