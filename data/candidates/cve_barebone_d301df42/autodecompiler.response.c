static int
call_backend(char *device_uri,
                int argc,
                char **argv,
                char *printer)
{
  char buffer[65536];
  char scheme[256];
  char *pos;
  char *backend_dir;
  int ret;


  strncpy(scheme, device_uri, sizeof(scheme) - 1);
  if (strlen(device_uri) >= sizeof(scheme) - 1)
    scheme[sizeof(scheme) - 1] = '\0';

  pos = strchr(scheme, ':');
  if (pos)
    *pos = '\0';


  backend_dir = getenv("CUPS_SERVERBIN");
  if (!backend_dir)
    backend_dir = "/usr/lib/cups";



  if (!strncasecmp(device_uri, "file:", 5) || device_uri[0] == '/')
  {
    fprintf(stderr, "ERROR: beh: Direct output into a file not supported.\n");
    exit(1);
  }

  snprintf(buffer, sizeof(buffer),
           "%s/backend/%s '%s' '%s' '%s' '%s' '%s' '%s' '%s' %s",
           backend_dir, scheme, argv[1], argv[2], argv[3],
           (argc == 6 ? "1" : argv[4]), printer, argv[5],
           (argc == 6 ? argv[4] : argv[6]),
           (argc == 6 ? "0" : argv[7]));

  setenv("DEVICE_URI", device_uri, 1);

  fprintf(stderr, "DEBUG: beh: Executing backend command line \"%s\"...\n", buffer);
  fprintf(stderr, "DEBUG: beh: Using device URI: %s\n", device_uri);

  ret = system(buffer) >> 8;

  if (ret == -1)
    fprintf(stderr, "ERROR: Unable to execute backend command line: %s\n", strerror(*___errno_location()));

  return(ret);
}