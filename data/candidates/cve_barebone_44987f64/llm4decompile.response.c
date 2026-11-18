int redis_check_aof_main(int argc, char **argv) {
    char *filepath, *dirpath;
    char temp_filepath[4096];
    input_file_type type;
    int fix = 0;

    if (argc < 2) {
        printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n", argv[0]);
        exit(1);
    } else if (argc == 2 && (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version"))) {
        sds version = getVersion();
        printf("redis-check-aof %s\n", version);
        sdsfree(version);
        exit(0);
    } else if (argc == 3 && !strcmp(argv[1],"--fix")) {
        fix = 1;
        filepath = argv[2];
    } else if (argc == 4 && !strcmp(argv[1],"--truncate-to-timestamp")) {
        char *endptr;
        *__errno_location() = 0;
        to_timestamp = strtol(argv[2],&endptr,10);
        if (*__errno_location() != 0 || *endptr != '\0') {
            printf("Invalid timestamp, aborting...\n");
            exit(1);
        }
        filepath = argv[3];
    } else {
        printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n", argv[0]);
        exit(1);
    }

    memcpy(temp_filepath,filepath,strlen(filepath)+1);
    dirpath = dirname(temp_filepath);

    type = getInputFileType(filepath);
    if (type == AOF_RESP) {
        checkOldStyleAof(filepath,fix,0);
    } else if (type == AOF_RDB_PREAMBLE) {
        checkOldStyleAof(filepath,fix,1);
    } else if (type == AOF_MULTI_PART) {
        checkMultiPartAof(dirpath,filepath,fix);
    }

    exit(0);
}