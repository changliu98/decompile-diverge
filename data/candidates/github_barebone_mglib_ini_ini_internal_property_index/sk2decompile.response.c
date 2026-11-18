static int ini_internal_property_index(ini_section_t *section, int key,
                                       int index) {
  int i, j;
  if (section && (key >= 0) && (key < section->key_count)) {
    j = 0;
    for (i = 0; i < section->property_count; i++) {
      if (section->properties[i].key == key) {
        if (j == index) return i;
        j++;
      }
    }
  }
  return -1;
}