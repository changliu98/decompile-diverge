OPJ_BOOL opj_j2k_add_tlmarker
                   (OPJ_UINT32 tileno,opj_codestream_index_t *cstr_index,OPJ_UINT32 type,
                   OPJ_OFF_T pos,OPJ_UINT32 len)

{
  opj_marker_info_t *poVar1;
  OPJ_UINT32 l_current_tile_part;
  opj_marker_info_t *new_marker;
  OPJ_UINT32 len_local;
  OPJ_OFF_T pos_local;
  OPJ_UINT32 type_local;
  opj_codestream_index_t *cstr_index_local;
  OPJ_UINT32 tileno_local;
  
  if (cstr_index == (opj_codestream_index_t *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("cstr_index != 00","/work/harness.c",0x6a,
                  "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
                 );
  }
  if (cstr_index->tile_index != (opj_tile_index_t *)0x0) {
    if (cstr_index->tile_index[tileno].maxmarknum < cstr_index->tile_index[tileno].marknum + 1) {
      cstr_index->tile_index[tileno].maxmarknum =
           (OPJ_UINT32)(long)((float)cstr_index->tile_index[tileno].maxmarknum + DAT_00102004);
      poVar1 = opj_realloc(cstr_index->tile_index[tileno].marker,
                           (ulong)cstr_index->tile_index[tileno].maxmarknum * 0x18);
      if (poVar1 == (opj_marker_info_t *)0x0) {
        opj_free(cstr_index->tile_index[tileno].marker);
        cstr_index->tile_index[tileno].marker = (opj_marker_info_t *)0x0;
        cstr_index->tile_index[tileno].maxmarknum = 0;
        cstr_index->tile_index[tileno].marknum = 0;
        return 0;
      }
      cstr_index->tile_index[tileno].marker = poVar1;
    }
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type =
         (unsigned_short)type;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos =
         (long)(int)pos;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
    cstr_index->tile_index[tileno].marknum = cstr_index->tile_index[tileno].marknum + 1;
    if ((type == 0xff90) && (cstr_index->tile_index[tileno].tp_index != (opj_tp_index_t *)0x0)) {
      cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].
      start_pos = pos;
    }
    return 1;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("cstr_index->tile_index != 00","/work/harness.c",0x6b,
                "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"
               );
}