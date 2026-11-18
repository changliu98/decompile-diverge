void __cdecl do_iccprofile_item(deark *c, lctx *d, int64_t pos, int64_t len)
{
  if ( len >= 4 )
  {
    uint32_t selector = dbuf_getu32be(c->infile, pos);
    int64_t data_len = len - 4;

    de_dbg(c, "ICC profile segment, selector=%d, data len=%d", selector, data_len);

    // If the selector is not 0 or 1, close any existing ICC profile file
    if ( selector != 1 )
    {
      dbuf_close(d->iccprofile_file);
      d->iccprofile_file = NULL;
    }

    // If the selector is 0, create a new ICC profile output file
    if ( selector == 0 )
    {
      d->iccprofile_file = dbuf_create_output_file(c, "icc", NULL, 1u);
    }

    // If the selector is 0 or 1, copy the segment data into the ICC profile file
    if ( selector <= 1 )
    {
      dbuf_copy(c->infile, pos + 4, data_len, d->iccprofile_file);
    }
  }
}