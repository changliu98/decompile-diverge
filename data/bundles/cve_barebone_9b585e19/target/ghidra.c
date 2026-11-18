int archive_read_format_rar_read_data(archive_read *a,void **buff,size_t *size,int64_t *offset)

{
  void *pvVar1;
  int ret;
  rar *rar;
  int64_t *offset_local;
  size_t *size_local;
  void **buff_local;
  archive_read *a_local;
  int local_c;
  
  pvVar1 = a->format->data;
  if (*(int *)((long)pvVar1 + 0x4f18) == -1) {
    *(undefined4 *)((long)pvVar1 + 0x4f18) = 0;
  }
  if (0 < *(long *)((long)pvVar1 + 0xa0)) {
    __archive_read_consume(a,*(int64_t *)((long)pvVar1 + 0xa0));
    *(undefined8 *)((long)pvVar1 + 0xa0) = 0;
  }
  *buff = (void *)0x0;
  if ((*(char *)((long)pvVar1 + 0xed) == '\0') &&
     (*(long *)((long)pvVar1 + 200) < *(long *)((long)pvVar1 + 0x28))) {
    if (*(char *)((long)pvVar1 + 0x17) == 0x30) {
      ret = read_data_stored(a,buff,size,offset);
    }
    else if ((int)*(char *)((long)pvVar1 + 0x17) - 0x31U < 5) {
      ret = read_data_compressed(a,buff,size,offset);
      if ((ret != 0) && (ret != -0x14)) {
        (*__archive_ppmd7_functions.Ppmd7_Free)((CPpmd7 *)((long)pvVar1 + 0x3a0));
      }
    }
    else {
      archive_set_error(&a->archive,-1,"Unsupported compression method for RAR file.");
      ret = -0x1e;
    }
    local_c = ret;
  }
  else {
    *size = 0;
    *offset = *(int64_t *)((long)pvVar1 + 0xb8);
    if (*offset < *(long *)((long)pvVar1 + 0x28)) {
      *offset = *(int64_t *)((long)pvVar1 + 0x28);
    }
    local_c = 1;
  }
  return local_c;
}