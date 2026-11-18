define OPLL_NUM_SLOTS 18

void __cdecl update_slots(OPLL *opll)
{
  OPLL_SLOT *buddy; 
  OPLL_SLOT *slot; 
  int i; 

  ++opll->eg_counter;
  
  for ( i = 0; i < OPLL_NUM_SLOTS; ++i )
  {
    slot = &opll->slot[i];
    buddy = NULL; // Replaced 0LL with NULL for readability

    // Determine the 'buddy' operator based on the slot's type.
    // Type 0: Modulator operator. Its buddy is the carrier operator (the next slot).
    if ( slot->type == 0 )
      buddy = &opll->slot[i + 1];
      
    // Type 1: Carrier operator. Its buddy points to a specific register offset.
    // (Note: The original cast to OPLL_SLOT* is preserved to avoid changing semantics).
    if ( slot->type == 1 )
      buddy = (OPLL_SLOT *)&opll->reg[72 * i + 64];

    // Apply any pending parameter updates for this slot
    if ( slot->update_requests )
      commit_slot_update(slot);

    // Calculate envelope and phase. 
    // The test_flag bits determine whether the envelope or phase is forced to reset.
    calc_envelope(slot, buddy, opll->eg_counter, opll->test_flag & 1);
    calc_phase(slot, opll->pm_phase, opll->test_flag & 4);
  }
}