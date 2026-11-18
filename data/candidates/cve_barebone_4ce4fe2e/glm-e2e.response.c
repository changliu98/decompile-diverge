void gf_av1_reset_state(GF_AV1State *state, Bool full_reset) {
    if (state->list1 != NULL) {
        while (gf_list_count(state->list1) > 0) {
            void *item = gf_list_pop_back(state->list1);
            // Assuming item is a struct where an internal pointer is stored at offset 0x10
            if (*(void **)((char *)item + 0x10) != NULL) {
                gf_free(*(void **)((char *)item + 0x10));
            }
            gf_free(item);
        }
    }

    if (state->list2 != NULL) {
        while (gf_list_count(state->list2) > 0) {
            void *item = gf_list_pop_back(state->list2);
            if (*(void **)((char *)item + 0x10) != NULL) {
                gf_free(*(void **)((char *)item + 0x10));
            }
            gf_free(item);
        }
    }

    GF_List *list2 = state->list2;
    GF_List *list1 = state->list1;

    // Reset the 24-byte block starting at offset 0x18
    memset(&state->some_state, 0, 0x18);
    state->some_state = 1;

    if (full_reset) {
        if (list2 != NULL) gf_list_del(list2);
        if (list1 != NULL) gf_list_del(list1);

        if (state->bs != NULL) {
            if (gf_bs_get_position(state->bs) > 0) {
                u32 extra;
                gf_bs_get_content_no_truncate(state->bs, &state->data, &state->data_size, &extra);
            }
            gf_bs_del(state->bs);
        }
        state->bs = NULL;
    } else {
        state->list2 = list2;
        state->list1 = list1;

        if (state->bs != NULL) {
            gf_bs_seek(state->bs, 0);
        }
    }
}