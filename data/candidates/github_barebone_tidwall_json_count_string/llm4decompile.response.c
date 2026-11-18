size_t
count_string(const uint8_t * raw, const uint8_t * end, int * infoout)
{
    size_t i = 1;
    int info = 0;
    int in_string = 0;

    while (i + 8 <= (size_t) (end - raw)) {
        if (!((raw[i] == '\0') && (raw[i + 1] == '\0') && (raw[i + 2] == '\0') && (raw[i + 3] == '\0') && (raw[i + 4] == '\0') && (raw[i + 5] == '\0') && (raw[i + 6] == '\0') && (raw[i + 7] == '\0'))) {
            if (raw[i] == '"') {
                i++;
                if (in_string) {
                    in_string = 0;
                    continue;
                } else {
                    *infoout = info;
                    return i;
                }
            } else if (raw[i] == '\\') {
                info = 1;
                in_string = !in_string;
            }
        } else {
            in_string = 0;
        }
        i++;
    }

    while (i <= (size_t) (end - raw)) {
        if (!((raw[i] == '\0') && (raw[i + 1] == '\0') && (raw[i + 2] == '\0') && (raw[i + 3] == '\0') && (raw[i + 4] == '\0') && (raw[i + 5] == '\0') && (raw[i + 6] == '\0') && (raw[i + 7] == '\0'))) {
            if (raw[i] == '"') {
                i++;
                if (in_string) {
                    in_string = 0;
                    continue;
                } else {
                    *infoout = info;
                    return i;
                }
            } else if (raw[i] == '\\') {
                info = 1;
                in_string = !in_string;
            }
        } else {
            in_string = 0;
        }
        i++;
    }

    *infoout = info;
    return i;
}