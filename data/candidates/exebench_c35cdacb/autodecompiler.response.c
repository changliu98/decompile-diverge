int libbf_is_composed_poweroftwo(unsigned int x, unsigned int * first, unsigned int * second) {

    unsigned int count = 0;
    unsigned int pos = 0;

    if (x == 0)
        return 0;

    if (first)
        *first = 0;
    if (second)
        *second = 0;

    while (1) {
        if (x == 0)
            return 0;

        if (x & 1) {
            count++;
            if (count == 1) {
                if (first)
                    *first = pos;
            } else if (count == 2) {
                if (second)
                    *second = pos;
            } else {
                return 0;
            }
        }

        pos++;
        x >>= 1;
    }
}