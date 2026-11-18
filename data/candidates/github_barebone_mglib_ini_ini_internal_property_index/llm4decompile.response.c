int ini_internal_property_index(ini_t *ini, int section, int property) {
 int i, p;

 if (ini == NULL || section < 0 || section >= ini->section_count)
  return -1;

 p = 0;
 for (i = 0; i < ini->property_count; i++) {
  if (ini->properties[i].section == section) {
   if (p == property)
    return i;
   p++;
  }
 }

 return -1;
}