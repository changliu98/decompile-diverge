void iwjpeg_scan_exif_ifd(iwjpegrcontext *rctx,iw_exif_state *e,uint32_t ifd)

{
  int iVar1;
  double v_dbl;
  uint v;
  uint tag_id;
  uint tag_pos;
  uint i;
  uint tag_count;
  uint32_t ifd_local;
  iw_exif_state *e_local;
  iwjpegrcontext *rctx_local;
  
  if (((7 < ifd) && ((ulong)ifd <= e->d_len - 0x12)) &&
     (ifd_local = ifd, e_local = e, rctx_local = rctx,
     tag_count = iw_get_ui16_e(e->d + ifd,e->endian), tag_count < 0x3e9)) {
    i = 0;
    while ((i < tag_count &&
           (tag_pos = ifd_local + 2 + i * 0xc, (ulong)(tag_pos + 0xc) <= e_local->d_len))) {
      tag_id = iw_get_ui16_e(e_local->d + tag_pos,e_local->endian);
      switch(tag_id) {
      case 0x112:
        iVar1 = get_exif_tag_int_value(e_local,tag_pos,&v);
        if (iVar1 != 0) {
          rctx_local->exif_orientation = v;
        }
        break;
      case 0x11a:
        iVar1 = get_exif_tag_dbl_value(e_local,tag_pos,&v_dbl);
        if (iVar1 != 0) {
          rctx_local->exif_density_x = v_dbl;
        }
        break;
      case 0x11b:
        iVar1 = get_exif_tag_dbl_value(e_local,tag_pos,&v_dbl);
        if (iVar1 != 0) {
          rctx_local->exif_density_y = v_dbl;
        }
        break;
      case 0x128:
        iVar1 = get_exif_tag_int_value(e_local,tag_pos,&v);
        if (iVar1 != 0) {
          rctx_local->exif_density_unit = v;
        }
      }
      i = i + 1;
    }
  }
  return;
}