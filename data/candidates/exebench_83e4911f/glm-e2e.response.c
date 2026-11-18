float pluck(struct PluckState *s, float input) {
    s->x[0] += 1.0f;
    float old_val;
    float ret;

    if (s->x[1] > s->x[0]) {
        int i = (int)s->x[0];
        old_val = s->x[i];
        s->x[i] = input + s->a * s->x[i] + s->b * s->x[i - 1];
        ret = old_val;
    } else {
        int i = 4;
        s->x[0] = 0.0f;
        old_val = s->x[i];
        int j = (int)(s->x[1] - 1.0);
        s->x[i] = input + s->a * s->x[i] + s->b * s->x[j];
        ret = old_val;
    }

    return ret;
}