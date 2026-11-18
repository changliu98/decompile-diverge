void bztar_get_info(void *bzimage, int *offset, int *size)
{
  struct bztar_header *header = (struct bztar_header *)bzimage;
  *offset = (header->offset * 512) + (header->blocksize + 1);
  *size = header->size;
}