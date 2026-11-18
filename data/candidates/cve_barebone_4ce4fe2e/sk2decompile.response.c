static void gf_av1_reset_state(gf_av1_state *state, gf_int32 reset_bits) {
  gf_list *list;
  gf_list *list_tile;
  gf_size_t size;
  if (state->frame.list_tile) {
    while (gf_list_count(state->frame.list_tile)) {
      list = gf_list_pop_back(state->frame.list_tile);
      if (list->data) {
        gf_free(list->data);
      }
      gf_free(list);
    }
  }
  if (state->frame.list_tile_group) {
    while (gf_list_count(state->frame.list_tile_group)) {
      list = gf_list_pop_back(state->frame.list_tile_group);
      if (list->data) {
        gf_free(list->data);
      }
      gf_free(list);
    }
  }
  list_tile = state->frame.list_tile_group;
  list = state->frame.list_tile;
  memset(&state->frame, 0, sizeof(state->frame));
  state->frame.tile_group_type = GF_AV1_TILE_GROUP_TYPE_EMPTY;
  if (reset_bits) {
    gf_list_del(list_tile);
    gf_list_del(list);
    if (state->bs) {
      if (gf_bs_get_position(state->bs)) {
        gf_bs_get_content_no_truncate(state->bs, &state->bs_data, &size,
                                      &state->bs_bits);
      }
      gf_bs_del(state->bs);
    }
    state->bs = NULL;
  } else {
    state->frame.list_tile_group = list_tile;
    state->frame.list_tile = list;
    if (state->bs) {
      gf_bs_seek(state->bs, 0);
    }
  }
}