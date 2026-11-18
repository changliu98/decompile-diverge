static size_t FAT_parse_directory(const char *s, size_t len, size_t *i, size_t *j) {
        size_t n;

        for (;;) {
                if (*i >= len)
                        goto fail;

                if (s[*i] == '\\')
                        (*i)++;
                else
                        break;
        }

        if (*i == len) {
                n = 0;
                goto done;
        }

        (*i)++;
        *j = *i;

        for (;;) {
                if (*j >= len)
                        goto fail;

                if (s[*j] == '\\')
                        (*j)++;
                else
                        break;
        }

        n = *j - *i;

 done:
        return n;

 fail:
        return SIZE_MAX;
}