static void fmtutil_macbitmap_read_pixmap_only_fields(
    demux_t *p_demux, dbuf_t *p_data, pict_t *p_pict, int i_offset) {
  unsigned i_tmp;
  unsigned i_reserved;
  de_dbg(p_demux, "additional PixMap header fields, at %d", i_offset);
  de_dbg_indent(p_demux, +1);
  i_tmp = dbuf_getu16be(p_data, i_offset + 0);
  de_dbg(p_demux, "pixmap version: %d", i_tmp);
  p_pict->i_packing = dbuf_getu16be(p_data, i_offset + 2);
  de_dbg(p_demux, "packing type: %d", p_pict->i_packing);
  i_tmp = dbuf_getu32be(p_data, i_offset + 4);
  de_dbg(p_demux, "pixel data length: %d", i_tmp);
  p_pict->d_x_dpi = pict_read_fixed(p_data, i_offset + 8);
  p_pict->d_y_dpi = pict_read_fixed(p_data, i_offset + 12);
  de_dbg(p_demux, "dpi: %f x %f", p_pict->d_x_dpi, p_pict->d_y_dpi);
  p_pict->i_pixel_type = dbuf_getu16be(p_data, i_offset + 16);
  p_pict->i_depth = dbuf_getu16be(p_data, i_offset + 18);
  p_pict->i_chroma = dbuf_getu16be(p_data, i_offset + 20);
  p_pict->i_bits_per_pixel = dbuf_getu16be(p_data, i_offset + 22);
  de_dbg(p_demux,
         "pixel type=%d, bits/pixel=%d, components/pixel=%d, bits/comp=%d",
         p_pict->i_pixel_type, p_pict->i_depth, p_pict->i_chroma,
         p_pict->i_bits_per_pixel);
  p_pict->i_sar_den =
      8 * p_pict->i_sar_num / p_pict->i_depth;
  if (p_pict->i_sar_den < p_pict->i_visible_height)
    p_pict->i_sar_den = p_pict->i_visible_height;
  i_tmp = dbuf_getu32be(p_data, i_offset + 24);
  de_dbg(p_demux, "plane bytes: %d", i_tmp);
  p_pict->i_pm_table = dbuf_getu32be(p_data, i_offset + 28);
  de_dbg(p_demux, "pmTable: 0x%08x", p_pict->i_pm_table);
  i_reserved = dbuf_getu32be(p_data, i_offset + 32);
  de_dbg(p_demux, "pmReserved: 0x%08x", i_reserved);
  de_dbg_indent(p_demux, -1);
}