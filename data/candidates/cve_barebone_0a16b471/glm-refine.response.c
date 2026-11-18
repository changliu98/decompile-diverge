int __cdecl iwgif_read_image(iwgifrcontext *rctx)
{
  unsigned int root_codesize;
  size_t subblocksize;
  lzwdeccontext d;
  int retval = 0;

  if ( !iwgif_read(rctx, rctx->rbuf, 9uLL) )
    return retval;

  rctx->image_left = iw_get_ui16le(rctx->rbuf);
  rctx->image_top = iw_get_ui16le(&rctx->rbuf[2]);
  rctx->image_width = iw_get_ui16le(&rctx->rbuf[4]);
  rctx->image_height = iw_get_ui16le(&rctx->rbuf[6]);
  rctx->interlaced = (rctx->rbuf[8] >> 6) & 1;

  // Check for local color table flag (bit 7)
  if ( (rctx->rbuf[8] >> 7) & 1 )
  {
    rctx->colortable.num_entries = 1 << ((rctx->rbuf[8] & 7) + 1);
    if ( !iwgif_read_color_table(rctx, &rctx->colortable) )
      return retval;
  }

  if ( rctx->has_transparency )
    rctx->colortable.entry[rctx->trans_color_index].a = 0;

  if ( !iwgif_read(rctx, rctx->rbuf, 1uLL) )
    return retval;

  root_codesize = rctx->rbuf[0];
  if ( root_codesize < 2 || root_codesize > 0xB )
  {
    iw_set_error(rctx->ctx, "Invalid LZW minimum code size");
    return retval;
  }

  if ( !iwgif_init_screen(rctx) )
    return retval;

  rctx->total_npixels = rctx->image_height * (__int64)rctx->image_width;
  if ( !iwgif_make_row_pointers(rctx) )
    return retval;

  lzw_init(&d, root_codesize);
  lzw_clear(&d);

  while ( iwgif_read(rctx, rctx->rbuf, 1uLL) )
  {
    subblocksize = rctx->rbuf[0];
    if ( !subblocksize )
      return 1;

    if ( !iwgif_read(rctx, rctx->rbuf, subblocksize) 
      || !lzw_process_bytes(rctx, &d, rctx->rbuf, subblocksize) )
    {
      return retval;
    }

    if ( d.eoi_flag || rctx->pixels_set >= rctx->total_npixels )
      return 1;
  }

  return retval;
}