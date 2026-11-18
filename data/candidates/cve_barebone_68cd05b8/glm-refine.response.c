njs_jump_off_t __cdecl njs_vmcode_typeof(njs_vm_t *vm, njs_value_t *value, njs_value_t *invld)
{
    // The `data` field of `njs_value_t` acts as a 1-byte type tag.
    // We use it to index into the `njs_vmcode_typeof_types` array to fetch the
    // corresponding static type string/value, which is then stored in `retval`.
    uint8_t type_tag = *(uint8_t *)&value->data;
    vm->retval.data = njs_vmcode_typeof_types[type_tag];

    // Advance the instruction pointer by 24 bytes.
    return 24LL;
}