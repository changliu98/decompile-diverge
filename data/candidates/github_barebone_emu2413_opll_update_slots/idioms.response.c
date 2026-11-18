void update_slots(struct opll *opll)
{
  int i;
  opll->eg_counter++;
  for (i = 0; i < 18; i++) {
    struct opll_slot *slot = &opll->slot[i];
    struct opll_slot *buddy = ((void *)0);
    if (slot->type == 0)
      buddy = &opll->slot[i + 1];
    if (slot->type == 1)
      buddy = &opll->reg[i * 9];
    if (slot->update_requests > 0)
      opll_update_slot(slot);
    opll_update_eg(slot, buddy, opll->eg_counter, opll->test_flag & 0x01);
    opll_update_pm(slot, opll->pm_phase, opll->test_flag & 0x04);
  }
}