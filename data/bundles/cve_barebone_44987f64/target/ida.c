int __cdecl __noreturn redis_check_aof_main(int argc, char **argv)
{
  size_t v2; // rax
  char *src; // [rsp+8h] [rbp-1058h]
  input_file_type InputFileType; // [rsp+18h] [rbp-1048h]
  char *endptr; // [rsp+20h] [rbp-1040h] BYREF
  sds version; // [rsp+28h] [rbp-1038h]
  int fix; // [rsp+34h] [rbp-102Ch]
  char *dirpath; // [rsp+38h] [rbp-1028h]
  char temp_filepath[4097]; // [rsp+40h] [rbp-1020h] BYREF
  char *filepath; // [rsp+1048h] [rbp-18h]
  char **argva; // [rsp+1050h] [rbp-10h]
  int argca; // [rsp+105Ch] [rbp-4h]

  argca = argc;
  argva = argv;
  fix = 0;
  if ( argc >= 2 )
  {
    if ( argca == 2 )
    {
      if ( !strcmp(argva[1], "-v") || !strcmp(argva[1], "--version") )
      {
        version = getVersion();
        printf("redis-check-aof %s\n", version);
        sdsfree(version);
        exit(0);
      }
      filepath = argva[1];
      goto LABEL_19;
    }
    if ( argca == 3 )
    {
      if ( !strcmp(argva[1], "--fix") )
      {
        filepath = argva[2];
        fix = 1;
        goto LABEL_19;
      }
    }
    else if ( argca == 4 && !strcmp(argva[1], "--truncate-to-timestamp") )
    {
      *__errno_location() = 0;
      to_timestamp = strtol(argva[2], &endptr, 10);
      if ( *__errno_location() || *endptr )
      {
        printf("Invalid timestamp, aborting...\n");
        exit(1);
      }
      filepath = argva[3];
LABEL_19:
      src = filepath;
      v2 = strlen(filepath);
      memcpy(temp_filepath, src, v2 + 1);
      dirpath = dirname(temp_filepath);
      InputFileType = getInputFileType(filepath);
      if ( InputFileType )
      {
        if ( InputFileType == AOF_RDB_PREAMBLE )
        {
          checkOldStyleAof(filepath, fix, 1);
        }
        else if ( InputFileType == AOF_MULTI_PART )
        {
          checkMultiPartAof(dirpath, filepath, fix);
        }
      }
      else
      {
        checkOldStyleAof(filepath, fix, 0);
      }
      exit(0);
    }
  }
  printf("Usage: %s [--fix|--truncate-to-timestamp $timestamp] <file.manifest|file.aof>\n", *argva);
  exit(1);
}