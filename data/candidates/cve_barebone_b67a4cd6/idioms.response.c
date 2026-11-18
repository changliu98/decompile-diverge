void fmtutil_macbitmap_read_pixmap_only_fields(struct deark *ark, struct dbuf *buf, struct fmtutil_macbitmap_info *bi, long pos)
{
  print_ark(ark, "additional PixMap header fields, at %d", (int)pos);
  ark_indent(ark, 1);
  int version = dbuf_getuint16(buf, pos);
  print_ark(ark, "pixmap version: %d", version);
  bi->packing_type = dbuf_getuint16(buf, pos + 2);
  print_ark(ark, "packing type: %d", bi->packing_type);
  int pack_size = dbuf_getuint32(buf, pos + 4);
  print_ark(ark, "pixel data length: %d", pack_size);
  bi->hdpi = dbuf_getint32(buf, pos + 8);
  bi->vdpi = dbuf_getint32(buf, pos + 12);
  print_ark(ark, "dpi: %d, %d", bi->hdpi, bi->vdpi);
  bi->pixeltype = dbuf_getuint16(buf, pos + 16);
  bi->pixelsize = dbuf_getuint16(buf, pos + 18);
  bi->cmpcount = dbuf_getuint16(buf, pos + 20);
  bi->cmpsize = dbuf_getuint16(buf, pos + 22);
  print_ark(ark, "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
    bi->pixeltype, bi->pixelsize, bi->cmpcount, bi->cmpsize);
  bi->pdwidth = (bi->rowbytes * 8) / bi->pixelsize;
  if (bi->pdwidth < bi->npwidth)
    bi->pdwidth = bi->npwidth;
  int plane_bytes = dbuf_getuint32(buf, pos + 24);
  print_ark(ark, "plane bytes: %d", plane_bytes);
  bi->pmTable = dbuf_getuint32(buf, pos + 28);
  print_ark(ark, "pmTable: 0x%08x", bi->pmTable);
  int pmreserved = dbuf_getuint32(buf, pos + 32);
  print_ark(ark, "pmReserved: 0x%08x", pmreserved);
  ark_indent(ark, -1);
}