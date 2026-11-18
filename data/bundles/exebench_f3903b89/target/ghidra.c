void get_payload_info(char *bzimage,int *offset,int *size)

{
  uchar setup_sectors;
  uint system_offset;
  int *size_local;
  int *offset_local;
  char *bzimage_local;
  
  *offset = (uint)(byte)(bzimage[0x1f1] + 1) * 0x200 + *(int *)(bzimage + 0x248);
  *size = *(int *)(bzimage + 0x24c);
  return;
}