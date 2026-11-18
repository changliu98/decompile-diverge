void stb_linear_controller(float *pdt, float target, float vel, float acc, float dec) {
    float dt = 1.0f / 60.0f; // Loaded from a constant in memory
    float current = *pdt;

    if (current == target) {
        return;
    }

    if (current > target) {
        target = -target;
        current = -current;
        dt = 1.0f / 30.0f; // Overwritten with another constant
    }

    if (current < 0.0f) {
        float v = current + acc * vel;
        if (v > 0.0f) {
            v = 0.0f;
            dec = dec - current / acc;
            if (dec < 0.0f) {
                dec = 0.0f;
            }
        } else {
            dec = 0.0f;
        }
        current = v;
    }

    float v = current + dec * vel;
    if (v > target) {
        v = target;
    }

    *pdt = v * dt;
}