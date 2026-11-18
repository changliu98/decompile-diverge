static int Curl_smtp_escape_eob(struct ao *ao, size_t size)
{
    struct priv *p = ao->priv;
    struct audio_data *data = p->data;
    char *buf = p->buf;
    char *buf_end = NULL;
    size_t buf_size = 0;
    int rc;

    while (1) {
        if (buf &&!(p->buf_size & 1)) {
            buf_end = buf;
            buf = talloc_size(p->buf, p->buf_size * 2);
            if (!buf)
                MP_FATAL(p, "Failed to reallocate buffer.\n");
            buf_size = p->buf_size;
        }

        while (data->size < size) {
            if (data->size == 0)
                data->data[0] = buf[0];
            else
                data->data[data->size] = buf[data->size];
            data->size++;
        }

        if (data->size) {
            memcpy(buf + buf_size, data->data, data->size);
            buf_size += data->size;
            data->size = 0;
        }

        p->buf = buf;
        p->buf_size = buf_size;

        rc = 0;
        break;
    }

    talloc_free(buf_end);
    return rc;
}