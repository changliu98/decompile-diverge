void gf_av1_reset_state(AV1State *state, Bool is_destroy)
{
        GF_List *frame_obus = NULL;
        GF_List *header_obus = NULL;

        if (state->frame_state.header_obus) {
                while (gf_list_count(state->frame_state.header_obus)) {
                        GF_AV1_OBUArrayEntry *entry = gf_list_pop_back(state->frame_state.header_obus);
                        if (entry->obu)
                                gf_free(entry->obu);
                        gf_free(entry);
                }
        }

        if (state->frame_state.frame_obus) {
                while (gf_list_count(state->frame_state.frame_obus)) {
                        GF_AV1_OBUArrayEntry *entry = gf_list_pop_back(state->frame_state.frame_obus);
                        if (entry->obu)
                                gf_free(entry->obu);
                        gf_free(entry);
                }
        }

        frame_obus = state->frame_state.frame_obus;
        header_obus = state->frame_state.header_obus;

        memset(&state->frame_state, 0, sizeof(state->frame_state));
        state->frame_state.is_first_frame = GF_TRUE;

        if (is_destroy) {
                gf_list_del(frame_obus);
                gf_list_del(header_obus);

                if (state->bs) {
                        if (gf_bs_get_position(state->bs))
                                gf_bs_get_content_no_truncate(state->bs, &state->frame_obus, &state->frame_obus_size, &state->frame_obus_alloc);
                        gf_bs_del(state->bs);
                }
                state->bs = NULL;
        } else {
                state->frame_state.frame_obus = frame_obus;
                state->frame_state.header_obus = header_obus;

                if (state->bs)
                        gf_bs_seek(state->bs, 0);
        }
}