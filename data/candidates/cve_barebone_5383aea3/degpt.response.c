RBinJavaAttrInfo *
r_bin_java_inner_classes_attr_new(RBinJavaObj *bin,uint8_t *buffer,uint64_t sz,uint64_t buf_offset)

{
  RBinJavaAttrInfo *pRVar1;
  RList *pRVar2;
  long lVar3;
  long *data;
  char *pcVar4;
  RBinJavaCPTypeObj *pRVar5;
  uint64_t curpos;
  uint64_t offset;
  uint32_t i;
  RBinJavaCPTypeObj *obj;
  RBinJavaAttrInfo *attr;
  RBinJavaClassesAttribute *icattr;
  uint64_t buf_offset_local;
  uint64_t sz_local;
  uint8_t *buffer_local;
  RBinJavaObj *bin_local;
  
  pRVar1 = r_bin_java_default_attr_new(bin,buffer,sz,buf_offset);
  if (pRVar1 != (RBinJavaAttrInfo *)0x0) {
    pRVar1->type = 7;
    (pRVar1->info).inner_classes_attr.number_of_classes = CONCAT11(buffer[6],buffer[7]);
    offset = 8;
    pRVar2 = r_list_newf(r_bin_java_inner_classes_attr_entry_free);
    (pRVar1->info).inner_classes_attr.classes = pRVar2;
    for (i = 0; i < (pRVar1->info).inner_classes_attr.number_of_classes; i = i + 1) {
      lVar3 = buf_offset + offset;
      if (sz < offset + 8) {
        fprintf(*(FILE **)PTR_stderr_00103ff8,"Invalid amount of inner classes\n");
        break;
      }
      data = calloc(1,0x38);
      if (data == (long *)0x0) break;
      *(ushort *)(data + 5) = CONCAT11(buffer[offset],buffer[offset + 1]);
      *(ushort *)((long)data + 0x2a) = CONCAT11(buffer[offset + 2],buffer[offset + 3]);
      *(ushort *)((long)data + 0x2c) = CONCAT11(buffer[offset + 4],buffer[offset + 5]);
      *(ushort *)((long)data + 0x2e) = CONCAT11(buffer[offset + 6],buffer[offset + 7]);
      offset = offset + 8;
      pcVar4 = retrieve_class_method_access_string(*(uint16_t *)((long)data + 0x2e));
      data[1] = (long)pcVar4;
      data[2] = lVar3;
      data[6] = 8;
      pRVar5 = r_bin_java_get_item_from_bin_cp_list
                         (R_BIN_JAVA_GLOBAL_BIN,(ulong)*(ushort *)((long)data + 0x2c));
      if (pRVar5 == (RBinJavaCPTypeObj *)0x0) {
        fprintf(*(FILE **)PTR_stderr_00103ff8,"BINCPLIS IS HULL %d\n",
                (ulong)*(ushort *)((long)data + 0x2c));
      }
      pcVar4 = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN,pRVar5);
      *data = (long)pcVar4;
      if (*data == 0) {
        pRVar5 = r_bin_java_get_item_from_bin_cp_list
                           (R_BIN_JAVA_GLOBAL_BIN,(ulong)*(ushort *)(data + 5));
        if (pRVar5 == (RBinJavaCPTypeObj *)0x0) {
          fprintf(*(FILE **)PTR_stderr_00103ff8,"BINCPLIST IS NULL %d\n",
                  (ulong)*(ushort *)(data + 5));
        }
        pcVar4 = r_bin_java_get_item_name_from_bin_cp_list(R_BIN_JAVA_GLOBAL_BIN,pRVar5);
        *data = (long)pcVar4;
        if (*data == 0) {
          pcVar4 = r_str_dup((char *)0x0,"NULL");
          *data = (long)pcVar4;
          fprintf(*(FILE **)PTR_stderr_00103ff8,
                  "r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n",
                  (ulong)*(ushort *)((long)data + 0x2c));
          free(data);
          break;
        }
      }
      r_list_append((pRVar1->info).inner_classes_attr.classes,data);
    }
    pRVar1->size = offset;
  }
  return pRVar1;
}