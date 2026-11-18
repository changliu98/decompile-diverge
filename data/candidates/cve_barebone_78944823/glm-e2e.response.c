int sample_conv_regsub(struct args *args, struct output *out, void *unused) {
    struct regex *reg = args->reg;
    struct trash_chunk *chunk = get_trash_chunk();
    const char *str = out->str;
    const char *end = out->str + out->len;
    int match_len = 0;
    int flags = 0;

    while (1) {
        if (!((args->flags & 2) || (flags & 1))) {
            if (regex_exec_match2(reg, str, end - str, &match_len, 10) == 0) {
                break;
            }
        }

        if (match_len == 0) {
            match_len = end - str;
        }

        int copy_len = chunk->size - chunk->len;
        if (copy_len != 0 && match_len > 0) {
            if (copy_len > match_len) {
                copy_len = match_len;
            }
            memcpy(chunk->ptr + chunk->len, str, copy_len);
            chunk->len += copy_len;
        }

        if (match_len == 0) {
            break;
        }

        struct trash_chunk *rep_chunk = alloc_trash_chunk();
        if (!rep_chunk) {
            break;
        }

        rep_chunk->len = exp_replace(rep_chunk, rep_chunk->size, str, args->replace_str, &match_len);

        copy_len = rep_chunk->size - rep_chunk->len;
        if (copy_len != 0) {
            if ((long)copy_len > rep_chunk->len) {
                copy_len = rep_chunk->len;
            }
            memcpy(chunk->ptr + chunk->len, rep_chunk->ptr, copy_len);
            chunk->len += copy_len;
        }

        free_trash_chunk(rep_chunk);

        if (str >= end) {
            break;
        }

        if (match_len == 0) {
            if (chunk->len < chunk->size) {
                chunk->ptr[chunk->len++] = str[match_len];
            }
            match_len++;
        }

        str += match_len;
        flags |= 1;
    }

    out->size = chunk->size;
    out->str = chunk->ptr;
    out->len = chunk->len;
    out->flags = chunk->flags; // Assuming offset 0x18 corresponds to flags

    return 1;
}