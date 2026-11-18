float reson(float arg, struct Filter *state) {
    // Calculate the new output sample
    float temp = state->field0 * arg + state->field1 * state->field3 - state->field2 * state->field4;
    
    // Shift the state registers
    state->field4 = state->field3;
    state->field3 = temp;
    
    return temp;
}