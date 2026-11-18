int
CFCMethod_num_vars(CFCMethod *self) {
    self->num_vars++;
    return self->num_vars;
}