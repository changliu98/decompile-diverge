void bgp_capabilities_print(struct bgp *bgp, const uint8_t *opt, int cap_len) {
    int i = 0;
    
    while (i < cap_len) {
        if (bgp->len < 2 || (uintptr_t)&opt[i] > (uintptr_t)bgp->data + bgp->len - 2) {
            bgp->print(bgp, "\n\t    malformed capabilities");
            return;
        }

        int cap_type = opt[i];
        int cap_opt_len = opt[i + 1];
        int remaining = cap_opt_len;

        const char *cap_str = tok2str(bgp_capcode_values, "Unknown", cap_type);
        bgp->print(bgp, "\n\t    %s (%u), length: %u", cap_str, cap_type, cap_opt_len);

        if (cap_opt_len > 0) {
            if (bgp->len < cap_opt_len || (uintptr_t)&opt[i + 2] > (uintptr_t)bgp->data + bgp->len - cap_opt_len) {
                bgp->print(bgp, "\n\t    malformed capabilities");
                return;
            }
        }

        switch (cap_type) {
            case 1: { // Multiprotocol Extensions
                const char *af_str = tok2str(af_values, "Unknown AFI", EXTRACT_16BITS(&opt[i + 2]));
                int afi = EXTRACT_16BITS(&opt[i + 2]);
                const char *safi_str = tok2str(bgp_safi_values, "Unknown SAFI", opt[i + 5]);
                bgp->print(bgp, "\n\t      AFI: %s (%u), SAFI: %s (%u)", af_str, afi, safi_str, opt[i + 5]);
                break;
            }
            case 2: // Route Refresh
            case 0x80: // Route Refresh (Old)
                break;
            case 0x40: { // Support for 4-octet AS number
                const char *flag_str = (opt[i + 2] & 0x80) ? "AS Path" : "Path";
                bgp->print(bgp, "\n\t      %s Limit: %u", flag_str, EXTRACT_16BITS(&opt[i + 2]) & 0xfff);
                
                remaining -= 2;
                int j = 4;
                while (remaining >= 4) {
                    const char *af_str = tok2str(af_values, "Unknown AFI", EXTRACT_16BITS(&opt[i + j]));
                    int afi = EXTRACT_16BITS(&opt[i + j]);
                    const char *safi_str = tok2str(bgp_safi_values, "Unknown SAFI", opt[i + j + 2]);
                    const char *dir_str = (opt[i + j + 3] & 0x80) ? "send" : "receive";
                    bgp->print(bgp, "\n\t\tAFI: %s (%u), SAFI: %s (%u), %s", af_str, afi, safi_str, opt[i + j + 2], dir_str);
                    
                    remaining -= 4;
                    j += 4;
                }
                break;
            }
            case 0x41: { // Support for 4-octet AS number
                if (cap_opt_len == 4) {
                    char as_str[20];
                    as_printf(as_str, sizeof(as_str), astostr, EXTRACT_32BITS(&opt[i + 2]));
                    bgp->print(bgp, "\n\t      4 Octet AS %s", as_str);
                }
                break;
            }
            case 0x45: { // Add Path
                int j = 2;
                if (remaining == 0) {
                    bgp->print(bgp, "\n\t      Add Path");
                } else {
                    while (remaining > 0) {
                        if (remaining < 4) {
                            bgp->print(bgp, "\n\t      malformed Add Path");
                            break;
                        }
                        const char *af_str = tok2str(af_values, "Unknown AFI", EXTRACT_16BITS(&opt[i + j]));
                        int afi = EXTRACT_16BITS(&opt[i + j]);
                        const char *safi_str = tok2str(bgp_safi_values, "Unknown SAFI", opt[i + j + 2]);
                        const char *dir_str = tok2str(bgp_add_path_recvsend, "Unknown", opt[i + j + 3]);
                        bgp->print(bgp, "\n\t\tAFI: %s (%u), SAFI: %s (%u), %s", af_str, afi, safi_str, opt[i + j + 2], dir_str);
                        
                        remaining -= 4;
                        j += 4;
                    }
                }
                break;
            }
            default: {
                bgp->print(bgp, "\n\t    unknown capability %u", cap_type);
                if (bgp->len > 1) {
                    print_unknown_data(bgp, &opt[i + 2], "\n\t      ", cap_opt_len);
                }
                break;
            }
        }

        if (bgp->len > 1 && cap_opt_len > 0) {
            print_unknown_data(bgp, &opt[i + 2], "\n\t      ", cap_opt_len);
        }

        i += cap_opt_len + 2;
    }
}