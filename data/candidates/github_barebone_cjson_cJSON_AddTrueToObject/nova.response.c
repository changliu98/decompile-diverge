static struct demangle_component *
cJSON_AddTrueToObject (struct d_info *di, const char *s)
{
  struct demangle_component *p;
  size_t len;

  p = d_make_empty (di);
  if (! cplus_demangle_fill_name (di, s, p, &dn_ident, NULL))
    {
      free (p);
      p = NULL;
    }
  len = strlen (s);
  if (p!= NULL)
    d_grow_number (di, len);
  return p;
}