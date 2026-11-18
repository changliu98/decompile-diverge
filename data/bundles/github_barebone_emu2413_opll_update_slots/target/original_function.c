static void update_slots(OPLL *opll) {
  int i;
  opll->eg_counter++;

  for (i = 0; i < 18; i++) {
    OPLL_SLOT *slot = &opll->slot[i];
    OPLL_SLOT *buddy = NULL;
    if (slot->type == 0) {
      buddy = &opll->slot[i + 1];
    }
    if (slot->type == 1) {
      buddy = &opll->slot[i - 1];
    }
    if (slot->update_requests) {
      commit_slot_update(slot);
    }
    calc_envelope(slot, buddy, opll->eg_counter, opll->test_flag & 1);
    calc_phase(slot, opll->pm_phase, opll->test_flag & 4);
  }
}