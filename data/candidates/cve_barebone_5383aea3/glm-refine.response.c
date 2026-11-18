RBinJavaAttrInfo *__cdecl r_bin_java_inner_classes_attr_new(
        RBinJavaObj *bin,
        uint8_t *buffer,
        uint64_t sz,
        uint64_t buf_offset)
{
    RBinJavaAttrInfo *attr = r_bin_java_default_attr_new(bin, buffer, sz, buf_offset);
    if (!attr)
        return NULL;

    attr->type = 7;
    attr->info.inner_classes_attr.number_of_classes = __builtin_bswap16(*((uint16_t *)(buffer + 6)));
    uint64_t offset = 8;
    attr->info.inner_classes_attr.classes = r_list_newf((RListFree)r_bin_java_inner_classes_attr_entry_free);

    for (uint32_t i = 0; i < attr->info.inner_classes_attr.number_of_classes; ++i)
    {
        uint64_t curpos = offset + buf_offset;

        if (offset + 8 > sz)
        {
            fprintf(stderr, "Invalid amount of inner classes\n");
            break;
        }

        RBinJavaClassesAttribute *icattr = (RBinJavaClassesAttribute *)calloc(1, 0x38);
        if (!icattr)
            break;

        icattr->inner_class_info_idx = __builtin_bswap16(*(uint16_t *)(buffer + offset));
        icattr->outer_class_info_idx = __builtin_bswap16(*(uint16_t *)(buffer + offset + 2));
        icattr->inner_name_idx       = __builtin_bswap16(*(uint16_t *)(buffer + offset + 4));
        icattr->inner_class_access_flags = __builtin_bswap16(*(uint16_t *)(buffer + offset + 6));
        
        icattr->flags_str = retrieve_class_method_access_string(icattr->inner_class_access_flags);
        icattr->file_offset = curpos;
        icattr->size = 8;

        RBinJavaCPTypeObj *obj = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_name_idx);
        if (!obj)
            fprintf(stderr, "BINCPLIS IS HULL %d\n", icattr->inner_name_idx);

        icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, obj);
        if (!icattr->name)
        {
            RBinJavaCPTypeObj *obja = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_class_info_idx);
            if (!obja)
                fprintf(stderr, "BINCPLIST IS NULL %d\n", icattr->inner_class_info_idx);

            icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, obja);
            if (!icattr->name)
            {
                icattr->name = r_str_dup(NULL, "NULL");
                fprintf(
                    stderr,
                    "r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n",
                    icattr->inner_name_idx);
                free(icattr);
                break;
            }
        }

        r_list_append(attr->info.inner_classes_attr.classes, icattr);
        offset += 8;
    }

    attr->size = offset;
    return attr;
}