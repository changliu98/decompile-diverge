static jp2_box_t *jp2_box_get(jas_stream_t *in) {
  jas_stream_t *boxdata = 0;
  jp2_box_t *box;
  unsigned int version;
  unsigned long long length64;
  jp2_boxinfot_ *boxinfo;
  if (!(box = jas_malloc(sizeof(jp2_box_t)))) goto error;
  box->ops_ = &jp2_boxops_.defaultops;
  if (jp2_getuint32(in, &version) || jp2_getuint32(in, &box->type_)) goto error;
  boxinfo = jp2_boxinfolookup(box->type_);
  box->info_ = boxinfo;
  box->ops_ = &boxinfo->defaultops;
  box->len_ = version;
  if (jas_getdbglevel() >= 10)
    jas_eprintf(
        "preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
        '"', boxinfo->name, '"', box->type_, box->len_);
  if (box->len_ == 1) {
    if (jp2_getuint64(in, &length64)) goto error;
    if (length64 > 0xffffffff) {
      jas_eprintf("warning: cannot handle large 64-bit box length\n");
      length64 = 0xffffffff;
    }
    box->len_ = length64;
    box->datalen_ = length64 - 16;
  } else {
    box->datalen_ = box->len_ - 8;
  }
  if (box->len_ && box->len_ < 8) goto error;
  if (!(box->info_->flags_ & (0x01 | 0x02))) {
    if (!(boxdata = jas_stream_memopen(0, 0))) goto error;
    if (jas_stream_copy(boxdata, in, box->datalen_)) {
      box->ops_ = &jp2_boxops_.defaultops;
      jas_eprintf("cannot copy box data\n");
      goto error;
    }
    jas_stream_rewind(boxdata);
    if (box->ops_->parse_ && box->ops_->parse_(box, boxdata)) {
      jas_eprintf("cannot parse box data\n");
      goto error;
    }
    jas_stream_close(boxdata);
  }
  if (jas_getdbglevel() >= 1) jp2_box_dump(box, jas_stdout);
  return box;
error:
  if (box) jp2_box_destroy(box);
  if (boxdata) jas_stream_close(boxdata);
  return 0;
}