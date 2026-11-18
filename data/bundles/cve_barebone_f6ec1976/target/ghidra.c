void bgp_capabilities_print(netdissect_options *ndo,u_char *opt,int caps_len)

{
  u_char uVar1;
  u_char uVar2;
  byte bVar3;
  _func_int_netdissect_options_ptr_char_ptr_varargs *p_Var4;
  uint v;
  uint len;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined *puVar8;
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
    p_Var4 = ndo->ndo_printf;
    pcVar5 = tok2str(bgp_capcode_values,"Unknown",v);
    (*p_Var4)(ndo,"\n\t      %s (%u), length: %u",pcVar5,(ulong)v,(ulong)len);
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -(long)(int)len) ||
       (ndo->ndo_snapend + -(long)(int)len < opt + (i + 2))) break;
    if (v == 1) {
      p_Var4 = ndo->ndo_printf;
      pcVar5 = tok2str(af_values,"Unknown",(uint)CONCAT11(opt[(long)i + 2],opt[(long)i + 3]));
      uVar1 = opt[(long)i + 2];
      uVar2 = opt[(long)i + 3];
      pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + 5]);
      (*p_Var4)(ndo,"\n\t\tAFI %s (%u), SAFI %s (%u)",pcVar5,(ulong)CONCAT11(uVar1,uVar2),pcVar6,
                (ulong)opt[i + 5]);
    }
    else if (v != 2) {
      if (v == 0x40) {
        if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) ||
           (ndo->ndo_snapend + -2 < opt + (long)i + 2)) break;
        puVar8 = &DAT_00102091;
        if ((opt[i + 2] & 0x80) != 0) {
          puVar8 = &DAT_0010208f;
        }
        (*ndo->ndo_printf)(ndo,"\n\t\tRestart Flags: [%s], Restart Time %us",puVar8,
                           (ulong)(CONCAT11(opt[(long)i + 2],opt[(long)i + 3]) & 0xfff));
        cap_offset = 4;
        for (tcap_len = len - 2; 3 < tcap_len; tcap_len = tcap_len + -4) {
          p_Var4 = ndo->ndo_printf;
          pcVar5 = tok2str(af_values,"Unknown",
                           (uint)CONCAT11(opt[(long)cap_offset + (long)i],
                                          opt[(long)cap_offset + (long)i + 1]));
          uVar1 = opt[(long)cap_offset + (long)i];
          uVar2 = opt[(long)cap_offset + (long)i + 1];
          pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + cap_offset + 2]);
          puVar8 = &DAT_001020d9;
          if ((opt[i + cap_offset + 3] & 0x80) != 0) {
            puVar8 = &DAT_001020d5;
          }
          (*p_Var4)(ndo,"\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding state preserved: %s",pcVar5,
                    (ulong)CONCAT11(uVar1,uVar2),pcVar6,(ulong)opt[i + cap_offset + 2],puVar8);
          cap_offset = cap_offset + 4;
        }
      }
      else if (v == 0x41) {
        if (len == 4) {
          p_Var4 = ndo->ndo_printf;
          pcVar5 = as_printf(ndo,astostr,0x14,
                             (uint)opt[(long)i + 2] << 0x18 | (uint)opt[(long)i + 3] << 0x10 |
                             (uint)opt[(long)i + 4] << 8 | (uint)opt[(long)i + 5]);
          (*p_Var4)(ndo,"\n\t\t 4 Byte AS %s",pcVar5);
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
            p_Var4 = ndo->ndo_printf;
            pcVar5 = tok2str(af_values,"Unknown",
                             (uint)CONCAT11(opt[(long)cap_offset + (long)i],
                                            opt[(long)cap_offset + (long)i + 1]));
            uVar1 = opt[(long)cap_offset + (long)i];
            uVar2 = opt[(long)cap_offset + (long)i + 1];
            pcVar6 = tok2str(bgp_safi_values,"Unknown",(uint)opt[i + cap_offset + 2]);
            bVar3 = opt[i + cap_offset + 2];
            pcVar7 = tok2str(bgp_add_path_recvsend,"Bogus (0x%02x)",(uint)opt[i + cap_offset + 3]);
            (*p_Var4)(ndo,"\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",pcVar5,
                      (ulong)CONCAT11(uVar1,uVar2),pcVar6,(ulong)bVar3,pcVar7);
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