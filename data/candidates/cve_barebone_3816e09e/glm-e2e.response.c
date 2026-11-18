int mobility_opt_print(struct printer *p, const uint8_t *bp, int length) {
    int offset = 0;
    int opt_len;

    while (offset < length) {
        // Bounds check against snapend (p->unused)
        if ((uint8_t *)p->unused - 1 < (uint8_t *)p->unused ||
            bp + offset > (uint8_t *)p->unused - 1) {
            return 1;
        }

        uint8_t type = bp[offset];

        if (type == 0) {
            opt_len = 1;
        } else {
            if (offset + 1 >= length) {
                return 1;
            }
            if ((uint8_t *)p->unused - 1 < (uint8_t *)p->unused ||
                bp + offset + 1 > (uint8_t *)p->unused - 1) {
                return 1;
            }
            opt_len = bp[offset + 1] + 2;
        }

        if (offset + opt_len > length) {
            return 1;
        }
        if ((uint8_t *)p->unused - 1 < (uint8_t *)p->unused ||
            bp + offset + opt_len > (uint8_t *)p->unused - 1) {
            return 1;
        }

        switch (type) {
            case 0: // Pad1
                p->print_func("(pad1)");
                break;
            case 1: // PadN
                if (length - offset < 2) {
                    p->print_func("(padN) ");
                    return 1;
                }
                p->print_func("(padN)");
                break;
            case 2: // Binding Refresh Advice
                if (length - offset < 4) {
                    p->print_func("(refresh advice: trunc) ");
                    return 1;
                }
                p->print_func("(refresh: %u)", EXTRACT_16BITS(bp + offset + 2) << 2);
                break;
            case 3: // Alternate CoA
                if (length - offset < 18) {
                    p->print_func("(alt CoA: trunc) ");
                    return 1;
                }
                p->print_func("(alt-CoA: %s)", getname6(bp + offset + 2));
                break;
            case 4: // Nonce Index
                if (length - offset < 6) {
                    p->print_func("(nonce idx: trunc) ");
                    return 1;
                }
                uint16_t home_nonce = EXTRACT_16BITS(bp + offset + 2);
                uint16_t careof_nonce = EXTRACT_16BITS(bp + offset + 4);
                p->print_func("(nonce idx: h=%u, c=%u)", home_nonce, careof_nonce);
                break;
            case 5: // Binding Authorization Data
                if (length - offset < 12) {
                    p->print_func("(bad: trunc) ");
                    return 1;
                }
                p->print_func("(BA auth)");
                break;
            default:
                if (length - offset < 2) {
                    p->print_func("(unknown opt %u: trunc)", type);
                    return 1;
                }
                p->print_func("(unknown opt %u len=%u)", type, bp[offset + 1]);
                break;
        }

        offset += opt_len;
    }

    return 0;
}