jp2_box_t *__cdecl jp2_box_get(jas_stream_t *in)
{
  uint_fast64_t extlen; // [rsp+8h] [rbp-38h] BYREF
  uint_fast32_t len; // [rsp+10h] [rbp-30h] BYREF
  jas_stream_t *tmpstream; // [rsp+18h] [rbp-28h]
  jp2_boxinfo_t *boxinfo; // [rsp+20h] [rbp-20h]
  jp2_box_t *box; // [rsp+28h] [rbp-18h]
  jas_stream_t *ina; // [rsp+30h] [rbp-10h]

  ina = in;
  tmpstream = 0LL;
  box = (jp2_box_t *)jas_malloc(0x140uLL);
  if ( !box )
    goto error;
  box->ops = (jp2_boxops_s *)((char *)&jp2_boxinfo_unk + 24);
  if ( jp2_getuint32(ina, &len) || jp2_getuint32(ina, &box->type) )
    goto error;
  boxinfo = jp2_boxinfolookup(box->type);
  box->info = boxinfo;
  box->ops = &boxinfo->ops;
  box->len = len;
  if ( jas_getdbglevel() >= 10 )
    jas_eprintf(
      "preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",
      34LL,
      boxinfo->name,
      34LL,
      box->type,
      box->len);
  if ( box->len == 1 )
  {
    if ( jp2_getuint64(ina, &extlen) )
      goto error;
    if ( extlen > 0xFFFFFFFF )
    {
      jas_eprintf("warning: cannot handle large 64-bit box length\n");
      extlen = 0xFFFFFFFFLL;
    }
    box->len = extlen;
    box->datalen = extlen - 16;
  }
  else
  {
    box->datalen = box->len - 8;
  }
  if ( box->len && box->len < 8 )
    goto error;
  if ( (box->info->flags & 3) != 0 )
    goto LABEL_23;
  tmpstream = jas_stream_memopen(0LL, 0);
  if ( !tmpstream )
  {
error:
    if ( box )
      jp2_box_destroy(box);
    if ( tmpstream )
      jas_stream_close(tmpstream);
    return 0LL;
  }
  if ( jas_stream_copy(tmpstream, ina, box->datalen) )
  {
    box->ops = (jp2_boxops_s *)((char *)&jp2_boxinfo_unk + 24);
    jas_eprintf("cannot copy box data\n");
    goto error;
  }
  jas_stream_rewind(tmpstream);
  if ( box->ops->getdata && box->ops->getdata(box, tmpstream) )
  {
    jas_eprintf("cannot parse box data\n");
    goto error;
  }
  jas_stream_close(tmpstream);
LABEL_23:
  if ( jas_getdbglevel() >= 1 )
    jp2_box_dump(box, stderr);
  return box;
}