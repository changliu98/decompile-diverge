int rpki_rtr_pdu_print(struct netdissect_options *ndo, unsigned char *start, int indent)
{
    unsigned char *end = start;
    unsigned char *ptr = start;
    unsigned int pdu_type = *ptr++;
    unsigned int pdu_len = (((((unsigned int) (start)[1]) << 24) | (((unsigned int) (start)[2]) << 16) | (((unsigned int) (start)[3]) << 8) | ((unsigned int) (start)[4])));
    if (ndo->ndo_snapend - pdu_len < start || ndo->ndo_snapend < start + pdu_len)
        return 1;
    int hexdump = 0;
    int (*ndo_printf)(struct netdissect_options *, char *fmt, ...);
    char *prefix = ndo_get_prefix(2);
    unsigned int version = *start;
    ndo_printf(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u",
               prefix, version,
               rtr_val_tostr(&rpki_rtr_pdu_values, "Unknown", pdu_type),
               pdu_type, pdu_len);
    switch (pdu_type) {
    case PDU_TYPE_HELLO:
    case PDU_TYPE_HELLO_ACK:
    case PDU_TYPE_UPDATE:
        ndo_printf = ndo->ndo_printf;
        prefix = ndo_get_prefix(indent + 2);
        ndo_printf(ndo, "%sSession ID: 0x%04x, Serial: %u",
                   prefix,
                   ((((((unsigned int) (start)[1]) << 8) | ((unsigned int) (start)[2])) << 16) | (((((unsigned int) (start)[3]) << 8) | ((unsigned int) (start)[4])))),
                   ((((((unsigned int) (start)[5]) << 24) | (((unsigned int) (start)[6]) << 16) | (((unsigned int) (start)[7]) << 8) | ((unsigned int) (start)[8]))));
        break;
    case PDU_TYPE_ERROR:
    case PDU_TYPE_ERROR_ACK:
        break;
    case PDU_TYPE_UPDATE_ACK:
        ndo_printf = ndo->ndo_printf;
        prefix = ndo_get_prefix(indent + 2);
        ndo_printf(ndo, "%sSession ID: 0x%04x",
                   prefix,
                   ((((((unsigned int) (start)[1]) << 8) | ((unsigned int) (start)[2])) << 16) | (((((unsigned int) (start)[3]) << 8) | ((unsigned int) (start)[4])))));
        break;
    case PDU_TYPE_UPDATE_ADD:
        ndo_printf = ndo->ndo_printf;
        prefix = ndo_get_prefix(indent + 2);
        char *str = rtr_val_tostr(ndo, start + 12);
        unsigned int origin_as = (((((unsigned int) (start)[12]) << 24) | (((unsigned int) (start)[13]) << 16) | (((unsigned int) (start)[14]) << 8) | ((unsigned int) (start)[15]));
        ndo_printf(ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                   prefix, str, start[9], start[10], origin_as, start[8]);
        break;
    case PDU_TYPE_UPDATE_DEL:
        ndo_printf = ndo->ndo_printf;
        prefix = ndo_get_prefix(indent + 2);
        char *str = rtr_val_tostr(ndo, start + 12);
        unsigned int origin_as = (((((unsigned int) (start)[12]) << 24) | (((unsigned int) (start)[13]) << 16) | (((unsigned int) (start)[14]) << 8) | ((unsigned int) (start)[15]));
        ndo_printf(ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x",
                   prefix, str, start[9],