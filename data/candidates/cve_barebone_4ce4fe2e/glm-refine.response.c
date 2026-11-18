void __cdecl gf_av1_reset_state(AV1State *state, Bool is_destroy)
{
    GF_AV1_OBUArrayEntry *entry;
    GF_List *frame_obus_list;
    GF_List *header_obus_list;
    u32 size;

    if (!state)
        return;

    // Free all entries in the header_obus list
    if (state->frame_state.header_obus) {
        while (gf_list_count(state->frame_state.header_obus)) {
            entry = (GF_AV1_OBUArrayEntry *)gf_list_pop_back(state->frame_state.header_obus);
            if (entry->obu)
                gf_free(entry->obu);
            gf_free(entry);
        }
    }

    // Free all entries in the frame_obus list
    if (state->frame_state.frame_obus) {
        while (gf_list_count(state->frame_state.frame_obus)) {
            entry = (GF_AV1_OBUArrayEntry *)gf_list_pop_back(state->frame_state.frame_obus);
            if (entry->obu)
                gf_free(entry->obu);
            gf_free(entry);
        }
    }

    // Backup list pointers before zeroing the structure
    frame_obus_list = state->frame_state.frame_obus;
    header_obus_list = state->frame_state.header_obus;
    
    memset(&state->frame_state, 0, sizeof(state->frame_state));
    state->frame_state.is_first_frame = GF_TRUE;

    if (is_destroy) {
        // Destroy the lists themselves
        gf_list_del(frame_obus_list);
        gf_list_del(header_obus_list);

        // Extract and store bitstream content before deletion
        if (state->bs) {
            if (gf_bs_get_position(state->bs)) {
                gf_bs_get_content_no_truncate(state->bs, &state->frame_obus, &size, &state->frame_obus_alloc);
            }
            gf_bs_del(state->bs);
            state->bs = NULL;
        }
    } else {
        // Restore list pointers for reuse
        state->frame_state.frame_obus = frame_obus_list;
        state->frame_state.header_obus = header_obus_list;

        // Rewind bitstream if it exists
        if (state->bs) {
            gf_bs_seek(state->bs, 0LL);
        }
    }
}