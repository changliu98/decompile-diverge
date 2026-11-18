void handle_ppp(struct NetFrame *frame, int proto, const unsigned char *px,
                int length) {
  if ((proto & 0xff00) == 0x8100) {
    ppp_hdlc(frame, px - 1, length);
    return;
  }
  switch (proto) {
    case 0x0021:
    case 0x0821:
      ip_print(frame, px, length);
      break;
    case 0x0023:
      isoclns_print(frame, px, length, length);
      break;
    case 0x002b:
    case 0x082b:
      ipx_print(frame, px, length);
      break;
    case 0x0033:
    case 0x0833:
      ip6_print(frame, px, length);
      break;
    case 0x0060:
    case 0x0860:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0061:
      handle_mlppp(frame, px, length);
      break;
    case 0x0063:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0064:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0065:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0067:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0068:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0069:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x006a:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x006b:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x006d:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x006f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0070:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0071:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0072:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0073:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0074:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0075:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0076:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0077:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0078:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0079:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007a:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007b:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007c:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007d:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007e:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x007f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02001:
      mpls_print(frame, px, length);
      break;
    case 0x02003:
      mpls_print(frame, px, length);
      break;
    case 0x02057:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0205f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02101:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02103:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02157:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0215f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02201:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02203:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02257:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0225f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02301:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02303:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02357:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0235f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02401:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02403:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02457:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0245f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02501:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02503:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02557:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0255f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02601:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02603:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02657:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0265f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02701:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02703:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02757:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0275f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02801:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02803:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02857:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0285f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02901:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02903:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02957:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0295f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02a01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02a03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02a57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02a5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02b01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02b03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02b57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02b5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02c01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02c03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02c57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02c5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02d01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02d03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02d57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02d5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02e01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02e03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02e57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02e5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02f01:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02f03:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02f57:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x02f5f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03001:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03003:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03057:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0305f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03101:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03103:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03157:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0315f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03201:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03203:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03257:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0325f:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03301:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03303:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x03357:
      handle_ctrl_proto(frame, proto, px, length);
      break;
    case 0x0335f:
      handle_ctrl_proto
#endif