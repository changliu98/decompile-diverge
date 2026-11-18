MOBI_RET mobi_reconstruct_infl(char *infl, const MOBIPdbRecord *pdb,
                               const MOBIIndxEntry *entry) {
  const char *infl_prefix = entry->infl;
  unsigned int *tag_array = NULL;
  size_t tag_array_len = mobi_get_indxentry_tagarray(&tag_array, entry, 42);
  if (tag_array_len == 0 || tag_array == NULL) {
    return 0;
  }
  const char *infl_start = "<idx:infl>";
  const char *infl_end = "</idx:infl>";
  const char *infl_entry = "<idx:iform%s value=\"%s\"/>";
  strcpy(infl, infl_start);
  size_t infl_start_len = strlen(infl_start) + strlen(infl_end);
  size_t infl_len = infl_start_len;
  size_t infl_prefix_len = strlen(infl_prefix);
  if (infl_prefix_len > 500) {
    return 3;
  }
  if (pdb->cncx == NULL) {
    return 3;
  }
  for (size_t i = 0; i < tag_array_len; i++) {
    size_t tag_index = tag_array[i];
    if (tag_index >= pdb->rec_count) {
      return 3;
    }
    unsigned int *tag_name_array;
    unsigned int tag_name_array_len = mobi_get_indxentry_tagarray(
        &tag_name_array, &pdb->records[tag_index], 5);
    unsigned int *tag_infl_array;
    unsigned int tag_infl_array_len = mobi_get_indxentry_tagarray(
        &tag_infl_array, &pdb->records[tag_index], 26);
    if (tag_name_array_len != tag_infl_array_len) {
      return 3;
    }
    for (size_t j = 0; j < tag_infl_array_len; j++) {
      char name_attr[500 + 1];
      name_attr[0] = '\0';
      char *name = mobi_get_cncx_string(pdb->cncx, tag_name_array[j]);
      if (name == NULL) {
        return 7;
      }
      if (strlen(name) > 0) {
        snprintf(name_attr, 500, " name=\"%s\"", name);
      }
      free(name);
      char infl_value[500 + 1];
      memset(infl_value, 0, 500 + 1);
      const char *infl_str = pdb->records[tag_infl_array[j]].infl;
      memcpy(infl_value, infl_prefix, infl_prefix_len);
      int infl_value_len = infl_prefix_len;
      MOBI_RET ret =
          mobi_decode_infl(infl_value, &infl_value_len, infl_str);
      if (ret != 0) {
        return ret;
      }
      if (infl_value_len > 0) {
        char infl_entry_str[500 + 1];
        int len = snprintf(infl_entry_str, 500, infl_entry, name_attr,
                           infl_value);
        if (len <= 500) {
          infl_len += strlen(infl_entry_str);
          if (infl_len > 25000) {
            return 1;
          }
          strcat(infl, infl_entry_str);
        }
      }
    }
  }
  if (infl_len != infl_start_len) {
    strcat(infl, infl_end);
  } else {
    infl[0] = '\0';
  }
  return 0;
}