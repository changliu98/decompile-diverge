void advance_kpos(struct kpos *p) {
    p->field0 = (p->field0 + 1) % 41;
    p->field1 = (p->field1 + 1) % 31;
    p->field2 = (p->field2 + 1) % 29;
    p->field3 = (p->field3 + 1) % 26;
    p->field4 = (p->field4 + 1) % 23;
}