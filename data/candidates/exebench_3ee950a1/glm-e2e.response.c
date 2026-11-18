float hpluck(struct HpluckState *state, float arg) {
    state->buf[0] += 1.0f; // 0x3f800000

    int index;
    if (state->buf[1] >= state->buf[0]) {
        index = (int)state->buf[0];
    } else {
        index = 20;
        state->buf[0] = 0.0f; // 0x00000000
    }

    // Double-precision intermediate calculations
    double temp0 = (double)state->field_20 - 1.0; // 0x3ff0000000000000
    double temp1 = (double)state->buf[index];
    double temp2 = (double)state->field_20 * (double)state->field_1c;
    
    state->field_1c = (float)(temp0 * temp1 + temp2);

    float temp3 = state->field_24 * 
                  (state->field_08 * state->buf[index] + state->field_0c * state->field_18);
    
    state->field_18 = state->buf[index];
    
    // 0x80000000 bitwise XOR is equivalent to negating the float
    state->buf[index] = state->field_10 + state->field_28 * temp3 + (-state->field_28) * state->field_14;
    
    state->buf[index] += arg;
    state->field_14 = state->buf[index];
    state->field_10 = temp3;

    return state->field_1c;
}