static BOOL resize_vbar_entry(rdpContext* context, vbar_entry* entry) {
  if (entry->height > entry->alloc_height) {
    UINT32 bpp = FreeRDPGetBytesPerPixel(context->server_format);
    UINT32 old_size = entry->alloc_height * bpp;
    UINT32 new_size = (entry->height - entry->alloc_height) * bpp;
    BYTE* new_data;
    entry->alloc_height = entry->height;
    new_data = (BYTE*)_alloca(entry->data, entry->height, bpp, 32);
    if (!new_data) {
      return 0;
    }
    memset(new_data + old_size, 0, new_size);
    entry->data = new_data;
  }
  return (entry->data != NULL) || (entry->alloc_height == 0);
}