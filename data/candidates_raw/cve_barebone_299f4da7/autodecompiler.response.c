__attribute__((used)) static int
mlppp_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
    if (!ndo->ndo_qflag)
        ndo->ndo_printf(ndo, "MLPPP, ");
    return (ndo->ndo_printf(ndo, "seq 0x%03x, Flags [%s], length %u",
                            EXTRACT_16BITS(cp) & 0xfff,
                            bittok2str(&ppp_ml_flag_values, "none", *cp & 0xc0),
                            length));
}