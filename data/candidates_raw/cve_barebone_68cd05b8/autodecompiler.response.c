static size_t
njs_vmcode_typeof(njs_vm_t *vm, u_char *start, u_char *end)
{
    vm->retval.u.string = njs_vmcode_typeof_types[*start].string;
    vm->retval.type = njs_vmcode_typeof_types[*start].type;

    return sizeof(njs_vmcode_typeof_t);
}