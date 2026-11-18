static gboolean latm_dmx_process(GF_Filter_State *filter_state) {
  GF_Filter_LATM_DMX_State *state = gf_filter_get_udta(filter_state);
  GF_Filter_Pck *pck;
  unsigned char *data;
  unsigned char frame[4096];
  unsigned int data_len;
  unsigned int pck_len;
  unsigned int pos;
  unsigned int frame_len;
  unsigned char *frame_data;
  GF_SAP sap;
  GF_BS bs;
  GF_Filter_Pck *out_pck;
  unsigned long long cts = -1;
  if (state->error) return state->error;
  if (state->dur.len == 0) latm_dmx_check_dur(filter_state, state);
  if (state->out_pid && state->eos == GF_TRUE) return 0;
  pck = gf_filter_pid_get_packet(state->in_pid);
  if (pck == NULL) {
    if (gf_filter_pid_is_eos(state->in_pid) == GF_TRUE) return 0;
    if (state->buffer_len == 0) {
      if (state->out_pid) gf_filter_pid_set_eos(state->out_pid);
      if (state->out_pck) gf_filter_pck_unref(state->out_pck);
      state->out_pck = NULL;
      return 1;
    }
  }
  data = gf_filter_pck_get_data(pck, &data_len);
  if (state->cts_present && pck) cts = gf_filter_pck_get_cts(pck);
  pck_len = state->buffer_len;
  if (pck && state->drop_len == 0) {
    if (state->buffer_len + data_len > state->buffer_size) {
      state->buffer_size = state->buffer_len + data_len;
      state->buffer =
          (unsigned char *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(
              state->buffer, state->buffer_size);
    }
    memcpy(state->buffer + state->buffer_len, data, data_len);
    state->buffer_len += data_len;
  }
  if (state->bs == NULL) {
    state->bs = gf_bs_new(state->buffer, state->buffer_len, 0);
  } else {
    gf_bs_reassign_buffer(state->bs, state->buffer, state->buffer_len);
  }
  if (state->drop_len) {
    gf_bs_seek(state->bs, state->drop_len - 1);
    state->drop_len = 0;
  }
  if (cts == -1) pck_len = 0;
  while (1) {
    pos = gf_bs_get_position(state->bs);
    frame_len = 4096;
    if (latm_dmx_sync_frame_bs(state->bs, &state->latm_header, &frame_len,
                               frame, 0) == GF_TRUE) {
      if (pck) {
        pos = gf_bs_get_position(state->bs);
        memmove(state->buffer, state->buffer + pos, state->buffer_len - pos);
        state->buffer_len -= pos;
        gf_filter_pid_drop_packet(state->in_pid);
        return 0;
      } else {
        state->buffer_len = 0;
        return latm_dmx_process(filter_state);
      }
    }
    if (state->check_dur &&
        state->cts + state->latm_header.frame_size >=
            (unsigned int)(latm_dmx_frame_size[state->frame_size_index] *
                           state->dur_mult))
      state->check_dur = GF_TRUE;
    latm_dmx_check_pid(filter_state, state);
    if (state->eos == GF_TRUE) {
      state->drop_len = pos + 1;
      return 0;
    }
    if (state->check_dur == GF_TRUE) {
      sap = GF_SAP_LATM;
      out_pck = gf_filter_pck_new_alloc(state->out_pid, frame_len, &frame_data);
      if (state->out_pck) gf_filter_pck_merge_properties(state->out_pck, out_pck);
      memcpy(frame_data, frame, frame_len);
      gf_filter_pck_set_cts(out_pck, state->cts);
      gf_filter_pck_set_duration(out_pck, state->latm_header.frame_size);
      gf_filter_pck_set_framing(out_pck, GF_FALSE, GF_FALSE);
      if (state->latm_header.object_type == 0x73616d73) {
        if (frame_len && (frame_data[0] & 0x80) &&
            state->sap_sam == GF_TRUE) {
          state->sap_sam = GF_FALSE;
          gf_filter_pck_set_sap(out_pck, GF_SAP_LATM);
        } else {
          sap = GF_SAP_SAM;
          state->sap_sam = GF_TRUE;
        }
      }
      gf_filter_pck_set_sap(out_pck, sap);
      gf_filter_pck_send(out_pck);
    } else {
      latm_dmx_update_cts(state);
    }
    if (pck_len) {
      pos = gf_bs_get_position(state->bs);
      if (pos >= pck_len) {
        pck_len = 0;
        if (state->out_pck) gf_filter_pck_unref(state->out_pck);
        state->out_pck = pck;
        if (pck) gf_filter_pck_ref_props(&state->out_pck);
      }
    }
  }
  return 0;
}