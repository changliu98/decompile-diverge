void vrrp_print(struct netdissect_options *ndo, struct ip *ip, int len, struct ip *inner_ip, int ttl)
{
    struct vrrp *vrrp = (const struct vrrp *) (ip + 1);
    int authtype = 0;
    if ((ndo->ndo_snapend - 1 < (char *) vrrp) ||
        (ndo->ndo_snapend - 1 < (char *) (vrrp + 1)))
        goto trunc;
    ndo->ndo_printf(ndo, "VRRPv%u, %s",
                    ((vrrp->vrrp_version & 0xf0) >> 4),
                    strfromindex(type2str, "unknown type (%u)",
                                 vrrp->vrrp_type));
    if (ttl != 0xff)
        ndo->ndo_printf(ndo, ", (ttl %u)", ttl);
    if (((((vrrp->vrrp_version == 2)) || ((vrrp->vrrp_version == 3))) &&
         (vrrp->vrrp_type == 1))) {
        if ((ndo->ndo_snapend - 1 < (char *) (vrrp + 1)) ||
            (ndo->ndo_snapend - 1 < (char *) (vrrp + 2)))
            goto trunc;
        ndo->ndo_printf(ndo, ", vrid %u, prio %u",
                        vrrp->vrrp_vrid, vrrp->vrrp_priority);
        if ((ndo->ndo_snapend - 1 < (char *) (vrrp + 3)) ||
            (ndo->ndo_snapend - 1 < (char *) (vrrp + 6)))
            goto trunc;
        if (vrrp->vrrp_version == 2) {
            authtype = vrrp->vrrp_authtype;
            ndo->ndo_printf(ndo, ", authtype %s",
                            strfromindex(auth2str, ((void *)0), authtype));
            ndo->ndo_printf(ndo, ", intvl %us, length %u",
                            vrrp->vrrp_intvl, len);
        } else {
            unsigned short intvl = (vrrp->vrrp_intvl & 0xff00) |
                                   (vrrp->vrrp_intvl & 0x00ff);
            ndo->ndo_printf(ndo, ", intvl %ucs, length %u",
                            intvl, len);
        }
        if (ndo->ndo_vflag) {
            int naddrs = vrrp->vrrp_naddrs;
            if (ndo->ndo_snapend - 1 < (char *) (vrrp + len) ||
                ndo->ndo_snapend - 1 < (char *) (vrrp + len + 1))
                goto trunc;
            if (cksum_check(vrrp + 1, len) != 0) {
                ndo->ndo_printf(ndo, ", (bad vrrp cksum %x)",
                                cksum_pseudo(ndo, inner_ip, vrrp + 1,
                                             len, len, 112));
            }
            if (ndo->ndo_snapend - 1 < (char *) (vrrp + len) ||
                ndo->ndo_snapend - 1 < (char *) (vrrp + len + 1))
                goto trunc;
            if (cksum_check(ndo, vrrp + 1, len,
                            ndo->ndo_snapend) != 0) {
                ndo->ndo_printf(ndo, ", (bad vrrp cksum %x)",
                                cksum_pseudo(ndo, inner_ip, vrrp + 1,
                                             len, len, 112));
            }
            ndo->ndo_printf(ndo, ", addrs");
            if (naddrs > 1)
                ndo->ndo_printf(ndo, "(%d)", naddrs);
            ndo->ndo_printf(ndo, ":");
            char delim = ' ';
            vrrp += 2;
            for (int i = 0; i < naddrs; i++) {
                if ((ndo->ndo_snapend - 1 < (char *) (vrrp)) ||
                    (ndo->ndo_snapend - 1 < (char *) (vrrp + 3)))
                    goto trunc;
                ndo->ndo_printf(ndo, "%c%s", delim,
                                ip_string(ndo, vrrp));
                delim = ',';
                vrrp += 2;
            }
            if (vrrp->vrrp_version == 2 &&
                vrrp->vrrp_authtype == 1) {
                if ((ndo->ndo_snapend - 1 < (char *) (vrrp)) ||
                    (ndo->ndo_snapend - 1 < (char *) (vrrp + 8)))
                    goto trunc;
                ndo->ndo_printf(ndo, " auth \"");
                if (cksum_check(ndo, vrrp, 8,
                                ndo->ndo_snapend) != 0) {
                    ndo->ndo_printf(ndo, "\"");
                } else {
                    ndo->ndo_printf(ndo, "\"");
                }
            }
        }
    }
    return;
trunc:
    ndo->ndo_printf(ndo, "[|vrrp]");
    return;
}