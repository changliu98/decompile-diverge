void update_slots(OPLL *opll)

{
  OPLL_SLOT *slot_00;
  OPLL_SLOT *buddy;
  OPLL_SLOT *slot;
  int i;
  OPLL *opll_local;
  
  opll->eg_counter = opll->eg_counter + 1;
  for (i = 0; i < 0x12; i = i + 1) {
    slot_00 = opll->slot + i;
    buddy = (OPLL_SLOT *)0x0;
    if (slot_00->type == '\0') {
      buddy = opll->slot + (i + 1);
    }
    if (slot_00->type == '\x01') {
      buddy = opll->slot + (i + -1);
    }
    if (slot_00->update_requests != 0) {
      commit_slot_update(slot_00);
    }
    calc_envelope(slot_00,buddy,(uint16_t)opll->eg_counter,opll->test_flag & 1);
    calc_phase(slot_00,opll->pm_phase,opll->test_flag & 4);
  }
  return;
}