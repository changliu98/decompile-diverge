static void postfillAllChannels(opj_mqc_t *mqc)
{
    OPJ_UINT32 i;
    OPJ_INT32 diff;

    diff = (OPJ_INT32)mqc->bp - (OPJ_INT32)mqc->c;

    if (diff < (OPJ_INT32)(mqc->ct / 2)) {
        for (i = 0; i < mqc->ct; i++) {
            memcpy(mqc->ctab[i], mqc->ctab[i], (mqc->c - mqc->bp) * sizeof(OPJ_BYTE));
        }

        mqc->bp -= (OPJ_INT32)(mqc->c - mqc->bp);
        mqc->c -= (OPJ_INT32)(mqc->c - mqc->bp);

        for (i = 0; i < mqc->ct; i++) {
            memset(mqc->ctab[i] + mqc->c, 0, (mqc->bp - mqc->c) * sizeof(OPJ_BYTE));
        }
    }

    mqc->ctok |= 0x200;
    mqc->c += (OPJ_INT32)(mqc->ct / 2);
}