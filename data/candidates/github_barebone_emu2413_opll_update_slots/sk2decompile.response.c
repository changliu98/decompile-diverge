static void update_slots(OPL3 *chip) {
  int i;
  chip->cycles++;
  for (i = 0; i < 18; i++) {
    OPL3_SLOT *slot = &chip->slot[i];
    OPL3_SLOT *next = NULL;
    if (slot->type == 0) next = &chip->slot[i + 1];
    if (slot->type == 1) next = &chip->ch[i * 0x12];
    if (slot->update) commit_slot_update(slot);
    calc_envelope(slot, next, chip->cycles, chip->mode & 1);
    calc_phase(slot, chip->eg_phase, chip->mode & 4);
  }
}