int njs_array_convert_to_slow_array(njs_thing_t *thing, njs_array_t *array) {
    njs_thing_t set_array_thing;
    njs_thing_t str_index;
    njs_property_t *prop;
    uint32_t i;
    int ret;

    njs_set_array(&set_array_thing, array);

    // Clear the lowest bit of the first byte (flags)
    array->flags &= 0xFE;

    for (i = 0; i < array->count; i++) {
        // Check if the item type (first byte of the value) is 7 (likely NJS_UNDEFINED or similar)
        if (array->items[i].data1 == 7) {
            continue;
        }

        njs_uint32_to_string(&str_index, i);
        
        // The 4th argument (rcx) is zeroed out before the call
        prop = njs_object_property_add(thing->object, &set_array_thing, &str_index, 0);
        if (prop == NULL) {
            ret = -1;
            goto done;
        }

        // Copy the 16-byte value from the array to the newly added property
        prop->data1 = array->items[i].data1;
        prop->data2 = array->items[i].data2;
    }

    // Free the memory pool associated with the array items
    njs_mp_free(thing->object, array->items);
    array->items = NULL;
    ret = 0;

done:
    return ret;
}