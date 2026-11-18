RBinJavaAttrInfo *__cdecl r_bin_java_inner_classes_attr_new(
        RBinJavaObj *bin,
        uint8_t *buffer,
        uint64_t sz,
        uint64_t buf_offset)
{
  uint64_t curpos; // [rsp+8h] [rbp-58h]
  uint64_t offset; // [rsp+10h] [rbp-50h]
  uint64_t offseta; // [rsp+10h] [rbp-50h]
  uint32_t i; // [rsp+1Ch] [rbp-44h]
  RBinJavaCPTypeObj *obj; // [rsp+20h] [rbp-40h]
  RBinJavaCPTypeObj *obja; // [rsp+20h] [rbp-40h]
  RBinJavaAttrInfo *attr; // [rsp+28h] [rbp-38h]
  RBinJavaClassesAttribute *icattr; // [rsp+30h] [rbp-30h]

  attr = r_bin_java_default_attr_new(bin, buffer, sz, buf_offset);
  if ( !attr )
    return 0LL;
  attr->type = 7;
  attr->info.inner_classes_attr.number_of_classes = _byteswap_ushort(*((_WORD *)buffer + 3));
  offset = 8LL;
  attr->info.inner_classes_attr.classes = r_list_newf((RListFree)r_bin_java_inner_classes_attr_entry_free);
  for ( i = 0; i < attr->info.inner_classes_attr.number_of_classes; ++i )
  {
    curpos = offset + buf_offset;
    if ( offset + 8 > sz )
    {
      fprintf(stderr, "Invalid amount of inner classes\n");
      break;
    }
    icattr = (RBinJavaClassesAttribute *)calloc(1uLL, 0x38uLL);
    if ( !icattr )
      break;
    icattr->inner_class_info_idx = _byteswap_ushort(*(_WORD *)&buffer[offset]);
    offseta = offset + 2;
    icattr->outer_class_info_idx = _byteswap_ushort(*(_WORD *)&buffer[offseta]);
    offseta += 2LL;
    icattr->inner_name_idx = _byteswap_ushort(*(_WORD *)&buffer[offseta]);
    icattr->inner_class_access_flags = _byteswap_ushort(*(_WORD *)&buffer[offseta + 2]);
    offset = offseta + 4;
    icattr->flags_str = retrieve_class_method_access_string(icattr->inner_class_access_flags);
    icattr->file_offset = curpos;
    icattr->size = 8LL;
    obj = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_name_idx);
    if ( !obj )
      fprintf(stderr, "BINCPLIS IS HULL %d\n", icattr->inner_name_idx);
    icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, obj);
    if ( !icattr->name )
    {
      obja = r_bin_java_get_item_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, icattr->inner_class_info_idx);
      if ( !obja )
        fprintf(stderr, "BINCPLIST IS NULL %d\n", icattr->inner_class_info_idx);
      icattr->name = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN, obja);
      if ( !icattr->name )
      {
        icattr->name = r_str_dup(0LL, "NULL");
        fprintf(
          stderr,
          "r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n",
          icattr->inner_name_idx);
        free(icattr);
        break;
      }
    }
    r_list_append(attr->info.inner_classes_attr.classes, icattr);
  }
  attr->size = offset;
  return attr;
}