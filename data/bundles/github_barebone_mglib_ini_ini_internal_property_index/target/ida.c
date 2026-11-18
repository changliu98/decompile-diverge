int __cdecl ini_internal_property_index(const ini_t *ini, int section, int property)
{
  int p; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  if ( ini && section >= 0 && section < ini->section_count )
  {
    p = 0;
    for ( i = 0; i < ini->property_count; ++i )
    {
      if ( ini->properties[i].section == section )
      {
        if ( p == property )
          return i;
        ++p;
      }
    }
  }
  return -1;
}