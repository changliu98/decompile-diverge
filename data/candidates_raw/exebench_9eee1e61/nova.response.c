int func0(int *p, int *q, float u, float v, float dt, float dx) {
    *p = (1 / (2 * u)) * ((v * dt) / (2 * dx));
    return 1;
}