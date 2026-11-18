void __cdecl listdir(unsigned int depth, int f, void *const tls_fd, const char *name)
{
  char subdir[4097]; // Replaces the bizarre alloca and obfuscated stack checks
  PureFileInfo *r;
  PureFileInfo *s;
  char *names;
  PureFileInfo *dir;

  // Early exit if depth or file count limits are exceeded
  if (depth >= max_ls_depth || matches >= (unsigned int)max_ls_files)
    return;

  dir = sreaddir(&names);
  if (!dir)
  {
    addreply(226, "Sorry, we were unable to read [%s]", name);
    return;
  }

  // Process files in the current directory
  for (s = dir; s->name_offset != -1LL; ++s)
  {
    int d = 0;
    char *entry_name = &(*s->names_pnt)[s->name_offset];

    if (entry_name[0] != '.' || opt_a)
    {
      if (entry_name[0] != '.' || (entry_name[1] && (entry_name[1] != '.' || entry_name[2])))
      {
        // Regular file or allowed hidden file
        d = listfile(s, 0LL);
      }
      else
      {
        // "." or ".." directory entry
        listfile(s, 0LL);
      }
    }

    // If listing failed (or skipped), mark entry as invalid
    if (!d)
      s->name_offset = -1LL;
  }

  outputfiles(f, tls_fd);

  // Recursively process subdirectories if -R option is set
  if (opt_R)
  {
    for (r = dir; r != s; ++r)
    {
      if (r->name_offset != -1LL && !chdir(&(*r->names_pnt)[r->name_offset]))
      {
        if (snprintf(subdir, sizeof(subdir), "%s/%s", name, &(*r->names_pnt)[r->name_offset]) < (int)sizeof(subdir))
        {
          wrstr(f, tls_fd, "\r\n\r\n");
          wrstr(f, tls_fd, subdir);
          wrstr(f, tls_fd, ":\r\n\r\n");
          listdir(depth + 1, f, tls_fd, subdir);
        }

        if (matches >= (unsigned int)max_ls_files)
          break;

        // Return to the parent directory
        if (chdir("..") && (chdir(wd) || chdir(name)))
        {
          die(421, 3, "chdir: %s", strerror(errno));
        }
      }
    }
  }

  free(names);
  free(dir);
}