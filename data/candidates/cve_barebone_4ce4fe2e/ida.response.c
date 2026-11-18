void __cdecl gf_av1_reset_state(AV1State *state, Bool is_destroy)
{
  u32 size; // [rsp+Ch] [rbp-34h] BYREF
  GF_AV1_OBUArrayEntry *a_0; // [rsp+10h] [rbp-30h]
  GF_AV1_OBUArrayEntry *a; // [rsp+18h] [rbp-28h]
  GF_List *l2; // [rsp+20h] [rbp-20h]
  GF_List *l1; // [rsp+28h] [rbp-18h]
  Bool is_destroya; // [rsp+34h] [rbp-Ch]
  AV1State *statea; // [rsp+38h] [rbp-8h]

  statea = state;
  is_destroya = is_destroy;
  if ( state->frame_state.header_obus )
  {
    while ( gf_list_count(statea->frame_state.header_obus) )
    {
      a = (GF_AV1_OBUArrayEntry *)gf_list_pop_back(statea->frame_state.header_obus);
      if ( a->obu )
        gf_free(a->obu);
      gf_free(a);
    }
  }
  if ( statea->frame_state.frame_obus )
  {
    while ( gf_list_count(statea->frame_state.frame_obus) )
    {
      a_0 = (GF_AV1_OBUArrayEntry *)gf_list_pop_back(statea->frame_state.frame_obus);
      if ( a_0->obu )
        gf_free(a_0->obu);
      gf_free(a_0);
    }
  }
  l1 = statea->frame_state.frame_obus;
  l2 = statea->frame_state.header_obus;
  memset(&statea->frame_state, 0, sizeof(statea->frame_state));
  statea->frame_state.is_first_frame = GF_TRUE;
  if ( is_destroya )
  {
    gf_list_del(l1);
    gf_list_del(l2);
    if ( statea->bs )
    {
      if ( gf_bs_get_position(statea->bs) )
        gf_bs_get_content_no_truncate(statea->bs, &statea->frame_obus, &size, &statea->frame_obus_alloc);
      gf_bs_del(statea->bs);
    }
    statea->bs = 0LL;
  }
  else
  {
    statea->frame_state.frame_obus = l1;
    statea->frame_state.header_obus = l2;
    if ( statea->bs )
      gf_bs_seek(statea->bs, 0LL);
  }
}