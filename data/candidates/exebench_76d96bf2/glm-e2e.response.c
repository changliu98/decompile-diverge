void goertzel_filter_v1(struct GoertzelState *state, int16_t sample, int16_t coeff) {
    // state->s1 * state->coeff
    int32_t mult = (int32_t)state->s1 * (int32_t)state->coeff;
    
    // Arithmetic right shift by 14 (Fixed-point Q14 multiplication)
    int16_t shifted_mult = (int16_t)(mult >> 14);
    
    // shifted_mult - state->s2
    int16_t s0 = shifted_mult - state->s2;
    
    // Shift the delay line: s2 = s1
    state->s2 = state->s1;
    
    // sample >> 7 (Fixed-point scaling)
    int16_t scaled_sample = sample >> 7;
    
    // s1 = s0 + scaled_sample
    state->s1 = s0 + scaled_sample;
}