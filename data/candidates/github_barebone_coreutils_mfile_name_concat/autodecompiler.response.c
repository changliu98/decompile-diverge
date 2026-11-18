char *
mfile_name_concat (char *directory, char *file, char **last_slash)
{
  char *concatenated;
  char *last_component ();
  size_t dirlen, dirlen2, filelen, slashlen;
  char *dp, *fp, *cp;

  dp = last_component (directory);
  dirlen = base_len (dp);

  dirlen2 = dp - directory + dirlen;

  filelen = strlen (file);
  slashlen = ((dirlen == 0 && file[0] == '/')
       || (directory[dirlen2 - 1] != '/'
    && file[0] != '/')) ? 1 : 0;

  concatenated = (char *)malloc (dirlen2 + slashlen + filelen + 1);
  if (concatenated == 0)
    {
      char *result;
      result = 0;
      return result;
    }

  cp = concatenated;
  memcpy (cp, directory, dirlen2);
  cp += dirlen2;
  *cp = '/';
  cp += slashlen;
  if (last_slash)
    *last_slash = cp;
  fp = file;
  memcpy (cp, fp, filelen);
  cp += filelen;
  *cp = '\0';
  return concatenated;
}