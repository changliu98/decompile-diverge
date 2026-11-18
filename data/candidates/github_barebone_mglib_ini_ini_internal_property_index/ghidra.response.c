int ini_internal_property_index(ini_t *ini,int section,int property)

{
  int p;
  int i;
  int property_local;
  int section_local;
  ini_t *ini_local;
  
  if (((ini != (ini_t *)0x0) && (-1 < section)) && (section < ini->section_count)) {
    p = 0;
    for (i = 0; i < ini->property_count; i = i + 1) {
      if (ini->properties[i].section == section) {
        if (p == property) {
          return i;
        }
        p = p + 1;
      }
    }
  }
  return -1;
}