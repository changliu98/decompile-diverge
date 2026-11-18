static void
isoclns_print(struct netdissect_options *ndo, u_char *pp, unsigned int length, unsigned int caplen)
{
 int nlpid;
 if (caplen < 2) {
  ndo->ndo_printf("|OSI");
  return;
 }
 if (ndo->ndo_eflag) {
  ndo->ndo_printf = ndo->ndo_eflag_printf;
  ndo->ndo_printf(ndo, "OSI NLPID %s (0x%02x): ",
    val_to_str_guess(pp, nlpid_values, "Unknown", 1),
    pp[0]);
 }
 nlpid = pp[0];
 if (nlpid == 0) {
  ndo->ndo_printf("%slength: %u",
    ndo->ndo_eflag ? ", " : "",
    length);
  return;
 }
 switch (nlpid) {
 case 0x08:
  ip_print(ndo, pp + 1, length - 1);
  break;
 case 0x81:
  if (ipx_print(ndo, pp, length) == 0)
   print_data(ndo, pp, "\n\t", caplen);
  break;
 case 0x82:
  atalk_print(ndo, pp, length);
  break;
 case 0x83:
  if (atalk_ac_print(ndo, pp, length) == 0)
   print_data(ndo, pp, "\n\t", caplen);
  break;
 case 0x8e:
  atalk_rt_print(ndo, pp + 1, length - 1);
  break;
 case 0xcc:
  atalk_st_print(ndo, pp + 1, length - 1);
  break;
 case 0xcf:
  atalk_rt_print(ndo, pp + 1, length - 1);
  break;
 default:
  if (!ndo->ndo_eflag)
   ndo->ndo_printf(ndo, "OSI NLPID 0x%02x unknown",
     pp[0]);
  ndo->ndo_printf("%slength: %u",
    ndo->ndo_eflag ? ", " : "",
    length);
  if (caplen > 1)
   print_data(ndo, pp, "\n\t", caplen);
  break;
 }
}