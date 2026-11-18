define SC_ERROR_OUT_OF_MEMORY    0xFFFFFA84

int cac_read_binary(void *card, unsigned int idx, unsigned char *buf, size_t count, void *priv) {
    struct cac_private_data *data = (struct cac_private_data *)((char *)card + 8); // Adjusted based on offset access
    int r = 0;
    struct cac_cert_data *cert = NULL;
    size_t bytes_to_read;
    unsigned char *val;
    size_t val_len;
    unsigned char type;

    // If data is already cached
    if (data->cached != 0) {
        if (idx > data->buffer_len) {
            return SC_ERROR_FILE_END_REACHED;
        }
        
        bytes_to_read = (count < (data->buffer_len - idx)) ? count : (data->buffer_len - idx);
        
        memcpy(buf, data->buffer + idx, bytes_to_read);
        return (int)bytes_to_read;
    }

    // If not cached, free any existing buffer and fetch the certificate
    free(data->buffer);
    data->buffer = NULL;
    data->buffer_len = 0;

    r = cac_cac1_get_certificate(card, &cert, &val_len);
    if (r < 0) {
        goto cleanup;
    }

    if (val_len < 1) {
        r = SC_ERROR_INVALID_DATA;
        goto cleanup;
    }

    type = cert->data[0];
    val = cert->data + 1;
    val_len = val_len - 1;

    // Check the type tag
    if ((type & 0x03) == 0x01) {
        r = SC_ERROR_WRONG_CARD;
        if (r != 0) {
            goto cleanup;
        }
    } else {
        if (val_len > 0) {
            data->buffer = malloc(val_len);
            if (data->buffer == NULL) {
                r = SC_ERROR_OUT_OF_MEMORY;
                goto cleanup;
            }
            data->buffer_len = val_len;
            memcpy(data->buffer, val, val_len);
        }
    }

    data->cached = 1;

    // Now that it's cached, read from the newly populated buffer
    bytes_to_read = (count < (data->buffer_len - idx)) ? count : (data->buffer_len - idx);

    if (bytes_to_read != 0 && data->buffer != NULL) {
        memcpy(buf, data->buffer + idx, bytes_to_read);
    }
    r = (int)bytes_to_read;

cleanup:
    if (cert != NULL) {
        free(cert);
    }

    return r;
}