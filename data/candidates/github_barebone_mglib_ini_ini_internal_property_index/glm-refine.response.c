int __cdecl ini_internal_property_index(const ini_t *ini, int section, int property)
{
  if (ini && section >= 0 && section < ini->section_count)
  {
    int property_index = 0;
    for (int i = 0; i < ini->property_count; ++i)
    {
      if (ini->properties[i].section == section)
      {
        if (property_index == property)
          return i;
        property_index++;
      }
    }
  }
  return -1;
}