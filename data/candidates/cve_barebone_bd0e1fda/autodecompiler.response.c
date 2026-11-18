static njs_int_t
njs_vmcode_array(njs_vm_t *vm, njs_str_t *string)
{
    njs_int_t         ret;
    njs_array_t       *array;
    u_char            *p, *end;
    njs_string_t      *s;

    s = (njs_string_t *) string;

    array = njs_array_alloc(vm, 0, s->size, sizeof(u_char));
    if ((njs_bool_t) (array != NULL)) {
        if (s->ascii) {
            p = array->u.string.data;
            end = p + array->size;

            do {
                *p = 7;
                p += sizeof(u_char);
            } while (--end);

        } else {
            array->size = 0;
        }

        njs_set_array(vm, array);

        ret = sizeof(njs_array_t);

    } else {
        ret = -1;
    }

    return ret;
}