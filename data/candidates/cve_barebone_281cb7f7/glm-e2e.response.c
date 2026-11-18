int dhcpv6_print(void **printer_obj, const unsigned char *cp, unsigned int length, int indent) {
    unsigned int offset = 0;
    int ret;

    while (offset < length) {
        const unsigned char *tp = cp + offset;
        
        // Extract option code and length (Network byte order / Big-endian)
        unsigned short optcode = (tp[0] << 8) | tp[1];
        unsigned short optlen = (tp[2] << 8) | tp[3];
        const unsigned char *optval = tp + 4;

        // Call the print function pointer (e.g. printf-like)
        ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, "\n\t");

        // Print indentation
        for (int i = indent; i > 0; i--) {
            ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, " ");
        }

        // Print option name and length
        const char *optstr = tok2str(dh6opt_str, "opt", optcode);
        ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, "%s (len %d)", optstr, optlen + 4);

        // Handle specific DHCPv6 options
        if (optcode == 23 || optcode == 31) {
            // OPTION_DNS_SERVERS (23) or OPTION_NTP_SERVERS (31)
            if (optlen % 16 != 0) {
                ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, "%s", " ");
                return -1;
            }
            
            for (int i = 0; i < optlen; i += 16) {
                const char *name = getname6(optval + i);
                ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, "%s", name);
            }
            
        } else if (optcode == 24) {
            // OPTION_DOMAIN_LIST (24)
            const unsigned char *dp = optval;
            while (dp < optval + optlen) {
                ((int (*)(void *, const char *, ...))*printer_obj)(printer_obj, "%s", " ");
                dp = ns_nprint(dp, optval + optlen);
                if (dp == NULL) {
                    return -1;
                }
            }
        }

        offset += 4 + optlen;
    }
    
    return 0;
}