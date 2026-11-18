void aodv_ext_print(struct netdissect_options *ndo, struct aodv_ext *ep, unsigned int length)
{
    switch (ep->type) {
    case AODV_EXT_HELLO:
        if (ndo->ndo_snapend - 6 < (void *)ep
            || (void *)ep - ndo->ndo_snapend + 6 > 0
            || length < 6)
            ndo->ndo_printf(ndo, " [|hello]");
        else
            ndo->ndo_printf(ndo, "\n\text HELLO %ld ms",
                             ((((unsigned long)(*((unsigned int *)((void *) (ep + 1)))) & (unsigned long) 0x000000ffUL) << 24) | (((unsigned long)(*((unsigned int *)((void *) (ep + 1)))) & (unsigned long) 0x0000ff00UL) << 8) | (((unsigned long)(*((unsigned int *)((void *) (ep + 1)))) & (unsigned long) 0x00ff0000UL) >> 8) | (((unsigned long)(*((unsigned int *)((void *) (ep + 1)))) & (unsigned long) 0xff000000UL) >> 24)));
        break;
    default:
        ndo->ndo_printf(ndo, "\n\text %u %u", ep->type, ep->length);
    }
}