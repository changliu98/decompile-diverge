void
eap_print(netdissect_options *ndo,
         register const u_char *dat, register int length)
{
    register int type;
    register int subtype;
    register int len;
    register int code;
    register int i = 0;
    register const char *cp = (const char *)dat;
    register int datalength = length;

    if (cp + sizeof(struct eap_header) > (const char *)ndo->ndo_snapend ||
        cp + length < (const char *)ndo->ndo_snapend)
        goto trunc;
    if (ndo->ndo_vflag >= 2) {
        (*ndo->ndo_printf)(ndo, "%s (%u) v%u, len %u",
                          tok2str(eap_frame_type_values, "unknown", *cp),
                          *cp,
                          *(cp + 1),
                          ((unsigned)((*((const u_int8_t *)(cp + 2)) << 8) | *((const u_int8_t *)(cp + 3))))
                         );
    } else {
        (*ndo->ndo_printf)(ndo, "%s (%u) v%u, len %u",
                          tok2str(eap_frame_type_values, "unknown", *cp),
                          *cp,
                          *(cp + 1),
                          ((unsigned)((*((const u_int8_t *)(cp + 2)) << 8) | *((const u_int8_t *)(cp + 3))))
                         );
    }
    cp += sizeof(struct eap_header);
    datalength -= sizeof(struct eap_header);

    type = *cp++;
    datalength--;

    switch (type) {
    case 0: /* request or response */
        code = *cp++;
        datalength--;
        len = ((unsigned)((*((const u_int8_t *)(cp)) << 8) | *((const u_int8_t *)(cp + 1))));
        (*ndo->ndo_printf)(ndo, ", %s (%u), id %u, len %u",
                          tok2str(eap_code_values, "unknown", code),
                          code,
                          *cp,
                          len);
        cp += 2;
        datalength -= 2;
        if (len > datalength || len <= 0)
            goto trunc;
        if (code == 1 || code == 2) {
            subtype = *cp++;
            (*ndo->ndo_printf)(ndo, "\n\t\t Type %s (%u)",
                               tok2str(eap_type_values, "unknown", *cp), *cp);
            switch (subtype) {
            case 1: /* identity */
                if (len > 5) {
                    (*ndo->ndo_printf)(ndo, ", Identity: ");
                    safeputs(ndo, cp + 1, len - 5);
                }
                break;
            case 2: /* notification */
                if (len > 5) {
                    (*ndo->ndo_printf)(ndo, ", Notification: ");
                    safeputs(ndo, cp + 1, len - 5);
                }
                break;
            case 3: /* Nak (response only) */
                for (i = 5; i < len; i++) {
                    (*ndo->ndo_printf)(ndo, " %s (%u),",
                                       tok2str(eap_type_values, "unknown", *cp), *cp);
                    cp++;
                }
                break;
            case 13: /* ttls */
                (*ndo->ndo_printf)(ndo, " TTLSv%u", *cp & 0x7);
            case 18: /* tls */
                (*ndo->ndo_printf)(ndo, " flags [%s] 0x%02x,",
                                   bittok2str(eap_tls_flags_values, "none", *cp), *cp);
                cp++;
                if ((*cp & 0x80) >> 7) {
                    (*ndo->ndo_printf)(ndo, " len %u",
                                       ((unsigned)((*((const u_int8_t *)(cp)) << 24) | (*((const u_int8_t *)(cp + 1)) << 16) | (*((const u_int8_t *)(cp + 2)) << 8) | *((const u_int8_t *)(cp + 3)))));
                }
                break;
            case 43: /* fast */
                (*ndo->ndo_printf)(ndo, " FASTv%u", *cp & 0x7);
                (*ndo->ndo_printf)(ndo, " flags [%s] 0x%02x,",
                                   bittok2str(eap_tls_flags_values, "none", *cp), *cp);
                cp++;
                if ((*cp & 0x80) >> 7) {
                    (*ndo->ndo_printf)(ndo, " len %u",
                                       ((unsigned)((*((const u_int8_t *)(cp)) << 24) | (*((const u_int8_t *)(cp + 1)) << 16) | (*((const u_int8_t *)(cp + 2)) << 8) | *((const u_int8_t *)(cp + 3)))));
                }
                break;
            case 21: /* peap */
            case 25: /* mschapv2 */
                (*ndo->ndo_printf)(ndo, " subtype [%s] 0x%02x,",
                                   tok2str(eap_aka_subtype_values, "unknown", *cp), *cp);
                break;
            default:
                break;
            }
        } else {
            (*ndo->ndo_printf)(ndo, "\n\t[|EAP]");
        }
        break;
    case 1: /* success */
    case 2: /* failure */
        (*ndo->ndo_printf)(ndo, " %s", type == 1 ? "success" : "failure");
        break;
    default:
        (*ndo->ndo_printf)(ndo, "\n\t[|EAP]");
        break;
    }
    return;

trunc:
    (*ndo->ndo_printf)(ndo, "\n\t[|%s]", proto2name(ETHPROTO_EAP));
}