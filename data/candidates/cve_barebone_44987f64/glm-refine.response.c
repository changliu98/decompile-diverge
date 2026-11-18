int __cdecl __noreturn redis_check_aof_main(int argc, char **argv)
{
  char *endptr;
  sds version;
  int fix = 0;
  char *filepath = NULL;
  char temp_filepath[4097];

  if (argc >= 2)
  {
    if (argc == 2)
    {
      if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
      {
        version = getVersion();
        printf("redis-check-aof %s\n", version);
        sdsfree(version);
        exit(0);
      }
      filepath = argv[1];
    }
    else if (argc == 3)
    {
      if (!strcmp(argv[1], "--fix"))
      {
        filepath = argv[2];
        fix = 1;
      }
    }
    else if (argc == 4 && !strcmp(argv[1], "--truncate-to-timestamp"))
    {
      *__errno_location() = 0;
      to_timestamp = strtol(argv[2], &endptr, 10);
      if (*__errno_location() || *endptr)
      {
        printf("Invalid timestamp, aborting...\n");
        exit(1);
      }
      filepath = argv[3];
    }

    // If a valid filepath was assigned from any of the argument branches above
    if (filepath)
    {
      // dirname() may modify its argument, so we copy the path to a temporary buffer
      memcpy(temp_filepath, filepath, strlen(filepath) + 1);
      char *dirpath = dirname(temp_filepath);
      
      input_file_type input_file_type = getInputFileType(filepath);
      
      if (input_file_type == AOF_FILE_TYPE_BASE)
      {
        checkOldStyleAof(filepath, fix, 0);
      }
      else if (input_file_type == AOF_RDB_PREAMBLE)
      {
        checkOldStyleAof(filepath, fix, 1);
      }
      else if (input_file_type == AOF_MULTI_PART)
      {
        checkMultiPartAof(dirpath, filepath, fix);
      }
      
      exit(0);
    }
  }

  printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n", argv[0]);
  exit(1);
}