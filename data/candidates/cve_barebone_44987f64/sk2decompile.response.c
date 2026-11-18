int redis_check_aof_main(int argc, char **argv) {
  char *filename;
  char dirnamebuf[4096];
  char *dirname;
  input_file_type_t input_file_type;
  int fix = 0;
  char *ptr;
  if (argc < 2) {
  } else if (argc == 2) {
    if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
      input_file_type_t version = getVersion();
      printf("redis-check-aof %s\n", version);
      sdsfree(version);
      exit(0);
    }
    filename = argv[1];
  } else if (argc == 3) {
    if (!strcmp(argv[1], "--fix")) {
      filename = argv[2];
      fix = 1;
    } else {
    }
  } else if (argc == 4) {
    char *endptr;
    if (!strcmp(argv[1], "--truncate-to-timestamp")) {
      errno = 0;
      truncate_to_timestamp = strtol(argv[2], &endptr, 10);
      if (errno || *endptr != '\0') {
        printf("Invalid timestamp, aborting...\n");
        exit(1);
      }
      filename = argv[3];
    } else {
    }
  } else {
  }
  if (filename == NULL) {
    printf(
        "Usage: %s [--fix|--truncate-to-timestamp $timestamp] "
        "<file.manifest|file.aof>\n",
        argv[0]);
    exit(1);
  }
  memcpy(dirnamebuf, filename, strlen(filename) + 1);
  dirname = dirname(dirnamebuf);
  input_file_type = getInputFileType(filename);
  if (input_file_type == INPUT_FILE_TYPE_OLD_STYLE_AOF) {
    checkOldStyleAof(filename, fix, 0);
  } else if (input_file_type == INPUT_FILE_TYPE_OLD_STYLE_AOF_COMPRESSED) {
    checkOldStyleAof(filename, fix, 1);
  } else if (input_file_type == INPUT_FILE_TYPE_MULTI_PART_AOF) {
    checkMultiPartAof(dirname, filename, fix);
  }
  exit(0);
}