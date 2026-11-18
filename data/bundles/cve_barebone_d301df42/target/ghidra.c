int call_backend(char *uri,int argc,char **argv,char *filename)

{
  FILE *__stream;
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int *piVar4;
  char *pcStack_10498;
  int retval;
  char cmdline [65536];
  char *ptr;
  char scheme [1024];
  char *cups_serverbin;
  char *filename_local;
  char **argv_local;
  int argc_local;
  char *uri_local;
  
  strncpy(scheme,uri,0x3ff);
  sVar2 = strlen(uri);
  if (0x3ff < sVar2) {
    scheme[0x3ff] = '\0';
  }
  pcVar3 = strchr(scheme,0x3a);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  cups_serverbin = getenv("CUPS_SERVERBIN");
  if (cups_serverbin == (char *)0x0) {
    cups_serverbin = "/usr/lib/cups";
  }
  iVar1 = strncasecmp(uri,"file:",5);
  if ((iVar1 != 0) && (*uri != '/')) {
    if (argc == 6) {
      pcStack_10498 = "1";
    }
    else {
      pcStack_10498 = argv[4];
    }
    snprintf(cmdline,0x10000,"%s/backend/%s \'%s\' \'%s\' \'%s\' \'%s\' \'%s\' %s",cups_serverbin,
             scheme,argv[1],argv[2],argv[3],pcStack_10498,argv[5],filename);
    setenv("DEVICE_URI",uri,1);
    fprintf(*(FILE **)PTR_stderr_00103ff8,"DEBUG: beh: Executing backend command line \"%s\"...\n",
            cmdline);
    fprintf(*(FILE **)PTR_stderr_00103ff8,"DEBUG: beh: Using device URI: %s\n",uri);
    iVar1 = system(cmdline);
    if (iVar1 >> 8 == -1) {
      __stream = *(FILE **)PTR_stderr_00103ff8;
      piVar4 = __errno_location();
      pcVar3 = strerror(*piVar4);
      fprintf(__stream,"ERROR: Unable to execute backend command line: %s\n",pcVar3);
    }
    return iVar1 >> 8;
  }
  fprintf(*(FILE **)PTR_stderr_00103ff8,"ERROR: beh: Direct output into a file not supported.\n");
                    /* WARNING: Subroutine does not return */
  exit(1);
}