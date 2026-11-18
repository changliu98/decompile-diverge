int
error(CFCMethod *self) {
    self->num_vars++;
    return self->num_vars;
}