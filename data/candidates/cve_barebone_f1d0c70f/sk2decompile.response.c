void ip_optprint(struct NetFrame *frame, const unsigned char *cp,
                 unsigned length) {
  const char *comma = "";
  unsigned opt, optlen;
  while (length) {
    frame->printer(frame, "%s", comma);
    comma = ",";
    if (cp > frame->payload_end - 1 || cp > frame->payload_end - 1) goto trunc;
    opt = *cp++;
    frame->printer(frame, "%s", tok2str(ip_opt_values, "unknown %u", opt));
    if (opt == 0 || opt == 1)
      optlen = 1;
    else {
      if (cp > frame->payload_end - 1 || cp > frame->payload_end - 1) goto trunc;
      optlen = *cp++;
    }
    if (optlen < 2) {
      frame->printer(frame, " [bad length %u]", optlen);
      return;
    }
    if (cp + optlen > frame->payload_end ||
        cp > frame->payload_end - optlen)
      goto trunc;
    switch (opt) {
      case 0:
        return;
      case 1:
        break;
      case 68:
        ip_printts(frame, cp, optlen);
        break;
      case 7:
      case 131:
      case 137:
        ip_printroute(frame, cp, optlen);
        break;
      case 130:
        break;
      case 148:
        if (optlen < 4) {
          frame->printer(frame, " [bad length %u]", optlen);
          break;
        }
        if (cp + 2 > frame->payload_end || cp + 2 > frame->payload_end)
          goto trunc;
        if ((((cp[1] << 8) | cp[2]) & 0xffff) != 0)
          frame->printer(frame, " value %u",
                         (((cp[1] << 8) | cp[2]) & 0xffff));
        break;
    }
    cp += optlen;
    length -= optlen;
  }
  return;
trunc:
  frame->printer(frame, "%s", "[|ip]");
}