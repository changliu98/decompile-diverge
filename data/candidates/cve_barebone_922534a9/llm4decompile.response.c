MOBI_RET mobi_search_links_kf7(MOBIResult *result, const unsigned char *data_start, const unsigned char *data_end) {
    const unsigned char *data;
    const unsigned char *needle1 = (const unsigned char *) "filepos=";
    const unsigned char *needle2 = (const unsigned char *) "recindex=";
    const size_t needle1_length = strlen((const char *) needle1);
    const size_t needle2_length = strlen((const char *) needle2);
    const size_t needle_length = (needle1_length > needle2_length) ? needle1_length : needle2_length;
    unsigned char last_border;
    int i;


    if (result == NULL) {
        return MOBI_PARAM_ERR;
    }
    result->start = NULL;
    result->end = NULL;
    result->value[0] = '\0';
    if (data_start == NULL || data_end == NULL) {
        return MOBI_PARAM_ERR;
    }


    if (data_start + needle_length > data_end) {
        return MOBI_SUCCESS;
    }


    last_border = '<';
    for (data = data_start; data <= data_end; data++) {
        if (*data == '<' || *data == '>') {
            last_border = *data;
        }
        if (data + needle_length <= data_end && (!memcmp(data, needle1, needle1_length) || !memcmp(data, needle2, needle2_length))) {
            if (last_border != '<') {
                data += needle_length;
                continue;
            }
            while (data >= data_start && !isspace(*data) && *data != '<') {
                data--;
            }
            result->start = ++data;
            for (i = 0; data <= data_end && !isspace(*data) && *data != '>' && i < 150; i++) {
                result->value[i] = *data;
                data++;
            }
            if (*(data - 1) == '/' && *data == '>') {
                data--;
                i--;
            }
            result->end = data;
            result->value[i] = '\0';
            return MOBI_SUCCESS;
        }
    }

    return MOBI_SUCCESS;
}