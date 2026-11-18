__attribute__((used)) static RBinJavaObj * r_bin_java_parse_inner_classes_attr(RBinJavaObj *obj, ut8* data, ut32 size, ut32 offset) {
	RBinJavaAttr *this_attr = 0;
	ut16 i;
	ut32 cur_offset;
	int read_bytes = 0;
	RBinJavaInnerClassesEntry *entry;
	RList *classes_list;
	RBinJavaCPItem *cpl;
	RBinJavaObj *inner_class;

	this_attr = r_bin_java_default_attr_new (obj, data, size, offset);
	read_bytes += 6;
	if (!this_attr) {
		return this_attr;
	}
	this_attr->type = 7;
	this_attr->attr_size = ((ut16)((((data+read_bytes)[0]&0xff)<< 8)| ((data+read_bytes)[1]&0xff)));
	read_bytes += 2;
	classes_list = r_list_newf (r_bin_java_inner_classes_attr_entry_free);
	this_attr->data = classes_list;
	for (i = 0; i < this_attr->attr_size; i++) {
		cur_offset = offset + read_bytes;
		if (read_bytes + 8 > size) {
			fprintf (stderr, "Invalid amount of inner classes\n");
			break;
		}
		entry = (RBinJavaInnerClassesEntry *) calloc (1, sizeof (RBinJavaInnerClassesEntry));
		if (!entry) {
			break;
		}
		entry->inner_class_idx = ((ut16)((((data+read_bytes)[0]&0xff)<< 8)| ((data+read_bytes)[1]&0xff)));
		read_bytes += 2;
		entry->outer_class_idx = ((ut16)((((data+read_bytes)[0]&0xff)<< 8)| ((data+read_bytes)[1]&0xff)));
		read_bytes += 2;
		entry->inner_name_idx = ((ut16)((((data+read_bytes)[0]&0xff)<< 8)| ((data+read_bytes)[1]&0xff)));
		read_bytes += 2;
		entry->inner_access_flags = ((ut16)((((data+read_bytes)[0]&0xff)<< 8)| ((data+read_bytes)[1]&0xff)));
		read_bytes += 2;
		entry->access_flags_str = retrieve_class_method_access_string (entry->inner_access_flags);
		entry->file_offset = cur_offset;
		entry->size = 8;
		cpl = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, entry->inner_name_idx);
		if (!cpl) {
			fprintf (stderr, "BINCPLIS IS HULL %d\n", entry->inner_name_idx);
		}
		entry->name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, cpl);
		if (!entry->name) {
			cpl = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, entry->inner_class_idx);
			if (!cpl) {
				fprintf (stderr, "BINCPLIST IS NULL %d\n", entry->inner_class_idx);
			}
			entry->name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, cpl);
			if (!entry->name) {
				entry->name = r_str_dup (entry->name, "NULL");
				fprintf (stderr, "r_bin_java_inner_classes_attr: Unable to find the name for %d index\n", entry->inner_name_idx);
				free (entry);
				break;
			}
		}
		r_list_append (classes_list, entry);
	}
	this_attr->file_offset = read_bytes;
	return this_attr;
}