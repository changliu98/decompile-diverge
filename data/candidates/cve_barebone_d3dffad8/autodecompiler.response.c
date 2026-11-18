static jp2_box_t *jp2_box_get(jas_stream_t *in)
{
 jp2_box_t *box;
 jp2_boxinfo_t *boxinfo;
 int extflag;
 unsigned long extlen;
 unsigned long len;
 jp2_box_t *ret;
 box = 0;
 jas_stream_t *datastrm = 0;

 if (!(box = jas_malloc(sizeof(jp2_box_t)))) {
  goto error;
 }
 box->type = &jp2_boxinfo_unk.typeinfo + 3;

 if (jp2_getuint32(in, &len) || jp2_getuint32(in, &box->typeval)) {
  goto error;
 }

 boxinfo = jp2_boxinfolookup(box->typeval);
 box->info = boxinfo;
 box->type = &boxinfo->typeinfo + 3;
 box->len = len;

 if (jas_getdbglevel() >= 11) {
  jas_eprintf("preliminary processing of JP2 box: "
    "type=%c%s%c (0x%08x); length=%lu\n",
    '"', boxinfo->name, '"', box->typeval,
    box->len);
 }

 if (box->len == 1) {
  if (jp2_getuint64(in, &extlen)) {
   goto error;
  }
  if (extlen > ((unsigned long) (~((unsigned long) 0)))) {
   jas_eprintf("warning: cannot handle large 64-bit box length\n");
   extlen = ((unsigned long) (~((unsigned long) 0)));
  }
  box->len = extlen;
  box->extlen = extlen - 16;
 } else {
  box->extlen = box->len - 8;
 }

 if (box->len != 0 && box->len < 8) {
  goto error;
 }

 extflag = (((box->info->flags & 0x0001) == 0) ? 1 : 0);

 if (extflag) {
  if (!(datastrm = jas_stream_memopen(0, 0))) {
   goto error;
  }
  if (jas_stream_copy(datastrm, in, (int) box->extlen)) {
   box->type = &jp2_boxinfo_unk.typeinfo + 3;
   jas_eprintf("cannot copy box data\n");
   goto error;
  }
  jas_stream_rewind(datastrm);
  if (box->type->parse) {
   if (box->type->parse(box, datastrm)) {
    jas_eprintf("cannot parse box data\n");
    goto error;
   }
  } else {
   jas_stream_close(datastrm);
  }
 }

 if (jas_getdbglevel() >= 2) {
  jp2_box_dump(box, stderr->s);
 }

 ret = box;
 goto done;

error:

 if (box) {
  jp2_box_destroy(box);
 }
 if (datastrm) {
  jas_stream_close(datastrm);
 }

 ret = 0;

done:
 return ret;
}