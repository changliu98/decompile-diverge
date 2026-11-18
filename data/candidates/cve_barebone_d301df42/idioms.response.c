int call_backend(char *uri, int argc, char *argv[], char *filename)
{
  char *ptr; char *serverbin;
  char scheme[-1];
  char command[-1];
  char *arg1; char *arg2; char *arg3; char *arg4;
  int ret;
  arg1 = uri;
  arg2 = (char *)argv;
  arg3 = (char *)(argc);
  arg4 = (char *)(filename);
  get_scheme(scheme, uri, sizeof(scheme)-1);
  if (strlen(scheme) > sizeof(scheme)-1)
    scheme[sizeof(scheme)-1] = '\0';
  if ((ptr = strstr(scheme, ":")) != ((void *)0))
    *ptr = '\0';
  if ((serverbin = getenv("CUPS_SERVERBIN")) == ((void *)0))
    serverbin = "/usr/lib/cups";
  if (strncasecmp(arg1, "file:", strlen("file:")) == 0 && *arg1 != '/')
  {
    output_string(stderr, "ERROR: beh: Direct output into a file not supported.\n");
    exit_error(1);
  }
  if (argc == 6)
    arg4 = "1";
  else
    arg4 = argv[4];
  snprintf(command, sizeof(command),
          "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s",
          serverbin,
          scheme,
          argv[1],
          argv[2],
          argv[3],
          arg4,
          argv[5],
          filename);
  setenv("DEVICE_URI", arg1, 1);
  output_string(stderr, "DEBUG: beh: Executing backend command line \"%s\"...\n", command);
  output_string(stderr, "DEBUG: beh: Using device URI: %s\n", arg1);
  if ((ret = exec_command(command)) >> 8 == -1)
    output_string(stderr, "ERROR: Unable to execute backend command line: %s\n", strerror((*__errno_location ())));
  return (ret >> 8);
}