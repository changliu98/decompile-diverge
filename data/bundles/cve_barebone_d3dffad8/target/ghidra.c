jp2_box_t * jp2_box_get(jas_stream_t *in)

{
  int iVar1;
  _Bool dataflag;
  uint_fast64_t extlen;
  uint_fast32_t len;
  jas_stream_t *tmpstream;
  jp2_boxinfo_t *boxinfo;
  jp2_box_t *box;
  jas_stream_t *in_local;
  
  box = (jp2_box_t *)0x0;
  tmpstream = (jas_stream_t *)0x0;
  in_local = in;
  box = jas_malloc(0x140);
  if (box != (jp2_box_t *)0x0) {
    box->ops = (jp2_boxops_s *)0x104598;
    iVar1 = jp2_getuint32(in_local,&len);
    if ((iVar1 == 0) && (iVar1 = jp2_getuint32(in_local,&box->type), iVar1 == 0)) {
      boxinfo = jp2_boxinfolookup((int)box->type);
      box->info = boxinfo;
      box->ops = &boxinfo->ops;
      box->len = len;
      iVar1 = jas_getdbglevel();
      if (9 < iVar1) {
        jas_eprintf("preliminary processing of JP2 box: type=%c%s%c (0x%08x); length=%d\n",0x22,
                    boxinfo->name,0x22,box->type,box->len);
      }
      if (box->len == 1) {
        iVar1 = jp2_getuint64(in_local,&extlen);
        if (iVar1 != 0) goto LAB_00101867;
        if (0xffffffff < extlen) {
          jas_eprintf("warning: cannot handle large 64-bit box length\n");
          extlen = 0xffffffff;
        }
        box->len = extlen;
        box->datalen = extlen - 0x10;
      }
      else {
        box->datalen = box->len - 8;
      }
      if ((box->len == 0) || (7 < box->len)) {
        if ((box->info->flags & 3U) != 0) {
LAB_00101839:
          iVar1 = jas_getdbglevel();
          if (0 < iVar1) {
            jp2_box_dump(box,*(FILE **)PTR_stderr_00103ff8);
          }
          return box;
        }
        tmpstream = jas_stream_memopen((char *)0x0,0);
        if (tmpstream != (jas_stream_t *)0x0) {
          iVar1 = jas_stream_copy(tmpstream,in_local,(int)box->datalen);
          if (iVar1 == 0) {
            jas_stream_rewind(tmpstream);
            if ((box->ops->getdata == (_func_int_jp2_box_t_ptr_jas_stream_t_ptr *)0x0) ||
               (iVar1 = (*box->ops->getdata)(box,tmpstream), iVar1 == 0)) {
              jas_stream_close(tmpstream);
              goto LAB_00101839;
            }
            jas_eprintf("cannot parse box data\n");
          }
          else {
            box->ops = (jp2_boxops_s *)0x104598;
            jas_eprintf("cannot copy box data\n");
          }
        }
      }
    }
  }
LAB_00101867:
  if (box != (jp2_box_t *)0x0) {
    jp2_box_destroy(box);
  }
  if (tmpstream != (jas_stream_t *)0x0) {
    jas_stream_close(tmpstream);
  }
  return (jp2_box_t *)0x0;
}