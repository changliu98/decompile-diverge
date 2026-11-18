static int mfr_parse(struct netdissect_options *ndo, u_char *start, unsigned int length)
{
    struct mfr_header *mfhdr;
    struct mfr_ie *ie;
    unsigned int ielen; unsigned int ielen2;
    unsigned int i;
    int (*printf)(struct netdissect_options *, char *, ...);
    int (*printf2)(struct netdissect_options *, char *, ...);
    char *flagstr;
    unsigned int seqno;
    if (ndo->ndo_snapend - 4 < (char *)start ||
        start + 4 > ndo->ndo_snapend) {
        ndo->ndo_printf(ndo, "[|mfr]");
        return length;
    }
    mfhdr = (struct mfr_header *)start;
    if ((mfhdr->mfhdr_flags & 0xe0) == 0xe0 &&
        mfhdr->mfhdr_seqno == 0) {
        printf = ndo->ndo_printf;
        flagstr = mfr_flagstr(mfhdr->mfhdr_flags);
        printf(ndo, "FRF.16 Control, Flags [%s], %s, length %u",
               flagstr,
               mfr_ctrl_msgstr(mfhdr->mfhdr_msg),
               length);
        ie = (struct mfr_ie *) (mfhdr + 1);
        length -= sizeof *mfhdr;
        if (ndo->ndo_vflag) {
            while (length > sizeof *ie) {
                if (ndo->ndo_snapend - sizeof *ie < (char *)ie ||
                    ie + 1 > (struct mfr_ie *)ndo->ndo_snapend)
                    goto trunc;
                if (ie->ie_type == 0 ||
                    ie->ie_len < sizeof *ie)
                    return 3;
                if (ndo->ndo_snapend - ie->ie_len < (char *)ie ||
                    ie + ie->ie_len > (struct mfr_ie *)ndo->ndo_snapend)
                    goto trunc;
                ie++;
                length -= sizeof *ie;
            }
            return 3;
        }
    } else {
        seqno = (mfhdr->mfhdr_seqno << 7) | (mfhdr->mfhdr_flags & 0x1e);
        if ((mfhdr->mfhdr_flags & 0xe0) == 0xc0 ||
            (mfhdr->mfhdr_flags & 0xe0) == 0x80) {
            printf = ndo->ndo_printf;
            printf(ndo, "FRF.16 Frag, seq %u, Flags [%s], ",
                   seqno,
                   mfr_flagstr(mfhdr->mfhdr_flags));
            mfr_frag_print(ndo, (char *) (mfhdr + 1), length - sizeof *mfhdr);
            return sizeof *mfhdr;
        }
        printf = ndo->ndo_printf;
        printf(ndo, "FRF.16 Frag, seq %u, Flags [%s]",
               seqno,
               mfr_flagstr(mfhdr->mfhdr_flags));
        mfr_print(ndo, (char *)start, "\n\t", length);
        return 0;
    }
trunc:
    ndo->ndo_printf(ndo, "[|mfr]");
    return length;
}