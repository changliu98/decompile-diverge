static void fmtutil_macbitmap_read_pixmap_only_fields(de_ctx *ctx, dbuf_t *s, de_pixmap_t *px, uint32_t off)
{
  uint16_t v;
  uint32_t pack_len, plane_bytes, pm_reserved;

  de_dbg(ctx, "additional PixMap header fields, at %d", off);
  de_dbg_indent(ctx, 1);

  v = dbuf_getu16be(s, off + 0);
  de_dbg(ctx, "pixmap version: %d", v);

  px->type = dbuf_getu16be(s, off + 2);
  de_dbg(ctx, "packing type: %d", px->type);

  pack_len = dbuf_getu32be(s, off + 4);
  de_dbg(ctx, "pixel data length: %d", pack_len);

  px->dpi_x = pict_read_fixed(s, off + 8);
  px->dpi_y = pict_read_fixed(s, off + 12);
  de_dbg(ctx, "dpi: %.2f", px->dpi_x, px->dpi_y);

  px->pixel_type = dbuf_getu16be(s, off + 16);
  px->bits_per_pixel = dbuf_getu16be(s, off + 18);
  px->components_per_pixel = dbuf_getu16be(s, off + 20);
  px->bits_per_component = dbuf_getu16be(s, off + 22);
  de_dbg(ctx, "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
    px->pixel_type, px->bits_per_pixel, px->components_per_pixel, px->bits_per_component);

  px->stride = (px->w * 8) / px->bits_per_pixel;
  if (px->stride < px->min_stride) {
    px->stride = px->min_stride;
  }

  plane_bytes = dbuf_getu32be(s, off + 24);
  de_dbg(ctx, "plane bytes: %d", plane_bytes);

  px->palette_offset = dbuf_getu32be(s, off + 28);
  de_dbg(ctx, "pmTable: 0x%08x", px->palette_offset);

  pm_reserved = dbuf_getu32be(s, off + 32);
  de_dbg(ctx, "pmReserved: 0x%08x", pm_reserved);

  de_dbg_indent(ctx, -1);
}