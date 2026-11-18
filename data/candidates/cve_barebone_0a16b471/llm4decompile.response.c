int iwgif_read_image(struct iwgifrcontext *rctx)
{
 struct lzwdeccontext d;
 int root_codesize;


 if( !iwgif_read(rctx,rctx->rbuf,9) ) {
  return 0;
 }


 rctx->image_left = iw_get_ui16le(rctx->rbuf+0);
 rctx->image_top = iw_get_ui16le(rctx->rbuf+2);
 rctx->image_width = iw_get_ui16le(rctx->rbuf+4);
 rctx->image_height = iw_get_ui16le(rctx->rbuf+6);
 rctx->interlaced = (rctx->rbuf[8]&0x40)!=0;


 if( rctx->rbuf[8]&0x80 ) {

  int ncol = 1 << ((rctx->rbuf[8]&0x07)+1);
  rctx->colortable.num_entries = ncol;
  if( !iwgif_read_color_table(rctx,&rctx->colortable) ) {
   return 0;
  }
 }


 if( rctx->has_transparency ) {
  rctx->colortable.entry[rctx->trans_color_index].a = 0;
 }


 if( !iwgif_read(rctx,rctx->rbuf,1) ) {
  return 0;
 }


 root_codesize = rctx->rbuf[0];
 if( root_codesize < 2 || root_codesize > 11 ) {
  iw_set_error(rctx->ctx,"Invalid LZW minimum code size");
  return 0;
 }


 if( !iwgif_init_screen(rctx) ) {
  return 0;
 }


 rctx->total_npixels = rctx->image_width * rctx->image_height;
 if( !iwgif_make_row_pointers(rctx) ) {
  return 0;
 }


 lzw_init(&d,root_codesize);
 lzw_clear(&d);


 for(;;) {
  size_t blocksize;


  if( !iwgif_read(rctx,rctx->rbuf,1) ) {
   return 0;
  }


  blocksize = rctx->rbuf[0];
  if( blocksize == 0 ) {
   break;
  }


  if( !iwgif_read(rctx,rctx->rbuf,blocksize) ) {
   return 0;
  }


  if( !lzw_process_bytes(rctx,&d,rctx->rbuf,blocksize) ) {
   return 0;
  }


  if( d.eoi_flag || rctx->pixels_set >= rctx->total_npixels ) {
   break;
  }
 }

 return 1;
}