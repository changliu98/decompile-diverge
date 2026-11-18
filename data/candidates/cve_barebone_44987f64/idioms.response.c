int redis_check_aof_main(int argc, char **argv)
{
    int i;
    char *file;
    char *file_path;
    char *file_path_temp;
    char *dir_path;
    char *endptr;
    int fix = 0;
    input_file_type file_type;
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    if (argc == 2) {
        if (is_equal(argv[1], "-v") || is_equal(argv[1], "--version")) {
            char *version = get_version();
            print_version("redis-check-aof %s\n", version);
            free_version(version);
            return 0;
        }
        file = argv[1];
    }
    else if (argc == 3) {
        if (is_equal(argv[1], "--fix")) {
            file = argv[2];
            fix = 1;
        }
    }
    else if (argc == 4) {
        if (is_equal(argv[1], "--truncate-to-timestamp")) {
            if (to_timestamp) {
                to_timestamp = ((void *)0);
            }
            to_timestamp = strtol(argv[2], &endptr, 10);
            if (to_timestamp == 0 || *endptr != '\0') {
                print_error("Invalid timestamp, aborting...\n");
                return 1;
            }
            file = argv[3];
        }
    }
    else {
        print_usage(argv[0]);
        return 1;
    }
    file_path = file;
    file_path_temp = (char *)malloc(sizeof(char) * (strlen(file_path)+1));
    strlcpy(file_path_temp, file_path, strlen(file_path)+1);
    dir_path = get_dir_path(file_path_temp);
    file_type = get_file_type(file_path);
    if (file_type == AOF_UNKNOWN) {
        check_aof(file_path, fix, 0);
    }
    else if (file_type == AOF_RDB_PREAMBLE) {
        check_aof(file_path, fix, 1);
    }
    else if (file_type == AOF_MULTI_PART) {
        check_multi_part(dir_path, file_path, fix);
    }
    return 0;
}