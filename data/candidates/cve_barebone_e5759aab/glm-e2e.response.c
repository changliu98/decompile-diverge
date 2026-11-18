OPJ_BOOL opj_j2k_add_tlmarker(OPJ_UINT32 tileno, opj_j2k_t *p_j2k, OPJ_UINT16 id, OPJ_UINT32 len, OPJ_UINT32 psot) {
    opj_marker_info_t *new_marker;
    OPJ_UINT32 count;
    OPJ_BOOL ret;

    if (p_j2k == NULL) {
        assert(0);
    }
    if (p_j2k->tile_index == NULL) {
        assert(0);
    }

    count = p_j2k->tile_index[tileno].marknum + 1;
    if (count > p_j2k->tile_index[tileno].nums) {
        p_j2k->tile_index[tileno].nums = (OPJ_UINT32)((float)p_j2k->tile_index[tileno].nums + 1.0f);
        new_marker = (opj_marker_info_t *)opj_realloc(p_j2k->tile_index[tileno].marker, p_j2k->tile_index[tileno].nums * sizeof(opj_marker_info_t));
        if (new_marker == NULL) {
            opj_free(p_j2k->tile_index[tileno].marker);
            p_j2k->tile_index[tileno].marker = NULL;
            p_j2k->tile_index[tileno].nums = 0;
            p_j2k->tile_index[tileno].marknum = 0;
            return 0;
        }
        p_j2k->tile_index[tileno].marker = new_marker;
    }

    p_j2k->tile_index[tileno].marker[p_j2k->tile_index[tileno].marknum].id = id;
    p_j2k->tile_index[tileno].marker[p_j2k->tile_index[tileno].marknum].len = len;
    p_j2k->tile_index[tileno].marker[p_j2k->tile_index[tileno].marknum].data = psot;
    p_j2k->tile_index[tileno].marknum++;

    if (id == 0xff90) {
        count = p_j2k->tile_index[tileno].marknum;
        if (p_j2k->tile_index[tileno].psot != NULL) {
            p_j2k->tile_index[tileno].psot[count] = psot;
        }
    }

    return 1;
}