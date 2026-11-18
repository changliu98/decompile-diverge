static void dcr_parse_icc_segment (DCRAW* p, DCR_METADATA* meta, int offset, int len)
{
 int sel, icclen;

 if (len < 5) return;
 sel = dbuf_getu32be(p->obj_, offset);
 icclen = len-4;
 de_dbg(p,"ICC profile segment, selector=%d, data len=%d",sel,icclen);

 if (sel != 1) {
  dbuf_close(meta->icc);
  meta->icc = NULL;
 }
 if (!sel) meta->icc = dbuf_create_output_file(p,"icc",NULL,1);
 if (!sel || sel == 1) dbuf_copy(p->obj_,offset+4,icclen,meta->icc);
}