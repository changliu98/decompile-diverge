OPJ_BOOL __cdecl opj_j2k_add_tlmarker(
        OPJ_UINT32 tileno,
        opj_codestream_index_t *cstr_index,
        OPJ_UINT32 type,
        OPJ_OFF_T pos,
        OPJ_UINT32 len)
{
    assert(cstr_index != NULL);
    assert(cstr_index->tile_index != NULL);

    opj_tile_index_t *tile = &cstr_index->tile_index[tileno];

    // Check if we need to expand the marker array
    if (tile->marknum + 1 > tile->maxmarknum) {
        // IDA misidentified 'realloc' as 'qstrcpy'. 
        // The float casts are an artifact of the compiler optimizing integer addition 
        // into floating-point operations, likely due to strict aliasing or specific optimization passes.
        tile->maxmarknum = (int)(float)((float)(int)tile->maxmarknum + 100.0f);
        
        opj_marker_info_t *new_marker = (opj_marker_info_t *)realloc(
            tile->marker, 
            24LL * tile->maxmarknum
        );

        if (!new_marker) {
            free(tile->marker);
            tile->marker = NULL;
            tile->maxmarknum = 0;
            tile->marknum = 0;
            return OPJ_FALSE;
        }
        tile->marker = new_marker;
    }

    // Add the new marker data
    opj_marker_info_t *current_marker = &tile->marker[tile->marknum];
    current_marker->type = type;
    current_marker->pos = pos;
    current_marker->len = len;

    tile->marknum++;

    // If the marker is a Start of Tile-part (SOT) marker, record the start position
    if (type == J2K_MS_SOT && tile->tp_index) {
        tile->tp_index[tile->current_tpsno].start_pos = pos;
    }

    return OPJ_TRUE;
}