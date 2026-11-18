static OPJ_BOOL opj_j2k_add_tlmarker( OPJ_UINT32 tileno,
                                      opj_codestream_index_t * cstr_index,
                                      OPJ_UINT16 type,
                                      OPJ_OFF_T pos,
                                      OPJ_SIZE_T len )
{
  char *data;
  OPJ_BOOL ret;

  if(!(cstr_index != NULL)) { ___assert_fail("cstr_index != 00","harness.c",224, "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT16, OPJ_OFF_T, OPJ_SIZE_T)"); };
  if(!(cstr_index->tile_index != NULL)) { ___assert_fail("cstr_index->tile_index != 00","harness.c",225, "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT16, OPJ_OFF_T, OPJ_SIZE_T)"); };

  if ( cstr_index->tile_index[tileno].marker_count + 1 > cstr_index->tile_index[tileno].marknum_alloc ) {
    cstr_index->tile_index[tileno].marknum_alloc += 100.0f;
    data = (char *) __Z7qstrcpyPcPKc(cstr_index->tile_index[tileno].marker_data, cstr_index->tile_index[tileno].marker_data, cstr_index->tile_index[tileno].marknum_alloc * sizeof( opj_marker_info_t ));
    if ( ! data ) {
      opj_free( cstr_index->tile_index[tileno].marker_data );
      cstr_index->tile_index[tileno].marker_data = NULL;
      cstr_index->tile_index[tileno].marknum_alloc = 0;
      cstr_index->tile_index[tileno].marker_count = 0;
      ret = 0;
    } else {
      cstr_index->tile_index[tileno].marker_data = (opj_marker_info_t *) data;
    }
  }

  cstr_index->tile_index[tileno].marker_data[cstr_index->tile_index[tileno].marker_count].type = type;
  cstr_index->tile_index[tileno].marker_data[cstr_index->tile_index[tileno].marker_count].pos = (OPJ_OFF_T)pos;
  cstr_index->tile_index[tileno].marker_data[cstr_index->tile_index[tileno].marker_count].len = (OPJ_SIZE_T)len;
  cstr_index->tile_index[tileno].marker_count++;

  if ( type == 0xff90 ) {
    OPJ_UINT32 l_current_tile_part = cstr_index->tile_index[tileno].current_tile_part;
    if ( cstr_index->tile_index[tileno].tile_parts ) {
      cstr_index->tile_index[tileno].tile_parts[l_current_tile_part].length_header = (OPJ_OFF_T)pos;
    }
  } else {
    ret = 1;
  }

  return ret;
}