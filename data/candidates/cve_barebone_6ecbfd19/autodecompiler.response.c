static int
ieee802_11_print(netdissect_options *ndo,
                         register const u_char *p, register u_int length,
                         register u_int caplen, int pad, u_int fcslen)
{
    struct lladdr_info src, dst;
    unsigned short fc;
    unsigned ftype, fsubtype;
    unsigned hdrlen, meshdrlen;
    int llc_hdrlen;
    unsigned orig_caplen = caplen;

    if (length < fcslen) {
        (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
        return (caplen);
    }
    length -= fcslen;

    if (caplen > length) {
        fcslen = caplen - length;
        caplen -= fcslen;
        ndo->ndo_snapend -= fcslen;
    }

    if (caplen < 3) {
        (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
        return (orig_caplen);
    }

    fc = ((p)[0] | ((p)[1] << 8));

    hdrlen = extract_header_length(ndo, fc);
    if (hdrlen == 0) {
        return (0);
    }

    if (pad) {
        hdrlen = (hdrlen + 3) & ~3;
    }

    if (ndo->ndo_qflag && (((((fc) >> 2) & 0x3) == 2) && ((((fc) >> 4) & 0xf) & 0x8))) {
        meshdrlen = extract_mesh_header_length(p + hdrlen);
        hdrlen += meshdrlen;
    } else {
        meshdrlen = 0;
    }

    if (caplen < hdrlen) {
        (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
        return (hdrlen);
    }

    if (ndo->ndo_vflag) {
        ieee_802_11_hdr_print(ndo, fc, p, hdrlen, meshdrlen);
    }

    length -= hdrlen;
    caplen -= hdrlen;
    p += hdrlen;

    src.addr_string = etheraddr_string;
    dst.addr_string = etheraddr_string;

    ftype = ((fc) >> 2) & 0x3;
    switch (ftype) {

    case 0:
        get_mgmt_src_dst_mac(p-hdrlen, &src, &dst);

        if (!mgmt_body_print(ndo, fc, src.addr, p, length)) {
            (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
            return (hdrlen);
        }
        break;

    case 1:
        break;

    case 2:
        if (!ctrl_body_print(ndo, fc, p-hdrlen, hdrlen)) {
            (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
            return (hdrlen);
        }
        break;

    case 3:
        if (((((fc) >> 4) & 0xf) & 0x4) != 0) {
            return (hdrlen);
        }
        if ((((fc) & 0x4000) != 0)) {
            (*ndo->ndo_printf)(ndo, "Data");
            if (!wep_print(ndo, p)) {
                (*ndo->ndo_printf)(ndo, "%s", "[|802.11]");
                return (hdrlen);
            }
        } else {
            fsubtype = ((fc) >> 4) & 0xf;
            get_data_src_dst_mac(fc, p-hdrlen, &src, &dst);
            llc_hdrlen = llc_print(ndo, p, length, caplen, &src, &dst);
            if (llc_hdrlen < 0) {
                if (!ndo->ndo_suppress_default_print)
                    (*ndo->ndo_default_print)(ndo, p, caplen);
                llc_hdrlen = -llc_hdrlen;
            }
            hdrlen += llc_hdrlen;
        }
        break;
    }

    return (hdrlen);
}