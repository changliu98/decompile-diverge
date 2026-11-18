int __cdecl call_backend(char *uri, int argc, char **argv, char *filename)
{
  char cmdline[65536];
  char scheme[1024];
  const char *cups_serverbin;
  const char *copies;
  int retval;

  // Extract the URI scheme (e.g., "socket" from "socket://...")
  strncpy(scheme, uri, 0x3FF);
  if (strlen(uri) > 0x3FF)
    scheme[1023] = '\0';
  
  char *colon = strchr(scheme, ':');
  if (colon)
    *colon = '\0';

  // Determine backend binary directory
  cups_serverbin = getenv("CUPS_SERVERBIN");
  if (!cups_serverbin)
    cups_serverbin = "/usr/lib/cups";

  // Security/Sanity check: Disallow direct file output
  if (!strncasecmp(uri, "file:", 5) || *uri == '/')
  {
    fprintf(stderr, "ERROR: beh: Direct output into a file not supported.\n");
    exit(1);
  }

  // Determine the number of copies argument
  if (argc == 6)
    copies = "1";
  else
    copies = argv[4];

  // Construct the command line to call the actual CUPS backend
  snprintf(
    cmdline,
    0x10000,
    "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s",
    cups_serverbin,
    scheme,
    argv[1],
    argv[2],
    argv[3],
    copies,
    argv[5],
    filename);

  // Export the original URI to the environment for the backend
  setenv("DEVICE_URI", uri, 1);

  fprintf(stderr, "DEBUG: beh: Executing backend command line \"%s\"...\n", cmdline);
  fprintf(stderr, "DEBUG: beh: Using device URI: %s\n", uri);

  // Execute the backend and extract the exit status
  retval = system(cmdline) >> 8;

  if (retval == -1)
  {
    fprintf(stderr, "ERROR: Unable to execute backend command line: %s\n", strerror(errno));
  }

  return retval;
}