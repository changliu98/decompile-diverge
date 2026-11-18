static int
l2vpn_isid_print(netdissect_options *ndo,
                 const u_char *cp, int len)
{
    int type, subtype, sublen, tlen, tlvs, etype;

    while (len > 2) {
        type = *cp++;
        subtype = *cp++;
        ndo->ndo_printf(ndo, "\n\t      %s subTLV #%u, length: %u",
                        tok2str(isis_mt_capability_subtlv_values, "unknown", type),
                        subtype, len);
        len -= 2;
        switch (type) {
        case 1:
            if (len < 19 || cp + 19 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, "\n\t        CIST Root-ID: %08x", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
            cp += 4;
            ndo->ndo_printf(ndo, " %08x", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
            cp += 4;
            ndo->ndo_printf(ndo, ", Path Cost: %08x", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
            cp += 4;
            ndo->ndo_printf(ndo, ", Prio: %d", ((cp[0]<<8)|cp[1]));
            cp += 2;
            ndo->ndo_printf(ndo, "\n\t        RES: %d", (((cp[0]<<8)|cp[1])>>5));
            ndo->ndo_printf(ndo, ", V: %d", (((cp[0]<<8)|cp[1])>>4)&1);
            ndo->ndo_printf(ndo, ", SPSource-ID: %d", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3])&0xfffff);
            cp += 4;
            ndo->ndo_printf(ndo, ", No of Trees: %x", *cp++);
            tlvs = *cp++;
            len -= 19;
            while (tlvs) {
                if (len < 8 || cp + 8 > ndo->ndo_snapend)
                    goto trunc;
                ndo->ndo_printf(ndo, "\n\t         U:%d, M:%d, A:%d, RES:%d",
                                (*cp & 0x80) >> 7,
                                (*cp & 0x40) >> 6,
                                (*cp & 0x20) >> 5,
                                (*cp & 0x1f));
                cp++;
                ndo->ndo_printf(ndo, ", ECT: %08x", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
                cp += 4;
                ndo->ndo_printf(ndo, ", BVID: %d, SPVID: %d",
                                ((cp[0]<<16)|(cp[1]<<8)|cp[2])&0xfff,
                                (((cp[0]<<16)|(cp[1]<<8)|cp[2])>>12)&0xfff);
                cp += 3;
                len -= 8;
                tlvs--;
            }
            break;
        case 2:
            if (len < 8 || cp + 8 > ndo->ndo_snapend)
                goto trunc;
            ndo->ndo_printf(ndo, "\n\t        ISID: %08x", ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
            cp += 4;
            ndo->ndo_printf(ndo, "%04x", ((cp[0]<<8)|cp[1]));
            cp += 2;
            ndo->ndo_printf(ndo, ", RES: %d, VID: %d",
                            ((cp[0]<<8)|cp[1])&0xfff,
                            ((cp[0]<<8)|cp[1])>>12);
            cp += 2;
            len -= 8;
            while (len >= 5) {
                if (cp + 5 > ndo->ndo_snapend)
                    goto trunc;
                ndo->ndo_printf(ndo, "\n\t        T: %d, R: %d, RES: %d, ISID: %08x",
                                ((*cp & 0xc0) >> 30),
                                ((*cp & 0x3f) >> 24),
                                ((*cp & 0x3f) >> 18),
                                ((cp[0]<<24)|(cp[1]<<16)|(cp[2]<<8)|cp[3]));
                cp += 4;
                len -= 4;
            }
            break;
        default:
            goto trunc;
        }
    }
    return 0;

trunc:
    ndo->ndo_printf(ndo, "\n");
    ndo->ndo_printf(ndo, "%s", " [|isis]");
    return 1;
}