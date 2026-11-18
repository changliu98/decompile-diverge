int iwgif_read_image(struct iwgifcontext *ctx)
{
  struct lzwdeccontext lzwdec;
  int ret = 0;
  if (iwgif_read(ctx, ctx->rbuf, 9)) {
    ctx->image_left = iwgif_getword(ctx->rbuf);
    ctx->image_top = iwgif_getword(&ctx->rbuf[2]);
    ctx->image_width = iwgif_getword(&ctx->rbuf[4]);
    ctx->image_height = iwgif_getword(&ctx->rbuf[6]);
    ctx->interlaced = (ctx->rbuf[8] & 0x40) >> 6;
    if (ctx->has_transparency
        && (ctx->colortable.num_entries = (1 << ((ctx->rbuf[8] & 0x07) + 1)),
            iwgif_read_colortable(ctx, &ctx->colortable))) {
      if (ctx->colortable.entry[ctx->trans_color_index].a = 0)
        ;
      if (iwgif_read(ctx, ctx->rbuf, 1)) {
        unsigned int root_codesize = ctx->rbuf[0];
        if (root_codesize < 2 || root_codesize > 12) {
          iwgif_error(ctx->ctx, "Invalid LZW minimum code size");
        } else if (iwgif_read_header(ctx)) {
          ctx->total_npixels = ctx->image_width * ctx->image_height;
          if (iwgif_read_subblock(ctx)) {
            lzwdec_init(&lzwdec, root_codesize);
            lzwdec_start(&lzwdec);
            while (iwgif_read(ctx, ctx->rbuf, 1)) {
              unsigned int subblocksize = ctx->rbuf[0];
              if (subblocksize == 0)
                break;
              if (iwgif_read(ctx, ctx->rbuf, subblocksize)) {
                if (lzwdec_decode(&lzwdec, ctx->rbuf, subblocksize)) {
                  if (lzwdec.eoi_flag || ctx->pixels_set >= ctx->total_npixels)
                    return 1;
                } else
                  return ret;
              } else
                return ret;
            }
          }
        }
      }
    }
  }
  return ret;
}