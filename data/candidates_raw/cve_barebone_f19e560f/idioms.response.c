void iwjpegr_exif_read(void *ctx, struct iw_exif *exif, unsigned int ifd)
{
  struct iwjpegrcontext *c = (iwjpegrcontext *)ctx;
  struct iw_exif_state *e = (struct iw_exif_state *)exif;
  unsigned int i;
  unsigned int tag_count;
  unsigned int tag_pos;
  unsigned int tag_id;
  unsigned int tag_val;
  double tag_vald;
  if (ifd < 8 || ifd + e->d_len < 18)
    return;
  tag_count = iwjpegr_read_int(&e->d[ifd], e->endian);
  if (tag_count > 1000)
    return;
  for (i = 0; i < tag_count; i++)
  {
    tag_pos = ifd + i * 12 + 2;
    if (tag_pos + 12 > e->d_len)
      break;
    tag_id = iwjpegr_read_int(&e->d[tag_pos], e->endian);
    switch (tag_id)
    {
      case 0x112:
        if (iwjpegr_read_int(e, tag_pos, &tag_val))
          c->exif_orientation = tag_val;
        break;
      case 0x11a:
        if (iwjpegr_read_double(e, tag_pos, &tag_vald))
          c->exif_density_x = tag_vald;
        break;
      case 0x11b:
        if (iwjpegr_read_double(e, tag_pos, &tag_vald))
          c->exif_density_y = tag_vald;
        break;
      case 0x128:
        if (iwjpegr_read_int(e, tag_pos, &tag_val))
          c->exif_density_unit = tag_val;
        break;
    }
  }
}