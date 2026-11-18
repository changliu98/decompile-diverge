void beep_print(netdissect_options *ndo,u_char *bp,u_int length)

{
  int iVar1;
  u_int length_local;
  u_char *bp_local;
  netdissect_options *ndo_local;
  
  iVar1 = l_strnstart("MSG",4,(char *)bp,length);
  if (iVar1 == 0) {
    iVar1 = l_strnstart("RPY ",4,(char *)bp,length);
    if (iVar1 == 0) {
      iVar1 = l_strnstart("ERR ",4,(char *)bp,length);
      if (iVar1 == 0) {
        iVar1 = l_strnstart("ANS ",4,(char *)bp,length);
        if (iVar1 == 0) {
          iVar1 = l_strnstart("NUL ",4,(char *)bp,length);
          if (iVar1 == 0) {
            iVar1 = l_strnstart("SEQ ",4,(char *)bp,length);
            if (iVar1 == 0) {
              iVar1 = l_strnstart("END",4,(char *)bp,length);
              if (iVar1 == 0) {
                (*ndo->ndo_printf)(ndo," BEEP (payload or undecoded)");
              }
              else {
                (*ndo->ndo_printf)(ndo," BEEP END");
              }
            }
            else {
              (*ndo->ndo_printf)(ndo," BEEP SEQ");
            }
          }
          else {
            (*ndo->ndo_printf)(ndo," BEEP NUL");
          }
        }
        else {
          (*ndo->ndo_printf)(ndo," BEEP ANS");
        }
      }
      else {
        (*ndo->ndo_printf)(ndo," BEEP ERR");
      }
    }
    else {
      (*ndo->ndo_printf)(ndo," BEEP RPY");
    }
  }
  else {
    (*ndo->ndo_printf)(ndo," BEEP MSG");
  }
  return;
}