void do_iccprofile_item(deark *c, lctx *d, int64_t pos, int64_t len)
{
 uint32_t selector;
 if (len < 4)
  return;
 selector = dbuf_getu32be(c->infile, pos);
 de_dbg(c, "ICC profile segment, selector=%d, data len=%d",
  (int)selector, (int)(len - 4));

 if (selector != 1) {
  dbuf_close(d->iccprofile_file);
  d->iccprofile_file = NULL;
 }

 if (selector == 0) {
  d->iccprofile_file = dbuf_create_output_file(c, "icc", NULL, 1);
 }

 if (selector == 1) {
  dbuf_copy(c->infile, pos + 4, len - 4, d->iccprofile_file);
 }
}