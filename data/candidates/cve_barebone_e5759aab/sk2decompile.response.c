OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno, opj_j2k_t *p_j2k,
                              OPJ_UINT32 p_type, OPJ_OFF_T p_pos,
                              OPJ_UINT32 p_len) {
  opj_codestream_marker_t *l_marker;
  assert(p_j2k != 00);
  assert(p_j2k->tile_info != 00);
  if (p_j2k->tile_info[tileno].num_markers + 1 >
      p_j2k->tile_info[tileno].markers_size) {
    p_j2k->tile_info[tileno].markers_size =
        (OPJ_UINT32)((float)p_j2k->tile_info[tileno].markers_size + 100);
    l_marker = qstrcpy(p_j2k->tile_info[tileno].markers,
                       p_j2k->tile_info[tileno].markers_size *
                           sizeof(opj_codestream_marker_t));
    if (!l_marker) {
      opj_free(p_j2k->tile_info[tileno].markers);
      p_j2k->tile_info[tileno].markers = 00;
      p_j2k->tile_info[tileno].markers_size = 0;
      p_j2k->tile_info[tileno].num_markers = 0;
      return 0;
    }
    p_j2k->tile_info[tileno].markers = l_marker;
  }
  p_j2k->tile_info[tileno].markers[p_j2k->tile_info[tileno].num_markers].type =
      p_type;
  p_j2k->tile_info[tileno].markers[p_j2k->tile_info[tileno].num_markers].pos =
      p_pos;
  p_j2k->tile_info[tileno].markers[p_j2k->tile_info[tileno].num_markers].len =
      p_len;
  p_j2k->tile_info[tileno].num_markers++;
  if (p_type == 0xff80) {
    if (p_j2k->tile_info[tileno].tile_parts) {
      p_j2k->tile_info[tileno].tile_parts[p_j2k->tile_info[tileno].num_parts]
          .part_start = p_pos;
    }
  }
  return 1;
}