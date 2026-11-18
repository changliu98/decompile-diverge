OPJ_BOOL __cdecl opj_j2k_add_tlmarker(
        OPJ_UINT32 tileno,
        opj_codestream_index_t *cstr_index,
        OPJ_UINT32 type,
        OPJ_OFF_T pos,
        OPJ_UINT32 len)
{
  opj_tile_index_t *v5; // rax
  opj_marker_info_t *new_marker; // [rsp+10h] [rbp-30h]

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
  if ( cstr_index->tile_index[tileno].marknum + 1 > cstr_index->tile_index[tileno].maxmarknum )
  {
    cstr_index->tile_index[tileno].maxmarknum = (int)(float)((float)(int)cstr_index->tile_index[tileno].maxmarknum
                                                           + 100.0);
    new_marker = (opj_marker_info_t *)qstrcpy(
                                        cstr_index->tile_index[tileno].marker,
                                        24LL * cstr_index->tile_index[tileno].maxmarknum);
    if ( !new_marker )
    {
      opj_free(cstr_index->tile_index[tileno].marker);
      cstr_index->tile_index[tileno].marker = 0LL;
      cstr_index->tile_index[tileno].maxmarknum = 0;
      cstr_index->tile_index[tileno].marknum = 0;
      return 0;
    }
    cstr_index->tile_index[tileno].marker = new_marker;
  }
  cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type = type;
  cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos = (int)pos;
  cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
  v5 = &cstr_index->tile_index[tileno];
  ++v5->marknum;
  if ( type == 65424 && cstr_index->tile_index[tileno].tp_index )
    cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].start_pos = pos;
  return 1;
}