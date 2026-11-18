int redis_check_aof_main(int argc,char **argv)

{
  int iVar1;
  input_file_type iVar2;
  int *piVar3;
  size_t sVar4;
  input_file_type type;
  char *endptr;
  sds version;
  int fix;
  char *dirpath;
  char temp_filepath [4097];
  char *filepath;
  char **argv_local;
  int argc_local;
  
  fix = 0;
  if (argc < 2) goto LAB_001014da;
  if (argc == 2) {
    iVar1 = strcmp(argv[1],"-v");
    if ((iVar1 == 0) || (iVar1 = strcmp(argv[1],"--version"), iVar1 == 0)) {
      version = getVersion();
      printf("redis-check-aof %s\n",version);
      sdsfree(version);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    filepath = argv[1];
  }
  else if (argc == 3) {
    iVar1 = strcmp(argv[1],"--fix");
    if (iVar1 != 0) {
LAB_001014da:
      printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n",*argv
            );
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    filepath = argv[2];
    fix = 1;
  }
  else {
    if ((argc != 4) || (iVar1 = strcmp(argv[1],"--truncate-to-timestamp"), iVar1 != 0))
    goto LAB_001014da;
    piVar3 = __errno_location();
    *piVar3 = 0;
    to_timestamp = strtol(argv[2],&endptr,10);
    piVar3 = __errno_location();
    if ((*piVar3 != 0) || (*endptr != '\0')) {
      printf("Invalid timestamp, aborting...\n");
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    filepath = argv[3];
  }
  sVar4 = strlen(filepath);
  memcpy(temp_filepath,filepath,sVar4 + 1);
  dirpath = dirname(temp_filepath);
  iVar2 = getInputFileType(filepath);
  if (iVar2 == AOF_RESP) {
    checkOldStyleAof(filepath,fix,0);
  }
  else if (iVar2 == AOF_RDB_PREAMBLE) {
    checkOldStyleAof(filepath,fix,1);
  }
  else if (iVar2 == AOF_MULTI_PART) {
    checkMultiPartAof(dirpath,filepath,fix);
  }
                    /* WARNING: Subroutine does not return */
  exit(0);
}