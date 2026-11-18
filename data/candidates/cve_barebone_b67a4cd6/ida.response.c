void __cdecl fmtutil_macbitmap_read_pixmap_only_fields(deark *c, dbuf *f, fmtutil_macbitmap_info *bi, int64_t pos)
{
  unsigned int n; // [rsp+0h] [rbp-40h]
  unsigned int plane_bytes; // [rsp+8h] [rbp-38h]
  unsigned int pack_size; // [rsp+10h] [rbp-30h]
  unsigned int pixmap_version; // [rsp+18h] [rbp-28h]

  de_dbg(c, "additional PixMap header fields, at %d", (unsigned int)pos);
  de_dbg_indent(c, 1);
  pixmap_version = dbuf_getu16be(f, pos);
  de_dbg(c, "pixmap version: %d", pixmap_version);
  bi->packing_type = dbuf_getu16be(f, pos + 2);
  de_dbg(c, "packing type: %d", (unsigned int)bi->packing_type);
  pack_size = dbuf_getu32be(f, pos + 4);
  de_dbg(c, "pixel data length: %d", pack_size);
  bi->hdpi = pict_read_fixed(f, pos + 8);
  bi->vdpi = pict_read_fixed(f, pos + 12);
  de_dbg(c, aDpi2f, bi->hdpi, bi->vdpi);
  bi->pixeltype = dbuf_getu16be(f, pos + 16);
  bi->pixelsize = dbuf_getu16be(f, pos + 18);
  bi->cmpcount = dbuf_getu16be(f, pos + 20);
  bi->cmpsize = dbuf_getu16be(f, pos + 22);
  de_dbg(
    c,
    "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
    (unsigned int)bi->pixeltype,
    (unsigned int)bi->pixelsize,
    (unsigned int)bi->cmpcount,
    (unsigned int)bi->cmpsize);
  bi->pdwidth = 8 * bi->rowbytes / bi->pixelsize;
  if ( bi->pdwidth < bi->npwidth )
    bi->pdwidth = bi->npwidth;
  plane_bytes = dbuf_getu32be(f, pos + 24);
  de_dbg(c, "plane bytes: %d", plane_bytes);
  bi->pmTable = dbuf_getu32be(f, pos + 28);
  de_dbg(c, "pmTable: 0x%08x", bi->pmTable);
  n = dbuf_getu32be(f, pos + 32);
  de_dbg(c, "pmReserved: 0x%08x", n);
  de_dbg_indent(c, -1);
}