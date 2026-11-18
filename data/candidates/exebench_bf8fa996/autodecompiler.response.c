int
test_and_set(CFCMethod *self) {
    int retval = self->is_abstract;
    self->is_abstract = 1;
    return retval;
}