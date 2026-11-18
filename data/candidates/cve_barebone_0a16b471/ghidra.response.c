int iwgif_read_image(iwgifrcontext *rctx)

{
  int iVar1;
  uint uVar2;
  ulong buflen;
  uint root_codesize;
  int local_ct_size;
  int has_local_ct;
  size_t subblocksize;
  lzwdeccontext d;
  int retval;
  iwgifrcontext *rctx_local;
  
  retval = 0;
  iVar1 = iwgif_read(rctx,rctx->rbuf,9);
  if (iVar1 != 0) {
    uVar2 = iw_get_ui16le(rctx->rbuf);
    rctx->image_left = uVar2;
    uVar2 = iw_get_ui16le(rctx->rbuf + 2);
    rctx->image_top = uVar2;
    uVar2 = iw_get_ui16le(rctx->rbuf + 4);
    rctx->image_width = uVar2;
    uVar2 = iw_get_ui16le(rctx->rbuf + 6);
    rctx->image_height = uVar2;
    rctx->interlaced = (int)(uint)rctx->rbuf[8] >> 6 & 1;
    if ((int)(uint)rctx->rbuf[8] >> 7 != 0) {
      (rctx->colortable).num_entries = 1 << (rctx->rbuf[8] & 7) + 1;
      iVar1 = iwgif_read_color_table(rctx,&rctx->colortable);
      if (iVar1 == 0) {
        return 0;
      }
    }
    if (rctx->has_transparency != 0) {
      (rctx->colortable).entry[rctx->trans_color_index].a = '\0';
    }
    iVar1 = iwgif_read(rctx,rctx->rbuf,1);
    if (iVar1 != 0) {
      uVar2 = (uint)rctx->rbuf[0];
      if ((uVar2 < 2) || (0xb < uVar2)) {
        iw_set_error(rctx->ctx,"Invalid LZW minimum code size");
      }
      else {
        iVar1 = iwgif_init_screen(rctx);
        if (iVar1 != 0) {
          rctx->total_npixels = (long)rctx->image_width * (long)rctx->image_height;
          iVar1 = iwgif_make_row_pointers(rctx);
          if (iVar1 != 0) {
            lzw_init(&d,uVar2);
            lzw_clear(&d);
            while( true ) {
              iVar1 = iwgif_read(rctx,rctx->rbuf,1);
              if (iVar1 == 0) {
                return 0;
              }
              buflen = (ulong)rctx->rbuf[0];
              if (buflen == 0) break;
              iVar1 = iwgif_read(rctx,rctx->rbuf,buflen);
              if (iVar1 == 0) {
                return 0;
              }
              iVar1 = lzw_process_bytes(rctx,&d,rctx->rbuf,buflen);
              if (iVar1 == 0) {
                return 0;
              }
              if ((d.eoi_flag != 0) || (rctx->total_npixels <= rctx->pixels_set)) break;
            }
            retval = 1;
          }
        }
      }
    }
  }
  return retval;
}