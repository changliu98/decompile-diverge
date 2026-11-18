void freduce_degree(struct State *s) {
    s->field8  += (s->field18 << 4) + (s->field18 << 1) + s->field18;
    s->field7  += (s->field17 << 4) + (s->field17 << 1) + s->field17;
    s->field6  += (s->field16 << 4) + (s->field16 << 1) + s->field16;
    s->field5  += (s->field15 << 4) + (s->field15 << 1) + s->field15;
    s->field4  += (s->field14 << 4) + (s->field14 << 1) + s->field14;
    s->field3  += (s->field13 << 4) + (s->field13 << 1) + s->field13;
    s->field2  += (s->field12 << 4) + (s->field12 << 1) + s->field12;
    s->field1  += (s->field11 << 4) + (s->field11 << 1) + s->field11;
    s->field0  += (s->field10 << 4) + (s->field10 << 1) + s->field10;
}