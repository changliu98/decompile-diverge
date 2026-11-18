int
CFCMethod_set_abstract(CFCMethod *self) {
    int retval = self->is_abstract;
    self->is_abstract = 1;
    return retval;
}