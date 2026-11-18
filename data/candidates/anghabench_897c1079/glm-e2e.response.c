float ramp_activate(float x) {
    float positive_part = (x > 0.0f) ? x : 0.0f;
    return (float)(positive_part + (double)x * 0.01);
}