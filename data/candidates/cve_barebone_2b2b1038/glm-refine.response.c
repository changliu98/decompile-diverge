void __cdecl vqp_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{
  const u_char *tptr;
  int tlen;
  uint8_t nitems;
  uint32_t vqp_obj_type;
  uint16_t vqp_obj_len;
  const char *type_str, *err_str;
  uint32_t seq;

  // Check if the packet is truncated (less than 8 bytes available)
  if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || pptr > ndo->ndo_snapend - 8)
    goto trunc;

  if (*pptr != 1)
  {
    ndo->ndo_printf(ndo, "VQP version %u packet not supported", *pptr);
    return;
  }

  // VQPv1
  if (ndo->ndo_vflag < 1)
  {
    type_str = tok2str(&vqp_msg_type_values, "unknown (%u)", pptr[1]);
    err_str = tok2str(&vqp_error_code_values, "unknown (%u)", pptr[2]);
    ndo->ndo_printf(ndo, "VQPv%u %s Message, error-code %s (%u), length %u",
                    *pptr, type_str, err_str, pptr[2], len);
    return;
  }

  // Verbose output (ndo->ndo_vflag >= 1)
  nitems = pptr[3];
  type_str = tok2str(&vqp_msg_type_values, "unknown (%u)", pptr[1]);
  err_str = tok2str(&vqp_error_code_values, "unknown (%u)", pptr[2]);
  seq = EXTRACT_32BITS(pptr + 4);

  ndo->ndo_printf(ndo,
    "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items %u, length %u",
    *pptr, type_str, err_str, pptr[2], seq, nitems, len);

  tptr = pptr + 8;
  tlen = len - 8;

  while (nitems && tlen > 0)
  {
    vqp_obj_type = EXTRACT_32BITS(tptr);
    vqp_obj_len = EXTRACT_16BITS(tptr + 4);
    tptr += 6;
    tlen -= 6;

    type_str = tok2str(&vqp_obj_values, "Unknown", vqp_obj_type);
    ndo->ndo_printf(ndo, "\n\t  %s Object (0x%08x), length %u, value: ",
                    type_str, vqp_obj_type, vqp_obj_len);

    if (!vqp_obj_type || !vqp_obj_len)
      break;

    // Bounds check against snapend
    if (tptr > ndo->ndo_snapend - vqp_obj_len)
      goto trunc;

    switch (vqp_obj_type)
    {
      case 0xC01u:
        ndo->ndo_printf(ndo, "%s (0x%08x)", ipaddr_string(ndo, tptr), EXTRACT_32BITS(tptr));
        break;
      case 0xC02u:
      case 0xC03u:
      case 0xC04u:
      case 0xC05u:
        safeputs(ndo, tptr, vqp_obj_len);
        break;
      case 0xC06u:
      case 0xC08u:
        ndo->ndo_printf(ndo, "%s", etheraddr_string(ndo, tptr));
        break;
      default:
        if (ndo->ndo_vflag <= 1)
          print_unknown_data(ndo, tptr, "\n\t    ", vqp_obj_len);
        break;
    }

    tptr += vqp_obj_len;
    tlen -= vqp_obj_len;
    nitems--;
  }
  return;

trunc:
  ndo->ndo_printf(ndo, "\n\t[|VQP]");
}