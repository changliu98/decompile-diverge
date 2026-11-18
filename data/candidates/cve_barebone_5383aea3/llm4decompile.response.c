RBinJavaAttrInfo *r_bin_java_inner_classes_attr_new(RBinJavaObj *bin,
                                                    const ut8 *buffer,
                                                    ut64 sz,
                                                    ut64 buf_offset) {
	RBinJavaAttrInfo *attr = r_bin_java_default_attr_new (bin, buffer, sz, buf_offset);
	if (!attr) {
		return NULL;
	}
	attr->type = 7;
	attr->info.inner_classes_attr.number_of_classes = (buffer[6] << 8) | buffer[7];
	ut64 offset = 8;
	attr->info.inner_classes_attr.classes = r_list_newf (r_bin_java_inner_classes_attr_entry_free);
	ut16 i = 0;
	for (i = 0; i < attr->info.inner_classes_attr.number_of_classes; i++) {
		ut64 curpos = buf_offset + offset;
		if (offset + 8 > sz) {
			fprintf (stderr, "Invalid amount of inner classes\n");
			break;
		}
		RBinJavaInnerClassesAttributeEntry *entry = calloc (1, sizeof (RBinJavaInnerClassesAttributeEntry));
		if (!entry) {
			break;
		}
		entry->inner_class_info_index = (buffer[offset] << 8) | buffer[offset + 1];
		entry->outer_class_info_index = (buffer[offset + 2] << 8) | buffer[offset + 3];
		entry->inner_name_index = (buffer[offset + 4] << 8) | buffer[offset + 5];
		entry->inner_class_access_flags = (buffer[offset + 6] << 8) | buffer[offset + 7];
		offset += 8;
		entry->inner_class_access_flags_str = retrieve_class_method_access_string (entry->inner_class_access_flags);
		entry->offset = curpos;
		entry->size = 8;
		RBinJavaCPTypeObj *cp_outer_class_info = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, entry->outer_class_info_index);
		if (!cp_outer_class_info) {
			fprintf (stderr, "BINCPLIS IS HULL %d\n", entry->outer_class_info_index);
		}
		entry->outer_class_info_name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, cp_outer_class_info);
		if (!entry->outer_class_info_name) {
			RBinJavaCPTypeObj *cp_inner_class_info = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, entry->inner_class_info_index);
			if (!cp_inner_class_info) {
				fprintf (stderr, "BINCPLIST IS NULL %d\n", entry->inner_class_info_index);
			}
			entry->outer_class_info_name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, cp_inner_class_info);
			if (!entry->outer_class_info_name) {
				entry->outer_class_info_name = r_str_dup (NULL, "NULL");
				fprintf (stderr, "r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n", entry->outer_class_info_index);
				free (entry);
				break;
			}
		}
		r_list_append (attr->info.inner_classes_attr.classes, entry);
	}
	attr->size = offset;
	return attr;
}