void ip_optprint(struct printer *p, const uint8_t *cp, int length) {
    const char *sep = "[ "; // 0xab5(%rip) -> 202f
    int option_len = 0;

    if (length == 0) {
        return;
    }

    while (length > 0) {
        // Check bounds for reading the option type
        if (p->max_length - 1 < p->max_length || cp > p->max_length - 1) {
            goto trunc;
        }

        uint8_t option = *cp;
        void (*print_func)(struct printer*, const char*, ...) = p->print_func;
        
        const char *token = tok2str(ip_option_values, "%u", option);
        print_func(p, "%s%s", sep, token);
        sep = ", "; // 0xa8f(%rip) -> 2039

        if (option == 1 || option == 0) {
            option_len = 1;
        } else {
            // Check bounds for reading the option length
            if (p->max_length - 1 < p->max_length || cp + 1 > p->max_length - 1) {
                goto trunc;
            }
            option_len = cp[1];
            if (option_len < 2) {
                print_func(p, "bad len=%d", option_len);
                return;
            }
        }

        if (option_len > length) {
            print_func(p, "bad len=%d", option_len);
            return;
        }

        // Check bounds for the entire option block
        if (option_len > 0) {
            if (p->max_length - option_len < p->max_length || cp > p->max_length - option_len) {
                goto trunc;
            }
        }

        switch (option) {
            case 0x44:
                ip_printts(p, cp, option_len);
                break;
            case 0x82:
                // Case 0x82 falls through to default
                break;
            case 0x7:
            case 0x83:
            case 0x89:
                ip_printroute(p, cp, option_len);
                break;
            case 0x94:
                if (option_len < 4) {
                    print_func(p, "bad len=%d", option_len);
                    break;
                }
                // Check bounds for reading 2 bytes at offset 2
                if (p->max_length - 1 < p->max_length || cp + 3 > p->max_length - 1) {
                    goto trunc;
                }
                uint16_t id = (cp[2] << 8) | cp[3];
                if (id != 0) {
                    print_func(p, "id=%u", id);
                }
                break;
            default:
                break;
        }

        cp += option_len;
        length -= option_len;
    }
    return;

trunc:
    p->print_func(p, "%s", tstr);
    return;
}