u_int ieee802_11_print(netdissect_options *ndo,u_char *p,u_int length,u_int orig_caplen,int pad,
                      u_int fcslen)

{
  ushort fc_00;
  ushort uVar1;
  uint uVar2;
  int iVar3;
  u_char *p_00;
  int llc_hdrlen;
  lladdr_info dst;
  lladdr_info src;
  u_int meshdrlen;
  u_int hdrlen;
  u_int caplen;
  uint16_t fc;
  u_int fcslen_local;
  int pad_local;
  u_int orig_caplen_local;
  u_int length_local;
  u_char *p_local;
  netdissect_options *ndo_local;
  u_int local_c;
  
  local_c = orig_caplen;
  if (length < fcslen) {
    (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
  }
  else {
    uVar2 = length - fcslen;
    caplen = orig_caplen;
    if (uVar2 < orig_caplen) {
      caplen = orig_caplen - (orig_caplen - uVar2);
      ndo->ndo_snapend = ndo->ndo_snapend + -(ulong)(orig_caplen - uVar2);
    }
    if (caplen < 2) {
      (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
    }
    else {
      fc_00 = *(ushort *)p;
      hdrlen = extract_header_length(ndo,fc_00);
      if (hdrlen == 0) {
        local_c = 0;
      }
      else {
        if (pad != 0) {
          hdrlen = hdrlen + 3 & 0xfffffffc;
        }
        if (((ndo->ndo_Hflag == 0) || (((int)(uint)fc_00 >> 2 & 3U) != 2)) ||
           (((int)(uint)fc_00 >> 4 & 8U) == 0)) {
          meshdrlen = 0;
        }
        else {
          meshdrlen = extract_mesh_header_length(p + hdrlen);
          hdrlen = meshdrlen + hdrlen;
        }
        if (caplen < hdrlen) {
          (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
          local_c = hdrlen;
        }
        else {
          if (ndo->ndo_eflag != 0) {
            ieee_802_11_hdr_print(ndo,fc_00,p,hdrlen,meshdrlen);
          }
          p_00 = p + hdrlen;
          src.addr_string = etheraddr_string;
          dst.addr_string = etheraddr_string;
          uVar1 = fc_00 >> 2 & 3;
          if ((fc_00 >> 2 & 3) == 0) {
            get_mgmt_src_dst_mac(p_00 + -(ulong)hdrlen,&src.addr,&dst.addr);
            iVar3 = mgmt_body_print(ndo,fc_00,src.addr,p_00,uVar2 - hdrlen);
            if (iVar3 == 0) {
              (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
              return hdrlen;
            }
          }
          else if (uVar1 == 1) {
            iVar3 = ctrl_body_print(ndo,fc_00,p_00 + -(ulong)hdrlen);
            if (iVar3 == 0) {
              (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
              return hdrlen;
            }
          }
          else if (uVar1 == 2) {
            if (((int)(uint)fc_00 >> 4 & 4U) != 0) {
              return hdrlen;
            }
            if ((fc_00 & 0x4000) == 0) {
              get_data_src_dst_mac(fc_00,p_00 + -(ulong)hdrlen,&src.addr,&dst.addr);
              llc_hdrlen = llc_print(ndo,p_00,uVar2 - hdrlen,caplen - hdrlen,&src,&dst);
              if (llc_hdrlen < 0) {
                if (ndo->ndo_suppress_default_print == 0) {
                  (*ndo->ndo_default_print)(ndo,p_00,caplen - hdrlen);
                }
                llc_hdrlen = -llc_hdrlen;
              }
              hdrlen = llc_hdrlen + hdrlen;
            }
            else {
              (*ndo->ndo_printf)(ndo,"Data");
              iVar3 = wep_print(ndo,p_00);
              if (iVar3 == 0) {
                (*ndo->ndo_printf)(ndo,"%s","[|802.11]");
                return hdrlen;
              }
            }
          }
          local_c = hdrlen;
        }
      }
    }
  }
  return local_c;
}