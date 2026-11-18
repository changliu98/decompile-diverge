int ini_internal_property_index(struct ini_t *ini, int section, int property)
{
  int i; int p;
  if (ini == ((void *)0))
    return -1;
  if (section < 0 || section >= ini->section_count)
    return -1;
  for (i = p = 0; i < ini->property_count; i++)
  {
    if (ini->properties[i].section == section)
    {
      if (p == property)
        return i;
      p++;
    }
  }
  return -1;
}