static int isis_print_mt_capability_subtlv(struct netdissect_options *ndo, void *pptr, int psize)
{
    struct isis_mt_capability *mtcap;
    int i;
    unsigned int type;
    unsigned int length;
    struct isis_mt_capability_subtlv *subtlv;
    mtcap = pptr;
    while (psize >= 2) {
        type = ((unsigned int) (((unsigned char *) (mtcap))->data[0]) << 8 | ((unsigned int) (((unsigned char *) (mtcap))->data[1])));
        length = ((unsigned int) (((unsigned char *) (mtcap->length))->data[0]) << 8 | ((unsigned int) (((unsigned char *) (mtcap->length))->data[1])));
        ndo->ndo_printf("\n\t      %s subTLV #%u, length: %u",
                        isis_mt_capability_subtlv_valstring(
                            isis_mt_capability_subtlv_values,
                            "unknown", type),
                        type, length);
        psize -= 2;
        if (type == 1) {
            if (ndo->ndo_snapend - 19 <= (char *)mtcap ||
                ndo->ndo_snapend - 19 < (char *)((char *)mtcap + psize))
                goto trunc;
            ndo->ndo_printf("\n\t        CIST Root-ID: %08x",
                            ((unsigned int) (((unsigned char *) (mtcap->root))->data[0]) << 24 | ((unsigned int) (((unsigned char *) (mtcap->root))->data[1]) << 16 | ((unsigned int) (((unsigned char *) (mtcap->root))->data[2]) << 8 | ((unsigned int) (((unsigned char *) (mtcap->root))->data[3]))));
            subtlv = (struct isis_mt_capability_subtlv *)((char *)mtcap->root + 4);
            ndo->ndo_printf(" %08x",
                            ((unsigned int) (((unsigned char *) (subtlv->root))->data[0]) << 24 | ((unsigned int) (((unsigned char *) (subtlv->root))->data[1]) << 16 | ((unsigned int) (((unsigned char *) (subtlv->root))->data[2]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->root))->data[3]))));
            subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->root + 4);
            ndo->ndo_printf(", Path Cost: %08x",
                            ((unsigned int) (((unsigned char *) (subtlv->pathcost))->data[0]) << 24 | ((unsigned int) (((unsigned char *) (subtlv->pathcost))->data[1]) << 16 | ((unsigned int) (((unsigned char *) (subtlv->pathcost))->data[2]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->pathcost))->data[3]))));
            subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->pathcost + 4);
            ndo->ndo_printf(", Prio: %d",
                            ((unsigned int) (((unsigned char *) (subtlv->prio))->data[0]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->prio))->data[1])));
            subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->prio + 2);
            ndo->ndo_printf("\n\t        RES: %d",
                            ((unsigned int) (((unsigned char *) (subtlv->res))->data[0]) << 13 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[1]) << 5 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[0]) << 5 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[1]) << 13) >> 8));
            ndo->ndo_printf(", V: %d",
                            ((unsigned int) (((unsigned char *) (subtlv->res))->data[0]) << 12 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[1]) << 4 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[0]) << 4 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[1]) << 12) >> 12));
            ndo->ndo_printf(", SPSource-ID: %d",
                            ((unsigned int) (((unsigned char *) (subtlv->res))->data[0]) << 20 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[1]) << 12 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[2]) << 4 | ((unsigned int) (((unsigned char *) (subtlv->res))->data[3]))));
            subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->res + 4);
            ndo->ndo_printf(", No of Trees: %x",
                            subtlv->ntrees);
            i = subtlv->ntrees;
            subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv + 1);
            while (i) {
                if (ndo->ndo_snapend - 8 <= (char *)subtlv ||
                    ndo->ndo_snapend - 8 < (char *)((char *)subtlv + psize))
                    goto trunc;
                ndo->ndo_printf("\n\t         U:%d, M:%d, A:%d, RES:%d",
                                ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 7 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 6 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 5 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 0)),
                                ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 6 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 5 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 0)),
                                ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 5 | ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 0)),
                                ((unsigned int) (((unsigned char *) (subtlv->tree))->data[0]) << 0);
                subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->tree + 1);
                ndo->ndo_printf(", ECT: %08x",
                                ((unsigned int) (((unsigned char *) (subtlv->ect))->data[0]) << 24 | ((unsigned int) (((unsigned char *) (subtlv->ect))->data[1]) << 16 | ((unsigned int) (((unsigned char *) (subtlv->ect))->data[2]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->ect))->data[3]))));
                subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->ect + 4);
                ndo->ndo_printf(", BVID: %d, SPVID: %d",
                                ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[0]) << 16 | ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[1]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[2]) << 0) & 0xfff),
                                ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[0]) << 16 | ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[1]) << 8 | ((unsigned int) (((unsigned char *) (subtlv->bvsp))->data[2]) << 0) & 0xfff));
                subtlv = (struct isis_mt_capability_subtlv *)((char *)subtlv->bvsp + 3);
                --i;
            }
        } else if (type == 3) {
            if (ndo->ndo_snapend - 8 <= (char *)mtcap ||
                ndo->ndo_snapend - 8 < (char *)((char *)mtcap + psize))
                goto trunc;
            ndo->ndo_printf("\n\t      %s subTLV #%u, length: %u",
                            isis_mt_capability_subtlv_valstring(
                                isis_mt_capability_subtlv_values,
                                "unknown", type),
                            type, length);
            subtlv = (struct isis_mt_capability_subtlv *)