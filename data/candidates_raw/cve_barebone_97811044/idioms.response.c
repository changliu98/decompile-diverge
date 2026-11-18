void iwjpegr_exif_read(struct iwjpegrcontext *ctx, struct iw_exif_state *exif, unsigned int ifd)
{
  struct iwjpegrcontext *ctxp = ctx;
  struct iw_exif_state *exifp = exif;
  unsigned int ifda = ifd;
  if (ifda < 8 || ifda > exif->d_len - 18)
    return;
  unsigned int tag_count = iwjpegr_exif_ifd_count(&exif->d[ifda], exif->endian);
  if (tag_count > 1000)
    return;
  for (unsigned int i = 0; i < tag_count; i++) {
    unsigned int tag_pos = ifda + 2 + i * 12;
    if (tag_pos + 12 > exif->d_len)
      break;
    unsigned int tag_id = iwjpegr_exif_ifd_tagid(&exif->d[tag_pos], exif->endian);
    switch (tag_id) {
      case 0x00112:
        unsigned int orientation;
        if (iwjpegr_exif_ifd_int(&exif->d[tag_pos], &orientation))
          ctxp->exif_orientation = orientation;
        break;
      case 0x0011a:
        double density_x;
        if (iwjpegr_exif_ifd_real(&exif->d[tag_pos], &density_x))
          ctxp->exif_density_x = density_x;
        break;
      case 0x0011b:
        double density_y;
        if (iwjpegr_exif_ifd_real(&exif->d[tag_pos], &density_y))
          ctxp->exif_density_y = density_y;
        break;
      case 0x00128:
        unsigned int density_unit;
        if (iwjpegr_exif_ifd_int(&exif->d[tag_pos], &density_unit))
          ctxp->exif_density_unit = density_unit;
        break;
    }
  }
}