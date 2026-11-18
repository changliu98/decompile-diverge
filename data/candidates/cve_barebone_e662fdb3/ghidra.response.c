void do_iccprofile_item(deark *c,lctx *d,int64_t pos,int64_t len)

{
  ulong uVar1;
  dbuf *pdVar2;
  int64_t data_len;
  int64_t selector;
  int64_t len_local;
  int64_t pos_local;
  lctx *d_local;
  deark *c_local;
  
  if (3 < len) {
    uVar1 = dbuf_getu32be(c->infile,pos);
    de_dbg(c,"ICC profile segment, selector=%d, data len=%d",uVar1 & 0xffffffff,
           len - 4U & 0xffffffff);
    if (uVar1 != 1) {
      dbuf_close(d->iccprofile_file);
      d->iccprofile_file = (dbuf *)0x0;
    }
    if (uVar1 == 0) {
      pdVar2 = dbuf_create_output_file(c,"icc",(de_finfo *)0x0,1);
      d->iccprofile_file = pdVar2;
    }
    else if (uVar1 != 1) {
      return;
    }
    dbuf_copy(c->infile,pos + 4,len - 4U,d->iccprofile_file);
  }
  return;
}