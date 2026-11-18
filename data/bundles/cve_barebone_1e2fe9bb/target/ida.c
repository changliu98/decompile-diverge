void __cdecl beep_print(netdissect_options *ndo, const u_char *bp_0, u_int length)
{
  if ( l_strnstart("MSG", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP MSG");
  }
  else if ( l_strnstart("RPY ", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP RPY");
  }
  else if ( l_strnstart("ERR ", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP ERR");
  }
  else if ( l_strnstart("ANS ", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP ANS");
  }
  else if ( l_strnstart("NUL ", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP NUL");
  }
  else if ( l_strnstart("SEQ ", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP SEQ");
  }
  else if ( l_strnstart("END", 4u, (const char *)bp_0, length) )
  {
    ndo->ndo_printf(ndo, " BEEP END");
  }
  else
  {
    ndo->ndo_printf(ndo, " BEEP (payload or undecoded)");
  }
}