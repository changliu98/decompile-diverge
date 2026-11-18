void gf_av1_reset_state(AV1State *state,Bool is_destroy)

{
  u32 uVar1;
  u64 uVar2;
  u32 size;
  GF_AV1_OBUArrayEntry *a_1;
  GF_AV1_OBUArrayEntry *a;
  GF_List *l2;
  GF_List *l1;
  Bool is_destroy_local;
  AV1State *state_local;
  
  is_destroy_local = is_destroy;
  state_local = state;
  if ((state->frame_state).header_obus != (GF_List *)0x0) {
    while (uVar1 = gf_list_count((state_local->frame_state).header_obus), uVar1 != 0) {
      a = gf_list_pop_back((state_local->frame_state).header_obus);
      if (a->obu != (u8 *)0x0) {
        gf_free(a->obu);
      }
      gf_free(a);
    }
  }
  if ((state_local->frame_state).frame_obus != (GF_List *)0x0) {
    while (uVar1 = gf_list_count((state_local->frame_state).frame_obus), uVar1 != 0) {
      a_1 = gf_list_pop_back((state_local->frame_state).frame_obus);
      if (a_1->obu != (u8 *)0x0) {
        gf_free(a_1->obu);
      }
      gf_free(a_1);
    }
  }
  l1 = (state_local->frame_state).frame_obus;
  l2 = (state_local->frame_state).header_obus;
  memset(&state_local->frame_state,0,0x18);
  (state_local->frame_state).is_first_frame = GF_TRUE;
  if (is_destroy_local == GF_FALSE) {
    (state_local->frame_state).frame_obus = l1;
    (state_local->frame_state).header_obus = l2;
    if (state_local->bs != (GF_BitStream *)0x0) {
      gf_bs_seek(state_local->bs,0);
    }
  }
  else {
    gf_list_del(l1);
    gf_list_del(l2);
    if (state_local->bs != (GF_BitStream *)0x0) {
      uVar2 = gf_bs_get_position(state_local->bs);
      if (uVar2 != 0) {
        gf_bs_get_content_no_truncate
                  (state_local->bs,&state_local->frame_obus,&size,&state_local->frame_obus_alloc);
      }
      gf_bs_del(state_local->bs);
    }
    state_local->bs = (GF_BitStream *)0x0;
  }
  return;
}