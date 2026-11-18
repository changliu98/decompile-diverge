int redis_check_aof_main(int argc, char **argv) {
    int fix = 0;
    char *filename;

    if (argc < 3) {
        usage();
    } else if (argc == 2) {
        if (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version")) {
            sds version = getVersion();
            printf("redis-check-aof %s\n", version);
            sdsfree(version);
            exit(0);
        }
        filename = argv[1];
    } else if (argc == 3) {
        if (!strcmp(argv[1],"--fix")) {
            filename = argv[2];
            fix = 1;
        } else if (!strcmp(argv[1],"--truncate-to-timestamp")) {
            char *eptr;
            ___errno_location() = 0;
            to_timestamp = strtol(argv[2],&eptr,10);
            if (___errno_location() != 0 || eptr[0] != '\0') {
                printf("Invalid timestamp, aborting...\n");
                exit(1);
            }
            filename = argv[3];
        } else {
            usage();
        }
    } else if (argc == 4) {
        if (!strcmp(argv[1],"--truncate-to-timestamp")) {
            char *eptr;
            ___errno_location() = 0;
            to_timestamp = strtol(argv[2],&eptr,10);
            if (___errno_location() != 0 || eptr[0] != '\0') {
                printf("Invalid timestamp, aborting...\n");
                exit(1);
            }
            filename = argv[3];
        } else {
            usage();
        }
    } else {
        usage();
    }

    while(1) {
        char workdir[4096];
        char *base;
        char *dir;
        int filetype;

        /* Get the AOF filename in a portable way. In theory there are only
         * two possible files: a file named 'appendonly.aof' which is the
         * old style file, and a directory named 'appendonly.aof.d' which is
         * the new style directory. However there are other possible files
         * which we can't ignore: for instance 'appendonly.aof.bak' which is
         * an AOF file created by a crash, or 'appendonly.aof.tmp' which is
         * an AOF temporary file. */
        char *aof_filename = filename;
        size_t aof_filename_len = strlen(aof_filename);
        memcpy(workdir,aof_filename,aof_filename_len+1);
        dir = dirname(workdir);
        base = basename(aof_filename);

        filetype = getInputFileType(aof_filename);
        if (filetype == 0) {
            checkOldStyleAof(aof_filename,fix,0);
        } else if (filetype == 1) {
            checkOldStyleAof(aof_filename,fix,1);
        } else if (filetype == 2) {
            checkMultiPartAof(dir,aof_filename,fix);
        } else {
            printf("Unknown input file type detected.\n");
            exit(1);
        }
        exit(0);
    }
}