void arp_print(struct netdissect_options *ndo, const struct arp_pkthdr *ap, int length, int caplen) {
    const uint8_t *bp = (const uint8_t *)ap;
    uint16_t pro, hrd, op;
    uint16_t is_atmarp = 0;

    // Bounds check
    if (ndo->ndo_snapend - 8 < (uint64_t)bp || (uint64_t)bp > ndo->ndo_snapend - 8) {
        goto trunc;
    }

    hrd = EXTRACT_16BITS(&bp[0]);
    pro = EXTRACT_16BITS(&bp[2]);
    op = EXTRACT_16BITS(&bp[6]);

    if (hrd == 0x000f || hrd == 0x0013) {
        if (hrd == 0x0013) {
            atmarp_print(ndo, ap, length, caplen);
            return;
        }
        is_atmarp = 1;
    }

    if (ap->plen > 0 && (uint64_t)(ndo->ndo_snapend - ap->plen) < ndo->ndo_snapend) {
        if ((uint64_t)(bp + 8 + (ap->hlen * 2) + ap->plen) > (uint64_t)(ndo->ndo_snapend - ap->plen)) {
trunc:
            ndo->ndo_printf(ndo, "%s", tstr);
            ndo->ndo_default_print(ndo, bp, length);
            return;
        }
    } else {
        ndo->ndo_printf(ndo, "%s", tstr);
        ndo->ndo_default_print(ndo, bp, length);
        return;
    }

    if (ndo->ndo_vflag == 0) {
        ndo->ndo_printf(ndo, "%s", "arp");
    }

    if ((pro == 0x0800 || pro == 0x1000) && ap->plen == 4 && ap->hlen != 0 && ndo->ndo_vflag != 0) {
        goto print_arp_details;
    }

    {
        const char *hrd_str = tok2str(arphrd_values, "Unknown Hardware (%u)", hrd);
        const char *pro_str = tok2str(ethertype_values, "Unknown Protocol (0x%04x)", pro);
        ndo->ndo_printf(ndo, "ARP, %s %s (len %d), %s %s (len %d)",
                        hrd_str, "Ethernet", ap->hlen, pro_str, "IPv4", ap->plen);
        if (ndo->ndo_vflag == 0) {
            goto done;
        }
    }

print_arp_details:
    {
        const char *op_str = tok2str(arpop_values, "Unknown (%u)", op);
        const char *fmt = (ndo->ndo_vflag == 0) ? ", %s" : "%s";
        ndo->ndo_printf(ndo, fmt, op_str);
    }

    switch (op - 1) {
        case 0: // ARP_REQUEST
            ndo->ndo_printf(ndo, "who-has %s", getname(bp + 8 + ap->hlen + ap->plen, 0));
            if (isnonzero(bp + 8 + ap->hlen + ap->plen, ap->hlen)) {
                ndo->ndo_printf(ndo, " tell %s", linkaddr_string(ndo, bp + 8 + ap->hlen + ap->plen, is_atmarp, ap->hlen));
            }
            ndo->ndo_printf(ndo, " tell %s", getname(bp + 8, 0));
            break;
        case 1: // ARP_REPLY
            ndo->ndo_printf(ndo, "reply %s is-at %s", 
                            getname(bp + 8 + ap->hlen, 0), 
                            linkaddr_string(ndo, bp + 8, is_atmarp, ap->hlen));
            break;
        case 2: // RARP_REQUEST
            ndo->ndo_printf(ndo, "who-is %s tell %s", 
                            linkaddr_string(ndo, bp + 8 + ap->hlen + ap->plen, is_atmarp, ap->hlen), 
                            linkaddr_string(ndo, bp + 8, is_atmarp, ap->hlen));
            break;
        case 3: // RARP_REPLY
            ndo->ndo_printf(ndo, "at %s says %s", 
                            linkaddr_string(ndo, bp + 8 + ap->hlen + ap->plen, is_atmarp, ap->hlen), 
                            getname(bp + 8 + ap->hlen * 2 + ap->plen, 0));
            break;
        case 4: // ATMARP_REQUEST
            ndo->ndo_printf(ndo, "who-has %s tell %s", 
                            linkaddr_string(ndo, bp + 8 + ap->hlen + ap->plen, is_atmarp, ap->hlen), 
                            linkaddr_string(ndo, bp + 8, is_atmarp, ap->hlen));
            break;
        case 5: // ATMARP_REPLY
            ndo->ndo_printf(ndo, "at %s says %s", 
                            linkaddr_string(ndo, bp + 8, is_atmarp, ap->hlen), 
                            getname(bp + 8 + ap->hlen, 0));
            break;
        default:
            ndo->ndo_default_print(ndo, bp, caplen);
            goto done;
    }

    ndo->ndo_printf(ndo, ", length %u", length);

done:
    return;
}