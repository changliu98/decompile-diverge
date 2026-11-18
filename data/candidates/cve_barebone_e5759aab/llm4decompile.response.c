OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno, opj_codestream_index_t *cstr_index, OPJ_UINT32 type, OPJ_OFF_T pos, OPJ_UINT32 len)
{
    opj_marker_info_t *new_marker = NULL;

    ((cstr_index != NULL) ? (void)0 : __assert_fail("cstr_index != NULL", "/work/harness.c", 106, "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"));
    ((cstr_index->tile_index != NULL) ? (void)0 : __assert_fail("cstr_index->tile_index != NULL", "/work/harness.c", 107, "OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32, opj_codestream_index_t *, OPJ_UINT32, OPJ_OFF_T, OPJ_UINT32)"));

    if (cstr_index->tile_index[tileno].marknum + 1 > cstr_index->tile_index[tileno].maxmarknum) {
        cstr_index->tile_index[tileno].maxmarknum = (OPJ_UINT32)(cstr_index->tile_index[tileno].maxmarknum + 1.25F);
        new_marker = (opj_marker_info_t*)opj_realloc(cstr_index->tile_index[tileno].marker, cstr_index->tile_index[tileno].maxmarknum * sizeof(opj_marker_info_t));
        if (new_marker == NULL) {
            opj_free(cstr_index->tile_index[tileno].marker);
            cstr_index->tile_index[tileno].marker = NULL;
            cstr_index->tile_index[tileno].maxmarknum = 0;
            cstr_index->tile_index[tileno].marknum = 0;
            return 0;
        }
        cstr_index->tile_index[tileno].marker = new_marker;
    }

    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].type = (unsigned short)type;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].pos = (OPJ_OFF_T)pos;
    cstr_index->tile_index[tileno].marker[cstr_index->tile_index[tileno].marknum].len = len;
    cstr_index->tile_index[tileno].marknum++;

    if (type == 0xff90) {
        if (cstr_index->tile_index[tileno].tp_index) {
            cstr_index->tile_index[tileno].tp_index[cstr_index->tile_index[tileno].current_tpsno].start_pos = pos;
        }
    }

    return 1;
}