static enum MOBI_RET mobi_idx_infl(char *outstring, struct MOBIIndx *infl, struct MOBIIndexEntry *orth_entry)
{
  char *out = outstring;
  char *label = orth_entry->label;
  char infl_tag[501];
  char name_attr[501];
  char *start_tag = "<idx:infl>";
  char *end_tag = "</idx:infl>";
  char *iform_tag = "<idx:iform%s value=\"%s\"/>";
  char *group_name;
  char *label_utf8;
  unsigned int *infl_groups = ((void *)0);
  unsigned int infl_count = mobi_idx_get_infl_groups(&infl_groups, orth_entry, sizeof(orth_entry->label));
  if (infl_count == 0 || infl_groups == ((void *)0))
    return MOBI_RET_OK;
  mobi_idx_putstring(out, start_tag);
  unsigned long startlen = mobi_idx_getlen(start_tag);
  unsigned long endlen = mobi_idx_getlen(end_tag);
  unsigned long len = startlen + endlen;
  label_utf8 = (char *)orth_entry->label;
  unsigned long label_len = strlen(label_utf8);
  if (label_len > 500)
    return MOBI_RET_ERR_LABEL_TOO_LONG;
  if (infl->cncx_record == ((void *)0))
    return MOBI_RET_ERR_NO_CNCX;
  for (unsigned long i = 0; i < infl_count; i++) {
    unsigned long offset = infl_groups[i];
    if (offset >= infl->entries_count)
      return MOBI_RET_ERR_INDEX_OUTOFBOUNDS;
    unsigned int *groups = ((void *)0);
    unsigned int group_count = mobi_idx_get_infl_groups(&groups, &infl->entries[offset], sizeof(struct MOBIIndexEntry));
    unsigned int *parts = ((void *)0);
    unsigned int part_count = mobi_idx_get_infl_groups(&parts, &infl->entries[offset], sizeof(struct MOBIIndexEntry) + 16);
    if (group_count != part_count)
      return MOBI_RET_ERR_INDEX_INCONSISTENT;
    for (unsigned long j = 0; j < part_count; j++) {
      name_attr[0] = '\0';
      group_name = mobi_idx_get_group_name(infl->cncx_record, groups[j]);
      if (group_name == ((void *)0))
        return MOBI_RET_ERR_NO_CNCX;
      if (mobi_idx_getlen(group_name) > 0)
        mobi_idx_putstring(name_attr, sizeof(name_attr), " name=\"%s\"", group_name);
      mobi_idx_putstring(group_name);
      char decoded[501];
      mobi_idx_zero(decoded, sizeof(decoded));
      char *infl_utf8 = (char *)infl->entries[parts[j]].label;
      mobi_idx_putstring(decoded, label_utf8, label_len);
      int decoded_len = label_len;
      enum MOBI_RET ret = mobi_idx_decode(decoded, &decoded_len, infl_utf8);
      if (ret != MOBI_RET_OK)
        return ret;
      if (decoded_len > 0) {
        if (mobi_idx_putstring(infl_tag, sizeof(infl_tag), iform_tag, name_attr, decoded) < (int)sizeof(infl_tag)) {
          len += mobi_idx_getlen(infl_tag);
          if (len > (10000 + 1000))
            return MOBI_RET_ERR_INDEX_TOO_LONG;
          mobi_idx_putstring(out, infl_tag);
        }
      }
    }
  }
  if (len != startlen)
    mobi_idx_putstring(out, end_tag);
  else
    out[0] = '\0';
  return MOBI_RET_OK;
}