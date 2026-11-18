void iwjpeg_scan_exif_ifd(iwjpegrcontext *rctx,iw_exif_state *e,unsigned int ifd)
{
 unsigned int tag_count,tag_id,tag_pos;
 unsigned int i;
 unsigned int v;
 double v_dbl;


 if(ifd<8) return;
 if(ifd>e->d_len-18) return;

 tag_count = iw_get_ui16_e(e->d+ifd,e->endian);
 if(tag_count>1000) return;

 for(i=0;i<tag_count;i++) {
  tag_pos = ifd + 2 + i*12;
  if(tag_pos+12>e->d_len) break;
  tag_id = iw_get_ui16_e(e->d+tag_pos,e->endian);
  switch(tag_id) {
  case 0x112:
   if(get_exif_tag_int_value(e,tag_pos,&v)) {
    rctx->exif_orientation = v;
   }
   break;
  case 0x11a:
   if(get_exif_tag_dbl_value(e,tag_pos,&v_dbl)) {
    rctx->exif_density_x = v_dbl;
   }
   break;
  case 0x11b:
   if(get_exif_tag_dbl_value(e,tag_pos,&v_dbl)) {
    rctx->exif_density_y = v_dbl;
   }
   break;
  case 0x128:
   if(get_exif_tag_int_value(e,tag_pos,&v)) {
    rctx->exif_density_unit = v;
   }
   break;
  }
 }
}