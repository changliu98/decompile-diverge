int mobi_search_links_kf7(void *out, const unsigned char *data, const unsigned char *data_end) {
    int ret;
    const char *str1 = "filepos=";
    const char *str2 = "recindex=";
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t max_len = len1 > len2 ? len1 : len2;
    const unsigned char *p;
    const unsigned char *start;
    char tag_start;
    int i;

    if (!out) {
        return 2;
    }

    // out->end = NULL
    *(void **)((char *)out + 8) = NULL;
    // out->start = NULL
    *(void **)out = NULL;
    // out->value[0] = '\0'
    *((char *)out + 16) = '\0';

    if (!data || !data_end) {
        return 2;
    }

    if (data + max_len > data_end) {
        return 0;
    }

    p = data;
    tag_start = '<';

    while (p <= data_end) {
        if (*p == '<' || *p == '>') {
            tag_start = *p;
        }

        if (p + max_len <= data_end) {
            if (memcmp(p, str1, len1) == 0 || memcmp(p, str2, len2) == 0) {
                if (tag_start == '<') {
                    start = p;

                    // Walk backwards to find the start of the tag
                    while (1) {
                        unsigned char c = (start > data) ? 1 : 0;
                        if (!c) {
                            break;
                        }
                        if (!isspace(*start)) {
                            c = (*start != '<');
                            if (!c) {
                                break;
                            }
                        }
                        start--;
                    }

                    p = start + 1;
                    // out->start = p
                    *(void **)out = (void *)p;

                    i = 0;
                    // Extract the attribute value
                    while (1) {
                        unsigned char c = (p <= data_end) ? 1 : 0;
                        if (!c) {
                            break;
                        }
                        if (!isspace(*p)) {
                            c = (*p != '>');
                            if (!c) {
                                break;
                            }
                        }
                        if (i >= 150) {
                            break;
                        }
                        // out->value[i] = *p
                        *((char *)out + 16 + i) = *p++;
                        i++;
                    }

                    // Handle self-closing tag
                    if (*(p - 1) == '/' && *p == '>') {
                        p--;
                        i--;
                    }

                    // out->end = p
                    *(void **)((char *)out + 8) = (void *)p;
                    // out->value[i] = '\0'
                    *((char *)out + 16 + i) = '\0';
                    
                    return 0;
                }
            }
        }
        p++;
    }

    return 0;
}