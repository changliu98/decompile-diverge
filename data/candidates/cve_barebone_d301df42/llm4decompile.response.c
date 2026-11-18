int
call_backend(const char *device_uri,
             int argc,
             char **argv,
             const char *filename)
{
  int status;
  char cmdline[65536];
  char scheme[1024];
  char *ptr;
  const char *cups_serverbin;


  strncpy(scheme, device_uri, sizeof(scheme) - 1);
  if (strlen(device_uri) >= sizeof(scheme))
    scheme[sizeof(scheme) - 1] = '\0';
  if ((ptr = strchr(scheme, ':')) != NULL)
    *ptr = '\0';

  if ((cups_serverbin = getenv("CUPS_SERVERBIN")) == NULL)
    cups_serverbin = "/usr/lib/cups";





  if (!strncasecmp(device_uri, "file:", 5) ||
      device_uri[0] == '/')
  {
    fprintf(PTR_stderr_00103ff8->stream,
            "ERROR: beh: Direct output into a file not supported.\n");
    exit(1);
  }

  snprintf(cmdline, sizeof(cmdline),
           "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s",
    cups_serverbin, scheme, argv[1], argv[2], argv[3],
    (argc == 6) ? "1" : argv[4], argv[5], filename);

  setenv("DEVICE_URI", device_uri, 1);

  fprintf(PTR_stderr_00103ff8->stream,
          "DEBUG: beh: Executing backend command line \"%s\"...\n",
          cmdline);
  fprintf(PTR_stderr_00103ff8->stream,
          "DEBUG: beh: Using device URI: %s\n", device_uri);

  if ((status = system(cmdline)) >> 8 == -1)
    fprintf(PTR_stderr_00103ff8->stream,
            "ERROR: Unable to execute backend command line: %s\n",
            strerror((*__errno_location ())));

  return (status >> 8);
}