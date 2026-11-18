struct jp2_box *jp2_box_get(struct jas_stream *in)
{
  struct jas_stream *in2 = in;
  struct jas_stream *in3 = ((void *)0);
  struct jp2_box *box = ((void *)0);
  struct jp2_boxinfo *boxinfo = ((void *)0);
  unsigned int len = 0;
  unsigned long extlen = 0;
  if ((box = jas_malloc(sizeof(struct jp2_box))) == ((void *)0))
    goto error;
  box->ops = &jp2_boxinfo_unk.ops;
  if (jp2_getuint32(in, &len) != 0
      || jp2_getuint32(in, &box->type) != 0)
    goto error;
  if ((boxinfo = jp2_boxinfolookup(box->type)) == ((void *)0))
    goto error;
  box->info = boxinfo;
  box->ops = &boxinfo->ops;
  box->len = len;
  if (jas_getdbglevel() >= 10)
    jas_eprintf
      ("preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
       '"', boxinfo->name, '"', box->type, (int)box->len);
  if (box->len == 1) {
    if (jp2_getuint64(in, &extlen) != 0)
      goto error;
    if (extlen > 0xFFFFFFFF) {
      jas_eprintf("warning: cannot handle large 64-bit box length\n");
      extlen = 0xFFFFFFFF;
    }
    box->len = extlen;
    box->datalen = extlen - 16;
  } else
    box->datalen = box->len - 8;
  if (box->len < 1 || box->len < 8)
    goto error;
  if (boxinfo->flags & (1 | 2))
    goto done;
  if ((in2 = jas_stream_memopen(((void *)0), 0)) == ((void *)0))
    goto error;
  if (jas_stream_copy(in2, in, box->datalen) != 0) {
    box->ops = &jp2_boxinfo_unk.ops;
    jas_eprintf("cannot copy box data\n");
    goto error;
  }
  jas_stream_rewind(in2);
  if (box->ops->getdata != ((void *)0)) {
    if (box->ops->getdata(box, in2) != 0) {
      jas_eprintf("cannot parse box data\n");
      goto error;
    }
  }
  jas_stream_close(in2);
 done:
  if (jas_getdbglevel() >= 1)
    jp2_box_dump(box, stderr);
  return box;
 error:
  if (box != ((void *)0))
    jp2_box_destroy(box);
  if (in2 != ((void *)0))
    jas_stream_close(in2);
  return ((void *)0);
}