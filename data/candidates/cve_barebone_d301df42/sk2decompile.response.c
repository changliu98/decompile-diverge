static int call_backend(char *device_uri, int argc, char **argv,
                        char *output_file) {
  char command[65536];
  char backend[1024];
  char *p;
  char *serverbin;
  int status;
  strncpy(backend, device_uri, sizeof(backend) - 1);
  if (strlen(device_uri) > sizeof(backend) - 1)
    backend[sizeof(backend) - 1] = '\0';
  p = strchr(backend, ':');
  if (p) *p = '\0';
  serverbin = getenv("CUPS_SERVERBIN");
  if (!serverbin) serverbin = "/usr/lib/cups";
  if (!strncasecmp(device_uri, "file:", 5) || device_uri[0] == '/') {
    fprintf(stderr,
            "ERROR: "
            "beh: Direct output into a file not supported.\n");
    exit(1);
  }
  snprintf(command, sizeof(command),
           "%s/backend/%s '%s' '%s' '%s' '%s' '%s' %s", serverbin, backend,
           argv[1], argv[2], argv[3], (argc == 6) ? "1" : argv[4], argv[5],
           output_file);
  setenv("DEVICE_URI", device_uri, 1);
  fprintf(stderr,
          "DEBUG: "
          "beh: Executing backend command line \"%s\"...\n",
          command);
  fprintf(stderr,
          "DEBUG: "
          "beh: Using device URI: %s\n",
          device_uri);
  status = system(command) >> 8;
  if (status == -1)
    fprintf(stderr,
            "ERROR: "
            "Unable to execute backend command line: %s\n",
            strerror(errno));
  return status;
}