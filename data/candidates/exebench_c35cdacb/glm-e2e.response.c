int libbf_is_composed_poweroftwo(uint32_t a, int *p1, int *p2) {
    int v1 = 0;
    int v2 = 0;

    if (a == 0) {
        return 0;
    }

    if (p1 != NULL) {
        *p1 = 0;
    }
    if (p2 != NULL) {
        *p2 = 0;
    }

    while (a != 0) {
        if (a & 1) {
            v2++;
            if (v2 == 1) {
                if (p1 != NULL) {
                    *p1 = v1;
                }
            } else if (v2 == 2) {
                if (p2 != NULL) {
                    *p2 = v1;
                }
            } else {
                return 0;
            }
        }
        v1++;
        a >>= 1;
    }

    return 1;
}