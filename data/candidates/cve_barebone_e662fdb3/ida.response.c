void __cdecl do_iccprofile_item(deark *c, lctx *d, int64_t pos, int64_t len)
{
  unsigned __int64 selector; // [rsp+8h] [rbp-28h]

  if ( len >= 4 )
  {
    selector = dbuf_getu32be(c->infile, pos);
    de_dbg(c, "ICC profile segment, selector=%d, data len=%d", (unsigned int)selector, (unsigned int)(len - 4));
    if ( selector != 1 )
    {
      dbuf_close(d->iccprofile_file);
      d->iccprofile_file = 0LL;
    }
    if ( !selector )
      d->iccprofile_file = dbuf_create_output_file(c, "icc", 0LL, 1u);
    if ( selector <= 1 )
      dbuf_copy(c->infile, pos + 4, len - 4, d->iccprofile_file);
  }
}