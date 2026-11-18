OPJ_BOOL opj_j2k_add_tlmarker(opj_j2k_t *p_j2k, OPJ_UINT32 p_tile_index, OPJ_UINT16 p_marker_id, OPJ_UINT32 p_data_len, OPJ_UINT32 p_total_size) {
    opj_marker_info_t *l_markers;
    OPJ_UINT32 l_count;
    opj_tile_index_t *l_tile_index;
    OPJ_BOOL result = 0;

    if (p_j2k == NULL) {
        // assert(p_j2k != NULL);
        return 0;
    }
    if (p_j2k->tile_index == NULL) {
        // assert(p_j2k->tile_index != NULL);
        return 0;
    }

    l_tile_index = p_j2k->tile_index;
    l_count = l_tile_index[p_tile_index].markers_count + 1;

    if (l_count > l_tile_index[p_tile_index].capacity) {
        OPJ_UINT32 new_capacity = (OPJ_UINT32)((float)l_tile_index[p_tile_index].capacity + 1.5f);
        l_tile_index[p_tile_index].capacity = new_capacity;
        
        l_markers = (opj_marker_info_t *)opj_realloc(
            l_tile_index[p_tile_index].markers,
            l_tile_index[p_tile_index].capacity * sizeof(opj_marker_info_t)
        );
        
        if (l_markers == NULL) {
            opj_free(l_tile_index[p_tile_index].markers);
            l_tile_index[p_tile_index].markers = NULL;
            l_tile_index[p_tile_index].capacity = 0;
            l_tile_index[p_tile_index].markers_count = 0;
            return 0;
        }
        
        l_tile_index[p_tile_index].markers = l_markers;
    }

    l_markers = l_tile_index[p_tile_index].markers;
    l_markers[l_tile_index[p_tile_index].markers_count].id = p_marker_id;
    l_markers[l_tile_index[p_tile_index].markers_count].len = p_data_len;
    l_markers[l_tile_index[p_tile_index].markers_count].val = p_total_size;
    l_tile_index[p_tile_index].markers_count++;

    if (p_marker_id == 0xff90) {
        l_count = l_tile_index[p_tile_index].tp_num;
        if (l_tile_index[p_tile_index].tile_parts != NULL) {
            l_tile_index[p_tile_index].tile_parts[l_count] = p_data_len;
        }
    }

    result = 1;
    return result;
}