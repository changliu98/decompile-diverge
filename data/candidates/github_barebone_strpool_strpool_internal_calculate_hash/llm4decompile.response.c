unsigned int strpool_internal_calculate_hash(const char *string, int length, int ignore_case)
{





    unsigned int hash = 5381;
    unsigned char c;
    int n;

    if (ignore_case) {
        for (n = 0; n < length; n++) {
            c = string[n];
            if (c >= 'a' && c <= 'z') {
                c -= 'a' - 'A';
            }
            hash = ((hash << 5) + hash) ^ c;
        }
    } else {
        for (n = 0; n < length; n++) {
            hash = ((hash << 5) + hash) ^ string[n];
        }
    }

    if (hash == 0) {
        hash = 1;
    }

    return hash;

}