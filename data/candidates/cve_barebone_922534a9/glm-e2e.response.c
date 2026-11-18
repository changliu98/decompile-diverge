int mobi_search_links_kf7(mobi_link_result *result, const char *data, const char *data_end) {
    const char *tag1 = "<a";      // 0x2004
    const char *tag2 = "<param";  // 0x200d
    size_t len1 = strlen(tag1);
    size_t len2 = strlen(tag2);
    size_t max_len;
    const char *p;
    char last_char = '<';
    int name_len = 0;

    if (result == NULL) {
        return 2;
    }

    result->end = NULL;
    result->start = NULL;
    result->name[0] = '\0';

    if (data == NULL || data_end == NULL) {
        return 2;
    }

    max_len = (len1 > len2) ? len1 : len2;

    if (data + max_len > data_end) {
        return 0;
    }

    p = data;

    while (p <= data_end) {
        if (*p == '<' || *p == '>') {
            last_char = *p;
        }

        if (p + max_len <= data_end) {
            if (memcmp(p, tag1, len1) == 0 || memcmp(p, tag2, len2) == 0) {
                if (last_char == '<') {
                    // Walk backwards to find the actual start of the tag
                    while (1) {
                        int stop = 0;
                        if (p < data) {
                            stop = 1;
                        } else if (isspace((unsigned char)*p)) {
                            stop = 1;
                        } else if (*p != '<') {
                            stop = 1;
                        }

                        if (!stop) {
                            break;
                        }
                        p--;
                    }

                    p++;
                    result->start = p;

                    // Extract the tag name
                    while (p <= data_end && 
                           !isspace((unsigned char)*p) && 
                           *p != '>' && 
                           name_len < 150) 
                    {
                        result->name[name_len++] = *p++;
                    }

                    // Handle self-closing tags (e.g., <br/>)
                    if (*(p - 1) == '/' && *p == '>') {
                        p--;
                        name_len--;
                    }

                    result->end = p;
                    result->name[name_len] = '\0';
                    return 0;
                }
            }
        }
        p++;
    }

    return 0;
}