void __cdecl beep_print(netdissect_options *ndo, const u_char *bp_0, u_int length)
{
  // Check standard 4-character BEEP header types
  if (beep_print_type(ndo, "MSG ", bp_0, length) ||
      beep_print_type(ndo, "RPY ", bp_0, length) ||
      beep_print_type(ndo, "ERR ", bp_0, length) ||
      beep_print_type(ndo, "ANS ", bp_0, length) ||
      beep_print_type(ndo, "NUL ", bp_0, length) ||
      beep_print_type(ndo, "SEQ ", bp_0, length))
  {
    return;
  }

  // Check the 3-character BEEP header type
  if (l_strnstart("END", 4u, (const char *)bp_0, length))
  {
    ndo->ndo_printf(ndo, " BEEP END");
    return;
  }

  // Fallback for unrecognized headers
  ndo->ndo_printf(ndo, " BEEP (payload or undecoded)");
}