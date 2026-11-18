void bgp_capabilities_print(netdissect_options *ndo,u_char *opt,int caps_len)

{
  byte bVar1;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var2;
  uint16_t uVar3;
  uint v;
  uint len;
  uint32_t asnum;
  char *pcVar4;
  undefined *puVar5;
  char *pcVar6;
  char *pcVar7;
  int i;
  int cap_offset;
  int tcap_len;
  int cap_len;
  int cap_type;
  int caps_len_local;
  u_char *opt_local;
  netdissect_options *ndo_local;
  
  i = 0;
  while( true ) {
    if (caps_len <= i) {
      return;
    }
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < opt + i)) break;
    v = (uint)opt[i];
    len = (uint)opt[i + 1];
    p_Var2 = ndo->ndo_printf;
    pcVar4 = tok2str(bgp_capcode_values,"Unknown",v);
    (*p_Var2)(ndo,"\n\t      %s (%u), length: %u",pcVar4,(ulong)v,(ulong)len);
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -(long)(int)len) ||
       (ndo->ndo_snapend + -(long)(int)len < opt + (i + 2))) break;
    if (v == 1) {
      p_Var2 = ndo->ndo_printf;
      uVar3 = EXTRACT_16BITS(opt + (long)i + 2);
      pcVar4 = tok2str(af_values,"Unknown",(uint)uVar3);
      uVar3 = EXTRACT_16BITS(opt + (long)i + 2);
      pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + 5]);
      (*p_Var2)(ndo,"\n\t\tAFI %s (%u), SAFI %s (%u)",pcVar4,(ulong)uVar3,pcVar6,(ulong)opt[i + 5]);
    }
    else if (v != 2) {
      if (v == 0x40) {
        p_Var2 = ndo->ndo_printf;
        puVar5 = &DAT_001020bf;
        if ((opt[i + 2] & 0x80) != 0) {
          puVar5 = &DAT_001020bd;
        }
        uVar3 = EXTRACT_16BITS(opt + (long)i + 2);
        (*p_Var2)(ndo,"\n\t\tRestart Flags: [%s], Restart Time %us",puVar5,(ulong)(uVar3 & 0xfff));
        cap_offset = 4;
        for (tcap_len = len - 2; 3 < tcap_len; tcap_len = tcap_len + -4) {
          p_Var2 = ndo->ndo_printf;
          uVar3 = EXTRACT_16BITS(opt + (long)cap_offset + (long)i);
          pcVar4 = tok2str(af_values,"Unknown",(uint)uVar3);
          uVar3 = EXTRACT_16BITS(opt + (long)cap_offset + (long)i);
          pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + cap_offset + 2]);
          puVar5 = &DAT_00102107;
          if ((opt[i + cap_offset + 3] & 0x80) != 0) {
            puVar5 = &DAT_00102103;
          }
          (*p_Var2)(ndo,"\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",pcVar4,
                    (ulong)uVar3,pcVar6,(ulong)opt[i + cap_offset + 2],puVar5);
          cap_offset = cap_offset + 4;
        }
      }
      else if (v == 0x41) {
        if (len == 4) {
          p_Var2 = ndo->ndo_printf;
          asnum = EXTRACT_32BITS(opt + (long)i + 2);
          pcVar4 = as_printf(ndo,astostr,0x14,asnum);
          (*p_Var2)(ndo,"\n\t\t 4 Byte AS %s",pcVar4);
        }
      }
      else if (v == 0x45) {
        cap_offset = 2;
        tcap_len = len;
        if (len == 0) {
          (*ndo->ndo_printf)(ndo," (bogus)");
        }
        else {
          for (; 0 < tcap_len; tcap_len = tcap_len + -4) {
            if (tcap_len < 4) {
              (*ndo->ndo_printf)(ndo,"\n\t\t(invalid)");
              break;
            }
            p_Var2 = ndo->ndo_printf;
            uVar3 = EXTRACT_16BITS(opt + (long)cap_offset + (long)i);
            pcVar4 = tok2str(af_values,"Unknown",(uint)uVar3);
            uVar3 = EXTRACT_16BITS(opt + (long)cap_offset + (long)i);
            pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + cap_offset + 2]);
            bVar1 = opt[i + cap_offset + 2];
            pcVar7 = tok2str(bgp_add_path_recvsend,"Bogus (0x%02x)",(uint)opt[i + cap_offset + 3]);
            (*p_Var2)(ndo,"\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",pcVar4,(ulong)uVar3,
                      pcVar6,(ulong)bVar1,pcVar7);
            cap_offset = cap_offset + 4;
          }
        }
      }
      else if ((v != 0x80) &&
              ((*ndo->ndo_printf)(ndo,"\n\t\tno decoder for Capability %u",(ulong)v),
              ndo->ndo_vflag < 2)) {
        print_unknown_data(ndo,opt + (i + 2),"\n\t\t",len);
      }
    }
    if ((1 < ndo->ndo_vflag) && (len != 0)) {
      print_unknown_data(ndo,opt + (i + 2),"\n\t\t",len);
    }
    i = len + 2 + i;
  }
  (*ndo->ndo_printf)(ndo,"[|BGP]");
  return;
}