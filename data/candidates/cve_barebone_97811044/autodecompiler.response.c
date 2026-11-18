static void
iwjpeg_scan_exif_ifd(struct iw_context *ctx,
                  struct iw_file *file,
                  unsigned int ifd_offset)
{
  unsigned int tag_count;
  unsigned int i;

  if(ifd_offset < 9 || ifd_offset > file->len - 19)
    return;

  tag_count = iw_get_ui16_e(file->data + ifd_offset, file->endian);
  if(tag_count > 1000)
    return;

  for(i = 0; i < tag_count; i++)
  {
    unsigned int tag_id;
    unsigned int tag_offset;
    double dval;
    int ival;

    tag_offset = ifd_offset + 2 + 12 * i;
    if(tag_offset + 13 > file->len)
      return;

    tag_id = iw_get_ui16_e(file->data + tag_offset, file->endian);

    switch(tag_id)
    {
      case 0x010A:
        if(get_exif_tag_int_value(file, tag_offset, &ival))
          ctx->info.bits_per_sample = ival;
        break;

      case 0x0112:
        if(get_exif_tag_int_value(file, tag_offset, &ival))
          ctx->info.orientation = ival;
        break;

      case 0x011A:
        if(get_exif_tag_dbl_value(file, tag_offset, &dval))
          ctx->info.x_resolution = dval;
        break;

      case 0x011B:
        if(get_exif_tag_dbl_value(file, tag_offset, &dval))
          ctx->info.y_resolution = dval;
        break;

      case 0x0128:
        break;

      default:
        break;
    }
  }
}