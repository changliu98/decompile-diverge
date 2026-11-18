void gf_av1_reset_state(struct AV1State *state, enum Bool is_destroy)
{
  struct AV1FrameState *frame_state = &state->frame_state;
  if (frame_state->header_obus)
  {
    while (av1_list_is_not_empty(frame_state->header_obus))
    {
      struct GF_AV1_OBUArrayEntry *entry = (GF_AV1_OBUArrayEntry *)av1_list_get(frame_state->header_obus);
      if (entry->obu)
      {
        av1_obu_free(entry->obu);
      }
      av1_free(entry);
    }
  }
  if (frame_state->frame_obus)
  {
    while (av1_list_is_not_empty(frame_state->frame_obus))
    {
      struct GF_AV1_OBUArrayEntry *entry = (GF_AV1_OBUArrayEntry *)av1_list_get(frame_state->frame_obus);
      if (entry->obu)
      {
        av1_obu_free(entry->obu);
      }
      av1_free(entry);
    }
  }
  struct GF_List *frame_obus = frame_state->frame_obus;
  struct GF_List *header_obus = frame_state->header_obus;
  memset(frame_state, 0, sizeof(*frame_state));
  frame_state->is_first_frame = GF_TRUE;
  if (is_destroy)
  {
    av1_list_destroy(frame_obus);
    av1_list_destroy(header_obus);
    if (state->bs)
    {
      unsigned int size = 0;
      if (av1_is_bitstream_valid(state->bs))
      {
        av1_get_bitstream_size(state->bs, &size);
        av1_get_bitstream_data(state->bs, state->frame_obus);
      }
      av1_bitstream_free(state->bs);
    }
    state->bs = ((void *)0);
  }
  else
  {
    frame_state->frame_obus = frame_obus;
    frame_state->header_obus = header_obus;
    if (state->bs)
    {
      av1_set_bitstream_data(state->bs, ((void *)0));
    }
  }
}