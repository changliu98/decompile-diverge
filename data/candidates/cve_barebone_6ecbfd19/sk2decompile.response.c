guint ieee802_11_print(wireshark_dissector_info_t *pinfo, const guint8 *tvbuff,
                       guint length, guint offset, int is_wep, int hdr_len) {
  int curr_length;
  int hdr_length;
  int llc_length;
  int mesh_hdr_length;
  int llc_ret;
  guint8 subtype;
  mac_addr src_mac, dst_mac;
  curr_length = offset;
  if (length < hdr_len) {
    pinfo->fh_print(pinfo, "%s", "[|802.11]");
    return curr_length;
  }
  length -= hdr_len;
  if (curr_length > length) {
    hdr_len = curr_length - length;
    curr_length = length;
    pinfo->captured_length -= hdr_len;
  }
  if (curr_length < 2) {
    pinfo->fh_print(pinfo, "%s", "[|802.11]");
    return offset;
  }
  subtype = *(const guint8 *)(tvbuff);
  hdr_length = extract_header_length(pinfo, subtype);
  if (hdr_length == 0) return 0;
  if (is_wep) hdr_length = (hdr_length + 3) & ~3;
  if (pinfo->is_mesh && (((subtype) >> 2) & 0x03) == 2 &&
      (((subtype) >> 4) & 0x08)) {
    mesh_hdr_length = extract_mesh_header_length(tvbuff + hdr_length);
    hdr_length += mesh_hdr_length;
  } else
    mesh_hdr_length = 0;
  if (curr_length < hdr_length) {
    pinfo->fh_print(pinfo, "%s", "[|802.11]");
    return hdr_length;
  }
  if (pinfo->fh_info)
    ieee_802_11_hdr_print(pinfo, subtype, tvbuff, hdr_length, mesh_hdr_length);
  length -= hdr_length;
  curr_length -= hdr_length;
  tvbuff += hdr_length;
  src_mac.type = MAC_ADDR_UNDEF;
  dst_mac.type = MAC_ADDR_UNDEF;
  switch (((subtype) >> 2) & 0x03) {
    case 0:
      get_mgmt_src_dst_mac(tvbuff - hdr_length, &src_mac, &dst_mac);
      if (mgmt_body_print(pinfo, subtype, src_mac, tvbuff, length) == 0) {
        pinfo->fh_print(pinfo, "%s", "[|802.11]");
        return hdr_length;
      }
      break;
    case 1:
      if (ctrl_body_print(pinfo, subtype, tvbuff - hdr_length) == 0) {
        pinfo->fh_print(pinfo, "%s", "[|802.11]");
        return hdr_length;
      }
      break;
    case 2:
      if ((((subtype) >> 4) & 0x04)) return hdr_length;
      if (((subtype) & 0x4000)) {
        pinfo->fh_print(pinfo, "Data");
        if (wep_print(pinfo, tvbuff) == 0) {
          pinfo->fh_print(pinfo, "%s", "[|802.11]");
          return hdr_length;
        }
      } else {
        get_data_src_dst_mac(subtype, tvbuff - hdr_length, &src_mac, &dst_mac);
        llc_ret = llc_print(pinfo, tvbuff, length, curr_length, &src_mac,
                            &dst_mac);
        if (llc_ret < 0) {
          if (!pinfo->eo_encap) pinfo->fh_encap(pinfo, tvbuff, curr_length);
          llc_ret = -llc_ret;
        }
        hdr_length += llc_ret;
      }
      break;
  }
  return hdr_length;
}