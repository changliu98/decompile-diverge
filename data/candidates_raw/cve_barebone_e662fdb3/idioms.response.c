void iccprofile(struct deark *d, struct lctx *ctx, long pos, long len)
{
  if (len < 4)
    return;
  unsigned long selector = read_be_uint(d->infile, pos);
  log_printf(d, "ICC profile segment, selector=%d, data len=%d",
    (int)selector, (int)(len - 4));
  if (selector != 1) {
    close_file(ctx->iccprofile_file);
    ctx->iccprofile_file = ((void *)0);
  }
  if (selector == 0)
    ctx->iccprofile_file = open_file(d, "icc", ((void *)0), 1);
  if (selector < 2)
    copy_to_file(d->infile, pos + 4, len - 4, ctx->iccprofile_file);
}