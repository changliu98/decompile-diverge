void
osi_print(netdissect_options *ndo,
          register const u_char *p, register u_int length, register u_int caplen)
{
    int nlpid;
    if (caplen <= 1) {
 (*ndo->ndo_printf)(ndo, "|OSI");
 return;
    }
    if (ndo->ndo_qflag)
 (*ndo->ndo_printf)(ndo, "OSI NLPID %s (0x%02x): ",
      tok2str(&nlpid_values,"Unknown",*p),
      *p);
    nlpid = *p++;
    if (nlpid == 0) {
 (*ndo->ndo_printf)(ndo, "%slength: %u",
     ndo->ndo_qflag ? "" : ", ",
     length);
 return;
    }

    switch (nlpid) {

    case NL_PID_Q933:
 (*ndo->ndo_printf)(ndo, "\n\t");
 q933_print(ndo, p, length - 1);
 break;

    case NL_PID_IPV4:
 (*ndo->ndo_printf)(ndo, "\n\t");
 ip_print(ndo, p, length - 1);
 break;

    case NL_PID_IPV6:
 (*ndo->ndo_printf)(ndo, "\n\t");
 ip6_print(ndo, p, length - 1);
 break;

    case NL_PID_NSAP:
 (*ndo->ndo_printf)(ndo, "\n\t");
 clnp_print(ndo, p, length);
 break;

    case NL_PID_ESIS:
 (*ndo->ndo_printf)(ndo, "\n\t");
 esis_print(ndo, p, length);
 break;

    case NL_PID_ISIS:
 (*ndo->ndo_printf)(ndo, "\n\t");
 if (!isis_print(ndo, p, length))
     print_unknown_data(ndo,p,"\n\t",caplen);
 break;

    case NL_PID_CLNP:
 (*ndo->ndo_printf)(ndo, "\n\t");
 clnp_print(ndo, p, length);
 break;

    case NL_PID_PPP:
 (*ndo->ndo_printf)(ndo, "\n\t");
 ppp_print(ndo, p, length - 1);
 break;

    case NL_PID_CCITT:
 (*ndo->ndo_printf)(ndo, "\n\t");
 ccitt_print(ndo, p, length);
 break;

    default:
 if (!ndo->ndo_qflag)
     (*ndo->ndo_printf)(ndo, "OSI NLPID 0x%02x unknown", nlpid);
 (*ndo->ndo_printf)(ndo, "%slength: %u",
     ndo->ndo_qflag ? "" : ", ",
     length);
 if (caplen > 1)
     print_unknown_data(ndo,p,"\n\t",caplen);
 break;
    }
}