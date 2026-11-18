long njs_vmcode_array(struct njs_vm *vm, struct njs_op *op)
{
    struct njs_array *array;
    struct njs_value *v;
    unsigned int i;
    if ((array = njs_get_array(vm, ((void *)0), op->arg, 8)) == ((void *)0))
        return -1;
    if (op->arg2) {
        for (v = array->start, i = array->length; i > 0; v++, i--)
            v->data = 7;
    }
    else
        array->length = 0;
    njs_set_value(&vm->retval, array);
    return (8 + 1 + 1);
}