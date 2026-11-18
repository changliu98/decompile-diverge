struct InnerClassesAttribute *r_bin_java_inner_classes_attr_new(void *a, void *b, void *c, void *d) {
    struct InnerClassesAttribute *attr = NULL;
    int i = 0;
    long offset = 0;
    struct InnerClassesAttribute *ret = NULL;

    attr = r_bin_java_default_attr_new(a, b, c, d);
    offset += 6;

    if (attr == NULL) {
        ret = attr;
        return ret;
    }

    attr->type = 7;
    attr->number_of_classes = ((char *)b)[offset] << 8 | ((char *)b)[offset + 1];
    offset += 2;

    attr->classes_list = r_list_newf(r_bin_java_inner_classes_attr_entry_free);

    for (i = 0; i < attr->number_of_classes; i++) {
        void *raw_bytes = (char *)d + offset;
        
        if (offset + 8 > (long)c) {
            fprintf(stderr, "Error: Some kind of overflow or bounds issue.\n");
            break;
        }

        struct InnerClassEntry *ic = calloc(1, 0x38);
        if (ic == NULL) {
            break;
        }

        ic->inner_class_info_index = ((char *)b)[offset] << 8 | ((char *)b)[offset + 1];
        offset += 2;
        ic->outer_class_info_index = ((char *)b)[offset] << 8 | ((char *)b)[offset + 1];
        offset += 2;
        ic->inner_name_index = ((char *)b)[offset] << 8 | ((char *)b)[offset + 1];
        offset += 2;
        ic->inner_class_access_flags = ((char *)b)[offset] << 8 | ((char *)b)[offset + 1];
        offset += 2;

        ic->flags_str = retrieve_class_method_access_string(ic->inner_class_access_flags);
        ic->raw_bytes = raw_bytes;
        ic->size = 8;

        void *cp_item = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, ic->outer_class_info_index);
        if (cp_item == NULL) {
            fprintf(stderr, "Error: Unable to find constant pool object for outer_class_info_index: %d.\n", ic->outer_class_info_index);
        }
        ic->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, cp_item);

        if (ic->name == NULL) {
            cp_item = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, ic->inner_class_info_index);
            if (cp_item == NULL) {
                fprintf(stderr, "Error: Unable to find constant pool object for inner_class_info_index: %d.\n", ic->inner_class_info_index);
            }
            ic->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, cp_item);

            if (ic->name == NULL) {
                ic->name = r_str_dup(0, "");
                fprintf(stderr, "Error: Unable to find name for inner_class_info_index: %d.\n", ic->outer_class_info_index);
                free(ic);
                break;
            }
        }

        r_list_append(attr->classes_list, ic);
    }

    attr->size = offset;
    ret = attr;
    return ret;
}