int nddissect_80211(struct netdissect_options *ndo, u_char *data, unsigned int length, unsigned int caplen, int pad, int fcslen)
{
    struct lladdr_info src; struct lladdr_info dst;
    unsigned int fc; unsigned int hdrlen; unsigned int meshdrlen;
    int type;
    struct netdissect_options *nd = ndo;
    u_char *packet = data;
    unsigned int packetlen = length;
    unsigned int origcaplen = caplen;
    int padlen = pad;
    caplen = caplen;
    if (length < fcslen) {
        nd->ndo_printf("%s", "[|802.11]");
        return caplen;
    }
    packetlen -= fcslen;
    if (caplen > packetlen) {
        fcslen = caplen - packetlen;
        caplen = packetlen;
        nd->ndo_snapend -= fcslen;
    }
    if (caplen < 2) {
        nd->ndo_printf("%s", "[|802.11]");
        return origcaplen;
    }
    fc = ((uint16_t) (((unsigned int) (packet)[0]) | ((unsigned int) (packet)[1] << 8)));
    hdrlen = nddissect_80211_hdr(nd, fc);
    if (hdrlen == 0)
        return 0;
    if (padlen)
        hdrlen = (hdrlen + 3) & ~3;
    if (nd->ndo_Hflag && (((fc & 0xc) == 0x8) && ((fc & 0x80) != 0))) {
        meshdrlen = nddissect_80211_mesh_hdr(packet + hdrlen);
        hdrlen += meshdrlen;
    } else
        meshdrlen = 0;
    if (caplen < (hdrlen)) {
        nd->ndo_printf("%s", "[|802.11]");
        return hdrlen;
    }
    if (nd->ndo_eflag)
        nddissect_80211_eflag(nd, fc, packet, hdrlen, meshdrlen);
    packetlen -= hdrlen;
    caplen -= hdrlen;
    packet += hdrlen;
    src.addr_string = etheraddr_string;
    dst.addr_string = etheraddr_string;
    type = (fc & 0xc) >> 2;
    switch (type) {
    case 0:
        nddissect_80211_mgmt(packet - hdrlen, &src.addr, &dst.addr);
        if (!nddissect_80211_mgmt_print(nd, fc, src.addr, packet, packetlen)) {
            nd->ndo_printf("%s", "[|802.11]");
            return hdrlen;
        }
        break;
    case 1:
        if (!nddissect_80211_ctrl(nd, fc, packet - hdrlen))
            goto print;
        break;
    case 2:
        if ((fc & 0x4) == 0)
            break;
        if (fc & 0x4000) {
            nd->ndo_printf("Data");
            if (!nddissect_80211_data(nd, packet))
                goto print;
        } else {
            nddissect_80211_data_hdr(fc, packet - hdrlen, &src.addr, &dst.addr);
            llc_hdrlen = nddissect_llc(nd, packet, packetlen, caplen, &src, &dst);
            if (llc_hdrlen < 0) {
                if (!nd->ndo_suppress_default_print)
                    nd->ndo_default_print(nd, packet, caplen);
                llc_hdrlen = -llc_hdrlen;
            }
            hdrlen += llc_hdrlen;
        }
        break;
    default:
        break;
    }
    return hdrlen;
print:
    nd->ndo_printf("%s", "[|802.11]");
    return hdrlen;
}