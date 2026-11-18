static void
beep_print(struct netdissect_options *ndo, u_char *bp, unsigned int length)
{
  if (strn_eq("MSG", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP MSG");
  else if (strn_eq("RPY ", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP RPY");
  else if (strn_eq("ERR ", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP ERR");
  else if (strn_eq("ANS ", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP ANS");
  else if (strn_eq("NUL ", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP NUL");
  else if (strn_eq("SEQ ", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP SEQ");
  else if (strn_eq("END", 4, (char *)bp, length))
    ndo->ndo_printf(ndo, " BEEP END");
  else
    ndo->ndo_printf(ndo, " BEEP (payload or undecoded)");
}