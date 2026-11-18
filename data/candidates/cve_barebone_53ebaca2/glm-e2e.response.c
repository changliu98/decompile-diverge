void isakmp_rfc3948_print(void *arg, const uint8_t *bp, int length, const uint8_t *ep) {
    int nhdr;
    int padlen;
    int esp_print_ret;

    // Check if length is 1 and the first byte is 0xFF (IKE NAT-T Marker)
    if (length == 1) {
        if (bp[0] == 0xFF) {
            printf_like(arg, " (IKE NAT-T)");
        }
        return;
    }

    // Check if length is less than 4
    if (length < 4) {
        printf_like(arg, " (length %d)", length);
        return;
    }

    // Check if the first 4 bytes are all zero (Non-ESP Marker)
    if (bp[0] == 0x00 && bp[1] == 0x00 && bp[2] == 0x00 && bp[3] == 0x00) {
        printf_like(arg, " (Non-ESP)");
        isakmp_print(arg, bp + 4, length - 4, ep);
        return;
    }

    // Otherwise, treat as ESP
    printf_like(arg, " (ESP)");
    esp_print_ret = esp_print(arg, bp, length, ep, &nhdr, &padlen);
    
    if (esp_print_ret > 0) {
        bp += esp_print_ret;
        length -= (esp_print_ret + padlen);
        ip_print_inner(arg, bp, length, nhdr & 0xFF, ep);
    }
}