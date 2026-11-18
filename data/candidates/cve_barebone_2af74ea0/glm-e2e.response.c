int vips_source_read_to_memory(VipsSource *source) {
    // Assertions
    if (source->decompressed == 0) {
        fprintf(stderr, "%s: %s\n", str_assertion, str_err_1);
        abort();
    }
    if (source->mmap_data != NULL) {
        fprintf(stderr, "%s: %s\n", str_assertion, str_err_2);
        abort();
    }
    if (source->data != NULL) {
        fprintf(stderr, "%s: %s\n", str_assertion, str_err_3);
        abort();
    }
    if (source->length < 0) {
        fprintf(stderr, "%s: %s\n", str_assertion, str_err_4);
        abort();
    }

    // Rewind the source
    if (vips_source_rewind(source) != 0) {
        return -1;
    }

    // Allocate a new GByteArray
    GByteArray *byte_array = g_byte_array_new();
    g_byte_array_set_size(byte_array, source->length);

    gint64 bytes_read_total = 0;
    guint8 *data_ptr = byte_array->data;

    // Read loop
    while (bytes_read_total < source->length) {
        gint64 bytes_to_read = 0x1000;
        if (bytes_to_read > source->length - bytes_read_total) {
            bytes_to_read = source->length - bytes_read_total;
        }

        gint64 bytes_read = vips_source_read(source, data_ptr, bytes_to_read);
        
        if (bytes_read == -1) {
            if (byte_array != NULL) {
                g_byte_array_unref(byte_array);
                byte_array = NULL;
            }
            return -1;
        }

        if (bytes_read == 0) {
            break;
        }

        bytes_read_total += bytes_read;
        data_ptr += bytes_read;
    }

    // Update source fields
    source->data = byte_array->data;
    source->decompressed = 0;
    source->byte_array = byte_array;

    vips_source_minimise(source);

    return 0;
}