int
ieee802_15_4_if_print(netdissect_options *ndo,
                register u_int length, register const u_char *p)
{
    unsigned int hdr_len;
    unsigned int fc, panid, seq, type, len;

    if (length < 4) {
        (*ndo->ndo_printf)(ndo, "[|802.15.4]");
        return(length);
    }

    hdr_len = 3;
    fc = p[0] | p[1] << 8;
    seq = p[2];
    p += 3;
    length -= 3;

    (*ndo->ndo_printf)(ndo, "IEEE 802.15.4 %s packet ", ftypes[(fc >> 0) & 0x7]);
    if (ndo->ndo_vflag) {
        (*ndo->ndo_printf)(ndo, "seq %02x ", seq);
    }

    type = (fc >> 10) & 0x3;
    switch (type) {
    case 0:
        if ((fc >> 6) & 0x3) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "none ");
        }
        break;
    case 1:
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "reserved destination addressing mode");
        }
        return(hdr_len);
    case 2:
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        panid = p[0] | p[1] << 8;
        p += 2;
        length -= 2;
        hdr_len += 2;
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "%04x:%04x ", panid, p[0] | p[1] << 8);
        }
        p += 2;
        length -= 2;
        hdr_len += 2;
        break;
    case 3:
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        panid = p[0] | p[1] << 8;
        p += 2;
        length -= 2;
        hdr_len += 2;
        if (length < 8) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "%04x:%s ", panid, le64addr_string(ndo, p));
        }
        p += 8;
        length -= 8;
        hdr_len += 8;
        break;
    }

    (*ndo->ndo_printf)(ndo, "< ");

    type = (fc >> 14) & 0x3;
    switch (type) {
    case 0:
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "none ");
        }
        break;
    case 1:
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "reserved source addressing mode");
        }
        return(0);
    case 2:
        if ((fc >> 6) & 0x3) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        panid = p[0] | p[1] << 8;
        p += 2;
        length -= 2;
        hdr_len += 2;
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "%04x:%04x ", panid, p[0] | p[1] << 8);
        }
        p += 2;
        length -= 2;
        hdr_len += 2;
        break;
    case 3:
        if ((fc >> 6) & 0x3) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (length < 2) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        panid = p[0] | p[1] << 8;
        p += 2;
        length -= 2;
        hdr_len += 2;
        if (length < 8) {
            (*ndo->ndo_printf)(ndo, "[|802.15.4]");
            return(hdr_len);
        }
        if (ndo->ndo_vflag) {
            (*ndo->ndo_printf)(ndo, "%04x:%s ", panid, le64addr_string(ndo, p));
        }
        p += 8;
        length -= 8;
        hdr_len += 8;
        break;
    }

    if (!ndo->ndo_qflag)
        len = print_unknown_data(ndo, p, "\n\t", length);

    return(hdr_len);
}