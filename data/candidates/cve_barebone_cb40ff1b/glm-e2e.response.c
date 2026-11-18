int isis_print_mt_capability_subtlv(struct netdissect_options *ndo, const uint8_t *tptr, int length) {
    int tlv_type, tlv_len;
    uint8_t subtlv_len;
    uint32_t val32;
    uint16_t val16;

    while (length > 2) {
        tlv_type = *tptr++;
        tlv_len = *tptr++;
        length -= 2;

        const char *tlv_str = tok2str(isis_mt_capability_subtlv_values, "unknown", tlv_type);
        ndo->printer(ndo, "\n\t    %s sub-TLV (0x%02x), length: %u", tlv_str, tlv_type, tlv_len);

        switch (tlv_type) {
        case 1:
            if (ndo->snapend - 0x13 < ndo->snapend || tptr + 0x13 > ndo->snapend) {
                goto trunc;
            }

            val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
            ndo->printer(ndo, "\n\t\t      MT-ID: 0x%08x", val32);
            tptr += 4;

            val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
            ndo->printer(ndo, "\n\t\t      O: %u", val32);
            tptr += 4;

            val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
            ndo->printer(ndo, "\n\t\t      A: %u", val32);
            tptr += 4;

            val16 = (tptr[0] << 8) | tptr[1];
            ndo->printer(ndo, "\n\t\t      Path Count: %u", val16);
            tptr += 2;

            val16 = (tptr[0] << 8) | tptr[1];
            ndo->printer(ndo, "\n\t\t      Preference: %u", val16 >> 5);
            
            val16 = (tptr[0] << 8) | tptr[1];
            ndo->printer(ndo, "\n\t\t      F-bit: %u", (val16 >> 4) & 1);
            
            val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
            ndo->printer(ndo, "\n\t\t      TE-class: 0x%05x", val32 & 0xfffff);
            tptr += 4;

            ndo->printer(ndo, "\n\t\t      Number of TLVs: %u", *tptr);
            subtlv_len = *tptr++;
            length -= 0x13;

            while (subtlv_len != 0) {
                if (ndo->snapend - 8 < ndo->snapend || tptr + 8 > ndo->snapend) {
                    goto trunc;
                }

                ndo->printer(ndo, "\n\t\t      Flags: 0x%02x", *tptr >> 7);
                ndo->printer(ndo, "\n\t\t      S: %u", (*tptr >> 6) & 1);
                ndo->printer(ndo, "\n\t\t      D: %u", (*tptr >> 5) & 1);
                ndo->printer(ndo, "\n\t\t      Reserved: %u", *tptr & 0x1f);
                tptr += 1;

                val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
                ndo->printer(ndo, "\n\t\t      Link Set ID: 0x%08x", val32);
                tptr += 4;

                val32 = (tptr[0] << 16) | (tptr[1] << 8) | tptr[2];
                ndo->printer(ndo, "\n\t\t      LSP-ID: 0x%03x", (val32 >> 12) & 0xfff);
                ndo->printer(ndo, "\n\t\t      Pseudonode-ID: 0x%03x", val32 & 0xfff);
                tptr += 3;

                length -= 8;
                subtlv_len--;
            }
            break;

        case 3:
            if (ndo->snapend - 8 < ndo->snapend || tptr + 8 > ndo->snapend) {
                goto trunc;
            }

            val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
            ndo->printer(ndo, "\n\t\t      MT-ID: 0x%08x", val32);
            tptr += 4;

            val16 = (tptr[0] << 8) | tptr[1];
            ndo->printer(ndo, "\n\t\t      O: %u", val16);
            tptr += 2;

            val16 = (tptr[0] << 8) | tptr[1];
            ndo->printer(ndo, "\n\t\t      A: %u, %u", val16 >> 12, val16 & 0xfff);
            tptr += 2;

            length -= 8;
            tlv_len -= 8;

            while (tlv_len >= 4) {
                if (ndo->snapend - 4 < ndo->snapend || tptr + 4 > ndo->snapend) {
                    goto trunc;
                }

                val32 = (tptr[0] << 24) | (tptr[1] << 16) | (tptr[2] << 8) | tptr[3];
                ndo->printer(ndo, "\n\t\t      R: %u", val32 >> 31);
                ndo->printer(ndo, "\n\t\t      N: %u", (val32 >> 30) & 1);
                ndo->printer(ndo, "\n\t\t      Type: %u", (val32 >> 24) & 0x3f);
                ndo->printer(ndo, "\n\t\t      Reserved: 0x%06x", val32 & 0xffffff);
                tptr += 4;

                length -= 4;
                tlv_len -= 4;
            }
            break;

        default:
            break;
        }
    }

    return 0;

trunc:
    ndo->printer(ndo, "\n\t\t");
    ndo->printer(ndo, "%s", tstr);
    return 1;
}