static RBinJavaAttr *r_bin_java_inner_classes_attr_new(
    RBinJava *bin, const ut8 *data, ut32 length, ut32 offset) {
  RBinJavaAttr *attr = r_bin_java_default_attr_new(bin, data, length, offset);
  if (!attr) {
    return NULL;
  }
  attr->type = 7;
  attr->u.inner_classes.num_classes = (data[3] << 8) | data[4];
  ut32 i = 8;
  attr->u.inner_classes.classes = r_list_newf((RListFree)r_bin_java_free_class);
  ut16 j;
  for (j = 0; j < attr->u.inner_classes.num_classes; j++) {
    ut32 class_offset = offset + i;
    if (i + 8 > length) {
      fprintf(stderr, "Invalid amount of inner classes\n");
      break;
    }
    RBinJavaClass *class_item = calloc(1, sizeof(RBinJavaClass));
    if (!class_item) {
      break;
    }
    class_item->inner_class_info_index = (data[i] << 8) | data[i + 1];
    i += 2;
    class_item->outer_class_info_index = (data[i] << 8) | data[i + 1];
    i += 2;
    class_item->inner_name_index = (data[i] << 8) | data[i + 1];
    i += 2;
    class_item->inner_class_access_flags = (data[i] << 8) | data[i + 1];
    i += 4;
    class_item->inner_class_access_flags_str =
        retrieve_class_method_access_string(class_item->inner_class_access_flags);
    class_item->offset = class_offset;
    class_item->length = 8;
    RBinJavaCpItem *inner_name_item =
        r_bin_java_get_item_from_bin_cp_list(bin_java, class_item->inner_name_index);
    if (!inner_name_item) {
      fprintf(stderr, "BINCPLIS IS HULL %d\n", class_item->inner_name_index);
    }
    class_item->inner_name =
        r_bin_java_get_item_name_from_bin_cp_list(bin_java, inner_name_item);
    if (!class_item->inner_name) {
      RBinJavaCpItem *inner_class_item =
          r_bin_java_get_item_from_bin_cp_list(bin_java,
                                               class_item->inner_class_info_index);
      if (!inner_class_item) {
        fprintf(stderr, "BINCPLIST IS NULL %d\n",
                class_item->inner_class_info_index);
      }
      class_item->inner_name = r_bin_java_get_item_name_from_bin_cp_list(
          bin_java, inner_class_item);
      if (!class_item->inner_name) {
        class_item->inner_name = r_str_dup(NULL, "NULL");
        fprintf(stderr,
                "r_bin_java_inner_classes_attr: Unable to find the name for %d "
                "index.\n",
                class_item->inner_name_index);
        free(class_item);
        break;
      }
    }
    r_list_append(attr->u.inner_classes.classes, class_item);
  }
  attr->length = i;
  return attr;
}