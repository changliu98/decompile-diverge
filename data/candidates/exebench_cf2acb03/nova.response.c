float MP_Rand(int64_t *state) {
    float res;
    *state = (*state ^ 123459876) * 16807;
    res = 2.0f * (float)(*state / (int64_t)127773) - 1.0f;
    *state = (*state ^ 123459876) * 16807;
    if (*state < 0)
        *state = *state + 2147483647;
    res = res * 4.0f;
    *state = (*state ^ 123459876);
    return res;
}