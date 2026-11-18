void fmtutil_macbitmap_read_pixmap_only_fields(deark *c, dbuf *f, fmtutil_macbitmap_info *bi, int64_t pos)
{







  int64_t pixmap_version, pixel_data_length, plane_bytes;
  int64_t pack_size;

  de_dbg(c, "additional PixMap header fields, at %d", (int)pos);
  de_dbg_indent(c, +1);

  pixmap_version = dbuf_getu16be(f, pos);
  de_dbg(c, "pixmap version: %d", (int)pixmap_version);

  bi->packing_type = dbuf_getu16be(f, pos+2);
  de_dbg(c, "packing type: %d", (int)bi->packing_type);

  pixel_data_length = dbuf_getu32be(f, pos+4);
  de_dbg(c, "pixel data length: %d", (int)pixel_data_length);

  bi->hdpi = pict_read_fixed(f, pos+8);
  bi->vdpi = pict_read_fixed(f, pos+12);
  de_dbg(c, "DPI: %g,%g", bi->hdpi, bi->vdpi);

  bi->pixeltype = dbuf_getu16be(f, pos+16);
  bi->pixelsize = dbuf_getu16be(f, pos+18);
  bi->cmpcount = dbuf_getu16be(f, pos+20);
  bi->cmpsize = dbuf_getu16be(f, pos+22);
  de_dbg(c, "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
    (int)bi->pixeltype, (int)bi->pixelsize, (int)bi->cmpcount, (int)bi->cmpsize);


  bi->pdwidth = (bi->rowbytes * 8) / bi->pixelsize;
  if(bi->pdwidth < bi->npwidth)
    bi->pdwidth = bi->npwidth;

  plane_bytes = dbuf_getu32be(f, pos+24);
  de_dbg(c, "plane bytes: %d", (int)plane_bytes);

  bi->pmTable = dbuf_getu32be(f, pos+28);
  de_dbg(c, "pmTable: 0x%08x", bi->pmTable);

  de_dbg(c, "pmReserved: 0x%08x", dbuf_getu32be(f, pos+32));

  de_dbg_indent(c, -1);
}