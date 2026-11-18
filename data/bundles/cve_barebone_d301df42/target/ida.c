int __cdecl call_backend(char *uri, int argc, char **argv, char *filename)
{
  int *v4; // rax
  char *v5; // rax
  struct _IO_FILE *stream; // [rsp+28h] [rbp-10498h]
  const char *v8; // [rsp+30h] [rbp-10490h]
  int retval; // [rsp+6Ch] [rbp-10454h]
  char cmdline[65536]; // [rsp+70h] [rbp-10450h] BYREF
  char *ptr; // [rsp+10078h] [rbp-448h]
  char scheme[1024]; // [rsp+10080h] [rbp-440h] BYREF
  const char *cups_serverbin; // [rsp+10488h] [rbp-38h]
  char *filenamea; // [rsp+10490h] [rbp-30h]
  char **argva; // [rsp+10498h] [rbp-28h]
  int argca; // [rsp+104A4h] [rbp-1Ch]
  char *uria; // [rsp+104A8h] [rbp-18h]

  uria = uri;
  argca = argc;
  argva = argv;
  filenamea = filename;
  strncpy(scheme, uri, 0x3FFuLL);
  if ( strlen(uria) > 0x3FF )
    scheme[1023] = 0;
  ptr = strchr(scheme, 58);
  if ( ptr )
    *ptr = 0;
  cups_serverbin = getenv("CUPS_SERVERBIN");
  if ( !cups_serverbin )
    cups_serverbin = "/usr/lib/cups";
  if ( !strncasecmp(uria, "file:", 5uLL) || *uria == 47 )
  {
    fprintf(stderr, "ERROR: beh: Direct output into a file not supported.\n");
    exit(1);
  }
  if ( argca == 6 )
    v8 = "1";
  else
    v8 = argva[4];
  snprintf(
    cmdline,
    0x10000uLL,
    "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s",
    cups_serverbin,
    scheme,
    argva[1],
    argva[2],
    argva[3],
    v8,
    argva[5],
    filenamea);
  setenv("DEVICE_URI", uria, 1);
  fprintf(stderr, "DEBUG: beh: Executing backend command line \"%s\"...\n", cmdline);
  fprintf(stderr, "DEBUG: beh: Using device URI: %s\n", uria);
  retval = system(cmdline) >> 8;
  if ( retval == -1 )
  {
    stream = stderr;
    v4 = __errno_location();
    v5 = strerror(*v4);
    fprintf(stream, "ERROR: Unable to execute backend command line: %s\n", v5);
  }
  return retval;
}