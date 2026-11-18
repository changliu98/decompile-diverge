static int do_bid_note(struct file *file, unsigned char *note, int desc_type,
                       int desc_size, int desc_namesz, int desc_dataz,
                       int desc_name_offset, int desc_data_offset,
                       int *note_type_p) {
  unsigned char build_id[20];
  int ret;
  int i;
  if (desc_namesz != 4 || strcmp((char *)note + desc_name_offset, "GNU\0") != 0 ||
      desc_type != 3)
    return 0;
  *note_type_p |= 0x10;
  switch (desc_dataz) {
    case 8:
      ret = file_printf(file, ", BuildID[%s]=", "xxHash");
      break;
    case 16:
      ret = file_printf(file, ", BuildID[%s]=", "md5/uuid");
      break;
    case 20:
      ret = file_printf(file, ", BuildID[%s]=", "sha1");
      break;
    default:
      ret = file_printf(file, ", BuildID[%s]=", "unknown");
      break;
  }
  if (ret == -1) return 1;
  memcpy(build_id, note + desc_data_offset, desc_dataz);
  for (i = 0; i < desc_dataz; i++) {
    if (file_printf(file, "%02x", build_id[i]) == -1) return 1;
  }
  return 1;
}