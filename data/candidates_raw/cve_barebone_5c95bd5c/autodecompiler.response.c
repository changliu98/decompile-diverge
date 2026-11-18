static int
rpki_rtr_pdu_print(netdissect_options *ndo,
                   register const u_char *cp, int indent)
{
    register unsigned pdu_type;
    register unsigned pdu_len;
    register unsigned pdu_version;
    unsigned error_code;
    unsigned encapsulated_pdu_length;
    unsigned text_length;
    unsigned tlen;
    int hexdump = 0;

    const u_char *pdu_header = cp;
    pdu_type = pdu_header[1];
    pdu_len = ((unsigned) (pdu_header[4] << 24 | pdu_header[5] << 16 | pdu_header[6] << 8 | pdu_header[7]));

    if (pdu_len > 0 || pdu_len == 0 && pdu_len <= ndo->ndo_snapend - cp) {
        if (cp + pdu_len > ndo->ndo_snapend) {
            goto trunc;
        }
    } else {
        goto trunc;
    }

    (*ndo->ndo_printf)(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u",
                       indent_string(indent),
                       pdu_header[0],
                       tok2str(rpki_rtr_pdu_values, "Unknown", pdu_type),
                       pdu_type,
                       pdu_len);

    switch (pdu_type) {
    case 0:
    case 1:
    case 7:
        (*ndo->ndo_printf)(ndo, "%sSession ID: 0x%04x, Serial: %u",
                           indent_string(indent + 2),
                           ((unsigned) (pdu_header[2] << 8 | pdu_header[3])),
                            ((unsigned) (pdu_header[8] << 24 | pdu_header[9] << 16 | pdu_header[10] << 8 | pdu_header[11])));
        break;
    case 2:
    case 8:
        break;
    case 3:
        (*ndo->ndo_printf)(ndo, "%sSession ID: 0x%04x",
                           indent_string(indent + 2),
                           ((unsigned) (pdu_header[2] << 8 | pdu_header[3])));
        break;
    case 4:
        {
            const u_char *pdu = cp;
            (*ndo->ndo_printf)(ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                               indent_string(indent + 2),
                               getname(ndo, &pdu[12]),
                               pdu[8],
                               pdu[9],
                               ((unsigned) (pdu[16] << 24 | pdu[17] << 16 | pdu[18] << 8 | pdu[19])),
                                pdu[10]);
        }
        break;
    case 6:
        {
            const u_char *pdu = cp;
            (*ndo->ndo_printf)(ndo, "%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                               indent_string(indent + 2),
                               getname6(ndo, &pdu[12]),
                               pdu[8],
                               pdu[9],
                               ((unsigned) (pdu[28] << 24 | pdu[29] << 16 | pdu[30] << 8 | pdu[31])),
                                pdu[10]);
        }
        break;
    case 10:
        {
            const u_char *pdu = cp;
            encapsulated_pdu_length = ((unsigned) (pdu[8] << 24 | pdu[9] << 16 | pdu[10] << 8 | pdu[11]));
            if (encapsulated_pdu_length > 0 || encapsulated_pdu_length == 0 && encapsulated_pdu_length <= ndo->ndo_snapend - cp) {
                if (cp + encapsulated_pdu_length > ndo->ndo_snapend) {
                    goto trunc;
                }
            } else {
                goto trunc;
            }
            tlen = pdu_len;
            error_code = ((unsigned) (pdu[2] << 8 | pdu[3]));
            (*ndo->ndo_printf)(ndo, "%sError code: %s (%u), Encapsulated PDU length: %u",
                               indent_string(indent + 2),
                               tok2str(rpki_rtr_error_codes, "Unknown", error_code),
                               error_code,
                               encapsulated_pdu_length);
            cp += 12;
            tlen -= 12;
            if (encapsulated_pdu_length > 0 && encapsulated_pdu_length <= tlen) {
                (*ndo->ndo_printf)(ndo, "%s-----encapsulated PDU-----",
                                   indent_string(indent + 4));
                if (rpki_rtr_pdu_print(ndo, cp, indent + 2)) {
                    goto trunc;
                }
            }
            cp += encapsulated_pdu_length;
            tlen -= encapsulated_pdu_length;
            text_length = 0;
            if (tlen > sizeof(text_length)) {
                text_length = ((unsigned) (cp[0] << 24 | cp[1] << 16 | cp[2] << 8 | cp[3]));
                cp += sizeof(text_length);
                tlen -= sizeof(text_length);
            }
            if (text_length > 0 || text_length == 0 && text_length <= ndo->ndo_snapend - cp) {
                if (cp + text_length > ndo->ndo_snapend) {
                    goto trunc;
                }
            } else {
                goto trunc;
            }
            if (text_length > 0 && text_length <= tlen) {
                (*ndo->ndo_printf)(ndo, "%sError text: ",
                                   indent_string(indent + 2));
                if (fn_printn(ndo, cp, text_length, ndo->ndo_snapend)) {
                    goto trunc;
                }
            }
        }
        break;
    default:
        hexdump = 1;
    }

    if (ndo->ndo_vflag >= 2 || (ndo->ndo_vflag && hexdump)) {
        print_unknown_data(ndo, cp, "\n\t  ", pdu_len);
    }

    return 0;

trunc:
    (*ndo->ndo_printf)(ndo, "[|%s]", proto2str(666, "unknown"));
    return 1;
}