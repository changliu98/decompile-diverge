static void RemoveICCProfileFromResourceBlock(StringInfo *string_info) {
  unsigned char *start;
  unsigned char *ptr;
  unsigned char *tag_start;
  unsigned long length;
  unsigned short tag;
  unsigned short type;
  unsigned long count;
  unsigned long data_length;
  length = GetStringInfoLength(string_info);
  if (length < 16) return;
  start = (unsigned char *)GetStringInfoDatum(string_info);
  ptr = start;
  while (ptr >= start && ptr < start + length - 16) {
    tag_start = ptr;
    if (LocaleNCompare((const char *)ptr, "8BIM", 4) != 0) return;
    ptr = PushLongPixel(LITTLE_ENDIAN_BYTE_ORDER, ptr, &count);
    ptr = PushShortPixel(LITTLE_ENDIAN_BYTE_ORDER, ptr, &tag);
    ptr = PushShortPixel(LITTLE_ENDIAN_BYTE_ORDER, ptr, &type);
    ptr = PushLongPixel(LITTLE_ENDIAN_BYTE_ORDER, ptr, &data_length);
    if (tag == 1039) {
      data_length = (data_length + 1) & ~1;
      CopyMagickMemory(tag_start, tag_start + 12 + data_length,
                       length - (tag_start - start) - 12 - data_length);
      SetStringInfoLength(string_info, length - 12 - data_length);
      return;
    }
    ptr += data_length;
    if (data_length & 1) ptr++;
  }
}