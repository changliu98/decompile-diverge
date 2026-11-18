uint16_t concat_hash_string(struct Buffer *buf, char *out, char flag) {
    uint16_t offset = 0x16;
    uint16_t out_offset = 0;
    uint32_t len;

    // Check if there's enough space to read the first length
    if ((uint32_t)offset + 4 >= buf->len) {
        return 0;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));
    offset += 4;

    // Check if string fits in buffer
    if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
        return 0;
    }

    strncpy(out, buf->data + offset, len);
    out_offset = (uint16_t)len;
    out[out_offset++] = ';';
    offset += (uint16_t)len;

    len = ntohl(*(uint32_t *)(buf->data + offset));
    offset += (uint16_t)len + 4;
    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        out[out_offset++] = ';';
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (!flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        out[out_offset++] = ';';
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        out[out_offset++] = ';';
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (!flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        out[out_offset++] = ';';
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    // Check if there's enough space to read the next length
    if ((uint32_t)offset + 4 >= buf->len) {
        return 0;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    len = ntohl(*(uint32_t *)(buf->data + offset));

    if (!flag) {
        offset += 4;
        if (offset >= buf->len || len >= (uint32_t)(buf->len - offset - 1)) {
            return 0;
        }
        strncpy(out + out_offset, buf->data + offset, len);
        out_offset += (uint16_t)len;
        offset += (uint16_t)len;
    } else {
        offset += (uint16_t)len + 4;
    }

    return out_offset;
}