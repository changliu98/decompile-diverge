void update_slots(struct State *state) {
    state->counter++;
    
    for (int i = 0; i < 18; i++) {
        struct Slot *current_slot = &state->slots[i];
        struct Slot *next_slot = NULL;
        
        if (current_slot->field_1 == 0) {
            next_slot = &state->slots[i + 1];
        }
        
        if (current_slot->field_1 == 1) {
            next_slot = &state->slots[i - 1];
        }
        
        if (current_slot->field_44 != 0) {
            calc_slot_car(current_slot);
        }
        
        commit_slot_update(current_slot, next_slot, (short)state->counter, state->flags & 1);
        calc_slot_mod(current_slot, state->field_78, state->flags & 4);
    }
}