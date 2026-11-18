OPJ_BOOL opj_j2k_add_tlmarker
                   (OPJ_UINT32 tileno,opj_codestream_index_t *cstr_index,OPJ_UINT32 type,
                   OPJ_OFF_T pos,OPJ_UINT32 len)

{
  // Check if the codestream index pointer is valid; if not, trigger assertion failure
  if (cstr_index == (opj_codestream_index_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("cstr_index != 00","/work/harness.c",0x6a,
                  "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
                 );
  }
  // Check if the tile index array is allocated
  if (cstr_index->tile_index != (opj_tile_index_t *)0x0) {
    // Check if the current marker count exceeds the allocated capacity
    if (cstr_index->tile_index[tileno].maxmarknum < cstr_index->tile_index[tileno].marknum + 1) {
      // Increase the maximum marker count by a predefined increment (DAT_00102004)
      cstr_index->tile_index[tileno].maxmarknum =
           (OPJ_UINT32)(long)((float)cstr_index->tile_index[tileno].maxmarknum + DAT_00102004);
      // Reallocate memory for the marker array with the new size (each marker is 0x18 bytes)
      opj_marker_info_t *poVar1 = opj_realloc(cstr_index->tile_index[tileno].marker,
                           (ulong)cstr_index->tile_index[tileno].maxmarknum * 0x18);
      // Check if reallocation failed
      if (poVar1 == (opj_marker_info_t *)0x0) {
        // Free the old marker array and reset marker-related fields
        opj_free(cstr_index->tile_index[tileno].marker);
        cstr_index->tile_index[tileno].marker = (opj_marker_info_t *)0x0;
        cstr_index->tile_index[tileno].maxmarknum = 0;
        cstr_index->tile_index[tileno].marknum = 0;
        return 0;
      }
      // Update the marker pointer to the newly allocated memory
      cstr_index->tile_index[tileno].marker = poVar1;
    }
    // Store the marker type, position, and length in the current marker slot
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type =
         (unsigned_short)type;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos =
         (long)(int)pos;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
    // Increment the marker count
    cstr_index->tile_index[tileno].marknum = cstr_index->tile_index[tileno].marknum + 1;
    // If the marker type is TLM (0xff90) and tile-part index exists, record the start position
    if ((type == 0xff90) && (cstr_index->tile_index[tileno].tp_index != (opj_tp_index_t *)0x0)) {
      cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].
      start_pos = pos;
    }
    // Return success
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  // Trigger assertion failure if tile index is not allocated
  __assert_fail("cstr_index->tile_index != 00","/work/harness.c",0x6b,
                "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
               );
}