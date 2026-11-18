static char *parse_die(char *buf, char *buf_end, struct die_info *parent,
         struct abbrev_info *ab, struct cu_info *cu, struct die_info *die,
         char *debug_str, size_t debug_str_len, unsigned char big_endian)
{
 char *comp_dir = NULL;
 size_t line_info_offset = -1;
 size_t i;

 for (i = 0;; i++) {
  if (i >= ab->num_attr - 1)
   break;

  memset(&die->attr[i], 0, sizeof(struct attr_info));
  buf = parse_attr_value(buf, buf_end - buf, &ab->attr[i],
           &die->attr[i], cu, debug_str, debug_str_len,
           big_endian & 1);

  struct attr_info *attr = &die->attr[i];

  if (attr->name == 27 && (attr->form == 14 ||
      attr->form == 8) && attr->val.string)
   comp_dir = attr->val.string;

  if (attr->name == 16) {
   if (attr->form == 2)
    line_info_offset = attr->val.u64;
   else if (attr->form == 9)
    line_info_offset = attr->val.u64;
   continue;
  }

  die->num_attr++;
 }

 if (comp_dir && line_info_offset != -1) {
  char *dup_comp_dir = strdup(comp_dir);
  if (!dup_comp_dir)
   goto out;

  if (!(ht_up_insert(parent->line_info, line_info_offset, dup_comp_dir) & 1))
   free(dup_comp_dir);
 }
out:
 return buf;
}