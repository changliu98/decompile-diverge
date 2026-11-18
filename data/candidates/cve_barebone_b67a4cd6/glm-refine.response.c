void __cdecl fmtutil_macbitmap_read_pixmap_only_fields(deark *c, dbuf *f, fmtutil_macbitmap_info *bi, int64_t pos)
{
  unsigned int pixmap_version;
  unsigned int pack_size;
  unsigned int plane_bytes;
  unsigned int pm_reserved;

  de_dbg(c, "additional PixMap header fields, at %d", (unsigned int)pos);
  de_dbg_indent(c, 1);

  // Base PixMap fields
  pixmap_version = dbuf_getu16be(f, pos);
  bi->packing_type = (unsigned int)dbuf_getu16be(f, pos + 2);
  pack_size = dbuf_getu32be(f, pos + 4);
  
  de_dbg(c, "pixmap version: %u", pixmap_version);
  de_dbg(c, "packing type: %u", bi->packing_type);
  de_dbg(c, "pixel data length: %u", pack_size);

  // DPI Information
  bi->hdpi = pict_read_fixed(f, pos + 8);
  bi->vdpi = pict_read_fixed(f, pos + 12);
  de_dbg(c, aDpi2f, bi->hdpi, bi->vdpi);

  // Pixel Component Information
  bi->pixeltype = (unsigned int)dbuf_getu16be(f, pos + 16);
  bi->pixelsize = (unsigned int)dbuf_getu16be(f, pos + 18);
  bi->cmpcount  = (unsigned int)dbuf_getu16be(f, pos + 20);
  bi->cmpsize   = (unsigned int)dbuf_getu16be(f, pos + 22);
  
  de_dbg(
    c,
    "pixel type=%u, bits/pixel=%u, components/pixel=%u, bits/comp=%u",
    bi->pixeltype,
    bi->pixelsize,
    bi->cmpcount,
    bi->cmpsize
  );

  // Dimensions and Alignment
  bi->pdwidth = 8 * bi->rowbytes / bi->pixelsize;
  if (bi->pdwidth < bi->npwidth) {
    bi->pdwidth = bi->npwidth;
  }

  // Color Table and Reserved Fields
  plane_bytes = dbuf_getu32be(f, pos + 24);
  bi->pmTable = dbuf_getu32be(f, pos + 28);
  pm_reserved = dbuf_getu32be(f, pos + 32);
  
  de_dbg(c, "plane bytes: %u", plane_bytes);
  de_dbg(c, "pmTable: 0x%08x", bi->pmTable);
  de_dbg(c, "pmReserved: 0x%08x", pm_reserved);

  de_dbg_indent(c, -1);
}