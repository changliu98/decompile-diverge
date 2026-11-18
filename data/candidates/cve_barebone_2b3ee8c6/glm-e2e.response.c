int zip_read_mac_metadata(struct archive *a, struct archive_entry *entry, struct zip *zip) {
    char *uncompressed;
    long bytes_avail;
    void *metadata;
    long local_file_header_size;
    long remaining_size;
    long bytes_to_copy;
    int eof_flag = 0;
    int r = 0;
    char *p;
    int ret;
    size_t read_size;
    const void *read_buf;
    char *state;

    state = *(char **)(((char *)a) + 0x8);
    bytes_avail = (long)archive_filter_bytes(a, 0);

    if (zip->field_18 != 0) {
        archive_set_error(a, 22, "%s", compression_name(zip->field_18));
        ret = -20;
        goto cleanup;
    }

    if (zip->field_10 > 0x400000) {
        archive_set_error(a, 22, "Mac metadata is too large: %jd bytes", zip->field_10);
        ret = -20;
        goto cleanup;
    }

    metadata = malloc(zip->field_10);
    if (metadata == NULL) {
        archive_set_error(a, 12, "Can't allocate memory for Mac metadata");
        ret = -30;
        goto cleanup;
    }

    if (bytes_avail < zip->field_0) {
        __archive_read_consume(a, zip->field_0 - bytes_avail);
    } else if (bytes_avail != zip->field_0) {
        __archive_read_seek(a, zip->field_0, 0);
    }

    local_file_header_size = zip_get_local_file_header_size(a, 0);
    __archive_read_consume(a, local_file_header_size);

    remaining_size = zip->field_8;
    bytes_to_copy = zip->field_10;
    p = (char *)metadata;

    while (!eof_flag && remaining_size > 0) {
        read_buf = __archive_read_ahead(a, 1, &read_size);
        if (read_buf == NULL) {
            archive_set_error(a, 22, "Truncated archive file");
            r = -20;
            break;
        }

        if (read_size > remaining_size) {
            read_size = remaining_size;
        }

        if (zip->field_18 == 0) {
            memcpy(p, read_buf, read_size);
            bytes_to_copy -= read_size;
            p += read_size;
            if (bytes_to_copy == 0) {
                eof_flag = 1;
            }
        } else {
            read_size = 0;
        }

        __archive_read_consume(a, read_size);
        remaining_size -= read_size;
    }

    archive_entry_copy_mac_metadata(entry, metadata, zip->field_10 - bytes_to_copy);
    __archive_read_seek(a, bytes_avail, 0);
    *state = 0;
    free(metadata);
    ret = r;

cleanup:
    return ret;
}