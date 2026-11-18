struct r_bin_java_attr_info *r_bin_java_inner_classes_attr_new(struct r_bin_java_obj *bin, unsigned char *buffer, unsigned long sz, unsigned long offset)
{
  struct r_bin_java_inner_classes_attr *icattr;
  struct r_bin_java_cp_type *item;
  struct r_bin_java_attr_info *attr;
  unsigned int i;
  unsigned long curpos;
  unsigned long curpos2;
  attr = r_bin_java_default_attr_new(bin, buffer, sz, offset);
  if (!attr)
    return ((void *)0);
  attr->type = R_BIN_JAVA_ATTR_INNER_CLASSES;
  attr->info.inner_classes_attr.number_of_classes = ((buffer[offset + 3] << 8) | (buffer[offset + 2]));
  offset += 4 - 2;
  attr->info.inner_classes_attr.classes = r_list_newf((RListFree) r_bin_java_inner_classes_attr_entry_free);
  for (i = 0; i < attr->info.inner_classes_attr.number_of_classes; i++) {
    curpos = offset + i * sizeof(struct r_bin_java_inner_classes_attr_entry);
    if (curpos + sizeof(struct r_bin_java_inner_classes_attr_entry) > sz) {
      fprintf(stderr, "Invalid amount of inner classes\n");
      break;
    }
    icattr = (struct r_bin_java_inner_classes_attr *) calloc(1, sizeof(struct r_bin_java_inner_classes_attr));
    if (!icattr)
      break;
    icattr->inner_class_info_idx = ((buffer[curpos + 0] << 8) | (buffer[curpos + 1]));
    curpos2 = curpos + 2;
    icattr->outer_class_info_idx = ((buffer[curpos2 + 0] << 8) | (buffer[curpos2 + 1]));
    curpos2 += 2;
    icattr->inner_name_idx = ((buffer[curpos2 + 0] << 8) | (buffer[curpos2 + 1]));
    icattr->inner_class_access_flags = ((buffer[curpos2 + 2] << 8) | (buffer[curpos2 + 1]));
    curpos2 += 2;
    icattr->flags_str = retrieve_class_method_access_string(icattr->inner_class_access_flags);
    icattr->file_offset = curpos;
    icattr->size = sizeof(struct r_bin_java_inner_classes_attr_entry);
    item = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_name_idx);
    if (!item)
      fprintf(stderr, "BINCPLIS IS HULL %d\n", icattr->inner_name_idx);
    icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, item);
    if (!icattr->name) {
      item = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_class_info_idx);
      if (!item)
        fprintf(stderr, "BINCPLIST IS NULL %d\n", icattr->inner_class_info_idx);
      icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, item);
      if (!icattr->name) {
        icattr->name = r_str_dup(((void *)0), "NULL");
        fprintf(stderr, "r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n", icattr->inner_name_idx);
        free(icattr);
        break;
      }
    }
    r_list_append(attr->info.inner_classes_attr.classes, icattr);
  }
  attr->size = offset;
  return attr;
}