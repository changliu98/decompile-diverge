void __cdecl update_slots(OPLL *opll)
{
  OPLL_SLOT *buddy; // [rsp+0h] [rbp-20h]
  OPLL_SLOT *slot; // [rsp+8h] [rbp-18h]
  int i; // [rsp+14h] [rbp-Ch]

  ++opll->eg_counter;
  for ( i = 0; i < 18; ++i )
  {
    slot = &opll->slot[i];
    buddy = 0LL;
    if ( !slot->type )
      buddy = &opll->slot[i + 1];
    if ( slot->type == 1 )
      buddy = (OPLL_SLOT *)&opll->reg[72 * i + 64];
    if ( slot->update_requests )
      commit_slot_update(slot);
    calc_envelope(slot, buddy, opll->eg_counter, opll->test_flag & 1);
    calc_phase(slot, opll->pm_phase, opll->test_flag & 4);
  }
}