int __cdecl parse_device(dev_t *pdev, archive *a, char *val)
{
  const char *error = NULL;
  dev_t result;
  pack_t *pack;
  int argc = 0;
  char *dev;
  char *p;
  uint64_t numbers[3];

  memset(pdev, 0, sizeof(dev_t));

  // Check if the string contains a comma
  dev = strchr(val, ',');
  if (!dev)
  {
    result = mtree_atol(&val);
    *pdev = result;
    return 0;
  }

  // Split the string at the first comma
  *dev++ = '\0';

  // Look up the device packing format by name (before the comma)
  pack = pack_find(val);
  if (!pack)
  {
    archive_set_error(a, 22, "Unknown format `%s'", val);
    return -20;
  }

  // Parse the comma-separated arguments
  while (1)
  {
    p = la_strsep(&dev, ",");
    if (!p)
      break;

    if (!*p)
    {
      archive_set_error(a, 22, "Missing number");
      return -20;
    }

    numbers[argc++] = mtree_atol(&p);
    if (argc > 3)
    {
      archive_set_error(a, 22, "Too many arguments");
      return -20;
    }
  }

  if (argc < 2)
  {
    archive_set_error(a, 22, "Not enough arguments");
    return -20;
  }

  // Execute the packing function to compute the device ID
  result = pack(argc, numbers, &error);
  if (error)
  {
    archive_set_error(a, 22, "%s", error);
    return -20;
  }

  *pdev = result;
  return 0;
}