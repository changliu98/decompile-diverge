static const unsigned char *parse_die(const unsigned char *start,
                                      const unsigned char *end,
                                      Dwarf *dw, Dwarf_Die *die,
                                      Dwarf_Debug *dbg, Dwarf_Attribute *attrs,
                                      const unsigned char *abbrev_offsets,
                                      unsigned abbrev_count, bool is_info) {
  const char *name = NULL;
  Dwarf_Unsigned tag = -1;
  for (size_t i = 0; i < die->at_num - 1; i++) {
    memset(&attrs->ar_attribute[i], 0, sizeof(attrs->ar_attribute[i]));
    start = parse_attr_value(start, end - start, &die->at_attribute[i],
                             &attrs->ar_attribute[i], dbg, abbrev_offsets,
                             abbrev_count, is_info);
    Dwarf_Attribute *a = &attrs->ar_attribute[i];
    if (a->ar_attribute_form == 0x1b &&
        (a->ar_attribute_form_class == 0x0e ||
         a->ar_attribute_form_class == 0x08) &&
        a->ar_attribute_at_value) {
      name = a->ar_u.ar_u_name;
    }
    if (a->ar_attribute_form == 0x10) {
      if (a->ar_attribute_form_target == DW_FORM_data1) {
        tag = a->ar_attribute_at_value;
      } else if (a->ar_attribute_form_target == DW_FORM_ref1) {
        tag = a->ar_attribute_at_value;
      }
    }
    attrs->ar_n_attrs++;
  }
  if (name && tag != -1) {
    char *name_copy = strdup(name);
    if (name_copy) {
      if (ht_up_insert(dw->dw_tag_ht, tag, name_copy) == NULL) {
        free(name_copy);
      }
    }
  }
  return start;
}