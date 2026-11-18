int __cdecl iwgif_read_image(iwgifrcontext *rctx)
{
  unsigned int root_codesize; // [rsp+Ch] [rbp-6054h]
  size_t subblocksize; // [rsp+18h] [rbp-6048h]
  lzwdeccontext d; // [rsp+20h] [rbp-6040h] BYREF
  int retval; // [rsp+6054h] [rbp-Ch]
  iwgifrcontext *rctxa; // [rsp+6058h] [rbp-8h]

  rctxa = rctx;
  retval = 0;
  if ( iwgif_read(rctx, rctx->rbuf, 9uLL) )
  {
    rctxa->image_left = iw_get_ui16le(rctxa->rbuf);
    rctxa->image_top = iw_get_ui16le(&rctxa->rbuf[2]);
    rctxa->image_width = iw_get_ui16le(&rctxa->rbuf[4]);
    rctxa->image_height = iw_get_ui16le(&rctxa->rbuf[6]);
    rctxa->interlaced = ((int)rctxa->rbuf[8] >> 6) & 1;
    if ( (((int)rctxa->rbuf[8] >> 7) & 1) == 0
      || (rctxa->colortable.num_entries = 1 << ((rctxa->rbuf[8] & 7) + 1),
          iwgif_read_color_table(rctxa, &rctxa->colortable)) )
    {
      if ( rctxa->has_transparency )
        rctxa->colortable.entry[rctxa->trans_color_index].a = 0;
      if ( iwgif_read(rctxa, rctxa->rbuf, 1uLL) )
      {
        root_codesize = rctxa->rbuf[0];
        if ( root_codesize >= 2 && root_codesize <= 0xB )
        {
          if ( iwgif_init_screen(rctxa) )
          {
            rctxa->total_npixels = rctxa->image_height * (__int64)rctxa->image_width;
            if ( iwgif_make_row_pointers(rctxa) )
            {
              lzw_init(&d, root_codesize);
              lzw_clear(&d);
              while ( iwgif_read(rctxa, rctxa->rbuf, 1uLL) )
              {
                subblocksize = rctxa->rbuf[0];
                if ( rctxa->rbuf[0] )
                {
                  if ( !iwgif_read(rctxa, rctxa->rbuf, subblocksize)
                    || !lzw_process_bytes(rctxa, &d, rctxa->rbuf, subblocksize) )
                  {
                    return retval;
                  }
                  if ( !d.eoi_flag && rctxa->pixels_set < rctxa->total_npixels )
                    continue;
                }
                return 1;
              }
            }
          }
        }
        else
        {
          iw_set_error(rctxa->ctx, "Invalid LZW minimum code size");
        }
      }
    }
  }
  return retval;
}