OPJ_BOOL opj_j2k_add_tlmarker
                   (OPJ_UINT32 tileno,opj_codestream_index_t *cstr_index,OPJ_UINT32 type,
                   OPJ_OFF_T pos,OPJ_UINT32 len)

{
  opj_marker_info_t *poVar1;
  
  // Validate that the codestream index pointer is not NULL
  if (cstr_index == (opj_codestream_index_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("cstr_index != 00","/work/harness.c",0xe0,
                  "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
                 );
  }
  // Check if the tile index array is initialized
  if (cstr_index->tile_index != (opj_tile_index_t *)0x0) {
    // Check if the current marker count exceeds the allocated maximum capacity
    if (cstr_index->tile_index[tileno].maxmarknum < cstr_index->tile_index[tileno].marknum + 1) {
      // Increase the maximum marker count by a fixed increment (likely 16 based on _DAT_00102004)
      cstr_index->tile_index[tileno].maxmarknum =
           (OPJ_UINT32)(long)((float)cstr_index->tile_index[tileno].maxmarknum + _DAT_00102004);
      // Reallocate memory for the marker array to accommodate more markers
      poVar1 = opj_realloc(cstr_index->tile_index[tileno].marker,
                           (ulong)cstr_index->tile_index[tileno].maxmarknum * 0x18);
      // Handle allocation failure by cleaning up and returning false
      if (poVar1 == (opj_marker_info_t *)0x0) {
        opj_free(cstr_index->tile_index[tileno].marker);
        cstr_index->tile_index[tileno].marker = (opj_marker_info_t *)0x0;
        cstr_index->tile_index[tileno].maxmarknum = 0;
        cstr_index->tile_index[tileno].marknum = 0;
        return 0;
      }
      // Update the marker pointer to the newly allocated memory
      cstr_index->tile_index[tileno].marker = poVar1;
    }
    // Store the marker type, position, and length in the next available slot
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type =
         (unsigned_short)type;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos =
         (long)(int)pos;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
    // Increment the marker count for the current tile
    cstr_index->tile_index[tileno].marknum = cstr_index->tile_index[tileno].marknum + 1;
    // If the marker type is TLM (Tile-part Lengths), record the start position for the current tile-part
    if ((type == 0xff90) && (cstr_index->tile_index[tileno].tp_index != (opj_tp_index_t *)0x0)) {
      cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].
      start_pos = pos;
    }
    // Return success
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  // Assert that tile_index is not NULL if the previous check failed
  __assert_fail("cstr_index->tile_index != 00","/work/harness.c",0xe1,
                "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
               );
}