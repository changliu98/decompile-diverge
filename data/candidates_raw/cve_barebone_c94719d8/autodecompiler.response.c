void
rip6_print(netdissect_options *ndo,
           register const u_char *cp, register u_int len)
{
    register int i, entries;
    unsigned int af;
    register const struct ng_mesg *ngm;
    register const struct ng_mesg_rply *ngmr;
    register const struct ng_mesg_req *ngmrq;

    ngm = (const struct ng_mesg *)cp;
    if ((unsigned int)len < sizeof(struct ng_mesg))
        return;

    entries = len - sizeof(struct ng_mesg);
    if (entries > len)
        return;

    i = entries;
    if (i < sizeof(struct ng_mesg_req))
        return;

    i -= sizeof(struct ng_mesg_req);

    switch (ngm->header.typecookie) {
    case NGM_RIPNG_COOKIE:
        ngmrq = (const struct ng_mesg_req *)&ngm->body[0];
        switch (ngm->header.cmd) {
        case NGM_RIPNG_REQ:
            if (entries < sizeof(struct ng_mesg_req))
                goto trunc;
            if ((entries / sizeof(struct ripng_entry)) == 1 &&
                ngmrq->num_entries == 16) {
                af = (ngmrq->address.sin6_addr.s6_addr[0] == 0 &&
                     ngmrq->address.sin6_addr.s6_addr[1] == 0 &&
                     ngmrq->address.sin6_addr.s6_addr[2] == 0 &&
                     ngmrq->address.sin6_addr.s6_addr[3] == 0) ? 1 : 0;
                if (af)
                    (*ndo->ndo_printf)(ndo, " ripng-req dump");
                else
                    goto notrip;
            } else {
                (*ndo->ndo_printf)(ndo, " ripng-req %d[%u]:",
                                   (int)(entries / sizeof(struct ripng_entry)),
                                   (unsigned int)len);
                if (i % sizeof(struct ripng_entry) != 0)
                    (*ndo->ndo_printf)(ndo, "[|ripng]");
            }
            for (cp = &ngm->body[sizeof(struct ng_mesg_req)];
                 i >= sizeof(struct ripng_entry);
                 i -= sizeof(struct ripng_entry), cp += sizeof(struct ripng_entry)) {
                if (ndo->ndo_vflag > 1)
                    (*ndo->ndo_printf)(ndo, "\n\t");
                else
                    (*ndo->ndo_printf)(ndo, " ");
                rip6_entry_print(ndo, (struct ripng_entry *)cp, 0);
            }
            break;
        case NGM_RIPNG_RESP:
            (*ndo->ndo_printf)(ndo, " ripng-resp %d:",
                               (int)(entries / sizeof(struct ripng_entry)));
            if (i % sizeof(struct ripng_entry) != 0)
                (*ndo->ndo_printf)(ndo, "[|ripng]");
            for (cp = &ngm->body[sizeof(struct ng_mesg_req)];
                 i >= sizeof(struct ripng_entry);
                 i -= sizeof(struct ripng_entry), cp += sizeof(struct ripng_entry)) {
                if (ndo->ndo_vflag > 1)
                    (*ndo->ndo_printf)(ndo, "\n\t");
                else
                    (*ndo->ndo_printf)(ndo, " ");
                rip6_entry_print(ndo, (struct ripng_entry *)cp,
                                 (unsigned int)cp[sizeof(struct ripng_entry) - 1]);
            }
            break;
        default:
            goto notrip;
        }
        break;
    case NGM_GENERIC_COOKIE:
        ngmr = (const struct ng_mesg_rply *)&ngm->body[0];
        switch (ngm->header.cmd) {
        case NGM_GENERIC_GET:
            (*ndo->ndo_printf)(ndo, " generic-get");
            if (ngmr->error)
                (*ndo->ndo_printf)(ndo, " err %d", ngmr->error);
            break;
        case NGM_GENERIC_SET:
            (*ndo->ndo_printf)(ndo, " generic-set");
            if (ngmr->error)
                (*ndo->ndo_printf)(ndo, " err %d", ngmr->error);
            break;
        case NGM_GENERIC_DEL:
            (*ndo->ndo_printf)(ndo, " generic-del");
            if (ngmr->error)
                (*ndo->ndo_printf)(ndo, " err %d", ngmr->error);
            break;
        case NGM_GENERIC_LST:
            (*ndo->ndo_printf)(ndo, " generic-lst");
            if (ngmr->error)
                (*ndo->ndo_printf)(ndo, " err %d", ngmr->error);
            break;
        default:
            goto notrip;
        }
        break;
    default:
notrip:
        (*ndo->ndo_printf)(ndo, " ripng-%d ?? %u",
                           (int)ngm->header.typecookie, (unsigned int)len);
    }

    if (ngm->header.token != 1)
        (*ndo->ndo_printf)(ndo, " [token %d]", ngm->header.token);
    return;

trunc:
    (*ndo->ndo_printf)(ndo, "[|ripng]");
}