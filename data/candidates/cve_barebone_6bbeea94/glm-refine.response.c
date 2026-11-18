OPJ_BOOL __cdecl opj_j2k_add_tlmarker(
        OPJ_UINT32 tileno,
        opj_codestream_index_t *cstr_index,
        OPJ_UINT32 type,
        OPJ_OFF_T pos,
        OPJ_UINT32 len)
{
  opj_marker_info_t *new_marker;
  opj_tile_index_t *tile_index;

  // Assertions for null pointer checks
  if ( !cstr_index )
    __assert_fail(
      "cstr_index != 00",
      "/work/harness.c",
      0xE0u,
      "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)");
      
  if ( !cstr_index->tile_index )
    __assert_fail(
      "cstr_index->tile_index != 00",
      "/work/harness.c",
      0xE1u,
      "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)");

  // Cache the tile index pointer to avoid redundant lookups
  tile_index = &cstr_index->tile_index[tileno];

  // Check if we need to expand the marker array
  if ( tile_index->marknum + 1 > tile_index->maxmarknum )
  {
    // Increase maxmarknum by 100 (using float cast as per original logic)
    tile_index->maxmarknum = (int)((float)tile_index->maxmarknum + 100.0f);
    
    // Reallocate marker array (qstrcpy is likely a misidentified realloc)
    new_marker = (opj_marker_info_t *)qstrcpy(
                                        tile_index->marker,
                                        24LL * tile_index->maxmarknum);
                                        
    if ( !new_marker )
    {
      // Handle allocation failure
      opj_free(tile_index->marker);
      tile_index->marker = NULL;
      tile_index->maxmarknum = 0;
      tile_index->marknum = 0;
      return 0;
    }
    tile_index->marker = new_marker;
  }

  // Populate the new marker entry
  tile_index->marker[tile_index->marknum].type = type;
  tile_index->marker[tile_index->marknum].pos = (int)pos;
  tile_index->marker[tile_index->marknum].len = len;
  
  // Increment the marker count
  tile_index->marknum++;

  // Check if the marker type is 65424 (0xFF90, likely SOP - Start of Packet)
  if ( type == 65424 && tile_index->tp_index )
  {
    tile_index->tp_index[tile_index->current_tpsno].start_pos = pos;
  }

  return 1;
}