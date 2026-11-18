jp2_box_t *jp2_box_get(jas_stream_t *in)
{
 jp2_box_t *box;
 jas_stream_t *datain;
 uint32_t len;
 uint64_t extlen;
 int rc;

 box = 0;
 datain = 0;

 box = jas_malloc(sizeof(jp2_box_t));
 if (!box)
  goto error;

 box->ops = &jp2_box_defops;

 rc = jp2_getuint32(in, &len);
 if (rc)
  goto error;

 rc = jp2_getuint32(in, &box->type);
 if (rc)
  goto error;

 box->info = jp2_boxinfolookup(box->type);
 box->ops = &box->info->ops;
 box->len = len;

 if (jas_getdbglevel() >= 10)
  jas_eprintf("preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
   34, box->info->name, 34, box->type, box->len);

 if (box->len == 1) {
  rc = jp2_getuint64(in, &extlen);
  if (rc)
   goto error;
  if (extlen >= 0x100000000) {
   jas_eprintf("warning: cannot handle large 64-bit box length\n");
   extlen = 0xffffffff;
  }
  box->len = extlen;
  box->datalen = box->len - 16;
 } else {
  box->datalen = box->len - 8;
 }

 if (box->len == 0 || box->len >= 8) {
  if (box->info->flags & (0x0001 | 0x0002))
   goto done;

  datain = jas_stream_memopen((char *) 0, 0);
  if (!datain)
   goto error;

  rc = jas_stream_copy(datain, in, box->datalen);
  if (rc) {
   box->ops = &jp2_box_defops;
   jas_eprintf("cannot copy box data\n");
   goto error;
  }

  jas_stream_rewind(datain);

  if (box->ops->getdata) {
   rc = box->ops->getdata(box, datain);
   if (rc) {
    jas_eprintf("cannot parse box data\n");
    goto error;
   }
  }

  jas_stream_close(datain);
 }

done:
 if (jas_getdbglevel() >= 1)
  jp2_box_dump(box, *PTR_stderr);

 return box;

error:
 if (box)
  jp2_box_destroy(box);
 if (datain)
  jas_stream_close(datain);
 return 0;
}