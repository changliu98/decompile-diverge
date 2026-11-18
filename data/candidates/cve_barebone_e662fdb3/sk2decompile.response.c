static void do_iccprofile_item(DeVibeContext *s, VibeFrame *frame,
                               unsigned long offset, unsigned long len) {
  unsigned long selector;
  if (len < 4) return;
  selector = dbuf_getu32be(s->dbuf, offset);
  de_dbg(s, "ICC profile segment, selector=%d, data len=%d", selector,
         len - 4);
  if (selector != 1) {
    dbuf_close(frame->icc);
    frame->icc = NULL;
  }
  if (selector == 0) frame->icc = dbuf_create_output_file(s, "icc", 0, 1);
  if (selector <= 1) dbuf_copy(s->dbuf, offset + 4, len - 4, frame->icc);
}