__attribute__((used)) static int
njs_array_convert_to_slow_array(njs_vm_t *vm, njs_array_t *array)
{
    int         ret;
    njs_value_t obj, index;
    njs_uint_t  length;

    njs_set_array(&obj, array);

    array->flags &= ~NJS_ARRAY_IS_TYPED;
    array->flags |= NJS_ARRAY_LENGTH_SET;

    length = array->length;

    for (njs_uint_t i = 0; ; i++) {
        if (i >= length) {
            break;
        }

        switch (array->buffer[i].type) {
        case NJS_ARRAY_SPARE:
            continue;
        }

        njs_uint32_to_string(&index, i);

        ret = njs_object_property_add(vm, &obj, &index, NULL);
        if (ret == 0) {
            ret = -1;
            goto fail;
        }

        ret = njs_object_property_set(vm, &obj, &index, &array->buffer[i]);
        if (ret != 0) {
            ret = -1;
            goto fail;
        }
    }

    njs_mp_free(vm->mp, array->buffer);
    array->buffer = NULL;

    ret = 0;

fail:

    return ret;
}