void png_check_chunk_length(png_const_structrp png_ptr,png_uint_32 length)

{
  undefined1 auVar1 [16];
  int iVar2;
  int iVar3;
  ulong local_50;
  ulong local_48;
  ulong local_40;
  size_t row_factor;
  png_alloc_size_t idat_limit;
  png_alloc_size_t limit;
  png_uint_32 length_local;
  png_const_structrp png_ptr_local;
  
  limit = 0x7fffffff;
  if ((png_ptr->user_chunk_malloc_max != 0) && (png_ptr->user_chunk_malloc_max < 0x7fffffff)) {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (png_ptr->chunk_name == 0x49444154) {
    iVar2 = 1;
    if (8 < png_ptr->bit_depth) {
      iVar2 = 2;
    }
    iVar3 = 0;
    if (png_ptr->interlaced != '\0') {
      iVar3 = 6;
    }
    local_40 = CONCAT44(0,png_ptr->width * (uint)png_ptr->channels * iVar2 + 1 + iVar3);
    auVar1._8_8_ = 0;
    auVar1._0_8_ = local_40;
    if (SUB168((ZEXT416(0) << 0x40 | ZEXT816(0xffffffff)) / auVar1,0) < (ulong)png_ptr->height) {
      idat_limit = 0x7fffffff;
    }
    else {
      idat_limit = png_ptr->height * local_40;
    }
    if (0x7f36 < local_40) {
      local_40 = 0x7f36;
    }
    local_48 = (idat_limit / local_40 + 1) * 5 + 6 + idat_limit;
    if (0x7ffffffe < local_48) {
      local_48 = 0x7fffffff;
    }
    if (limit < local_48) {
      local_50 = local_48;
    }
    else {
      local_50 = limit;
    }
    limit = local_50;
  }
  if (limit < length) {
    png_chunk_error(png_ptr,"chunk data is too large");
  }
  return;
}