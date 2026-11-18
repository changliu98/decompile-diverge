char *
last_component (char const *name)
{
  char const *base = name + FILE_SYSTEM_PREFIX_LEN (name);
  while (ISSLASH (*base))
    base++;

  bool last_was_slash = false;
  for (char const *p = base; *p; p++)
    {
      if (ISSLASH (*p))
        last_was_slash = true;
      else if (last_was_slash)
        {
          base = p;
          last_was_slash = false;
        }
    }

  return (char *) base;
}