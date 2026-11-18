int decode_rt_routing_info(struct netdissect_options *ndo, struct rtattr *rta, char *buf, unsigned int len)
{
    struct rtattr *tb[-1];
    if (rta->rta_len < sizeof(rta->rta_len) ||
        ((unsigned char *)((rta)->rta_len) + (rta)->rta_len) > ndo->ndo_snapend)
        return -2;
    if (rta->rta_type == 0) {
        strlcpy(buf, len, "default route target");
        return 1;
    }
    if (rta->rta_type < RTA_UNSPEC ||
        rta->rta_type >= (__rta_max))
        return -1;
    if (rta->rta_len < sizeof(rta->rta_type) ||
        ((unsigned char *)((rta)->rta_len) + (rta)->rta_len) > ndo->ndo_snapend)
        return -2;
    tb[-1] = (struct rtattr *)((char *)rta + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ));
    tb[RTA_UNSPEC] = (struct rtattr *)((char *)rta + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (rta->rta_len - sizeof(rta->rta_type)));
    if (rtattr_parse(tb, __rta_max, rta->rta_len - sizeof(rta->rta_type)) < 0)
        return -1;
    if (tb[RTA_TARGET] == ((void *)0))
        return -1;
    strlcpy(buf, len, "origin AS: %s, route target %s",
            as2str(ndo, tb[RTA_ORIGIN], sizeof(struct asnum)),
            as2str(ndo, tb[RTA_TARGET], sizeof(struct asnum)));
    return ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (rta->rta_len - sizeof(rta->rta_type)) + sizeof(rta->rta_type);
}