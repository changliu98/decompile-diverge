void ubik_print(netdissect_options *ndo, const unsigned char *p) {
  int op;
  op = EXTRACT_32BITS(p + 7);
  ndo->ndo_efunc(ndo, " ubik call %s", tok2str(ubik_op_values, "op#%d", op));
  p += 8;
  switch (op) {
    case 10000: {
      int syncsite;
      time_t votestart;
      char votestart_str[256];
      struct tm *tm;
      syncsite = EXTRACT_32BITS(p);
      p += 4;
      ndo->ndo_efunc(ndo, " syncsite %s", syncsite ? "yes" : "no");
      ndo->ndo_efunc(ndo, " votestart");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      votestart = EXTRACT_32BITS(p);
      p += 4;
      tm = localtime(&votestart);
      strftime(votestart_str, sizeof(votestart_str), "%Y/%m/%d %H:%M:%S", tm);
      ndo->ndo_efunc(ndo, " %s", votestart_str);
      ndo->ndo_efunc(ndo, " dbversion");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
    }
    case 10003:
      ndo->ndo_efunc(ndo, " site");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %lu", (unsigned long)EXTRACT_32BITS(p));
      p += 4;
      break;
    case 20000:
    case 20001:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
    case 20002:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " file");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " pos");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " length");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " type %d", EXTRACT_32BITS(p));
      p += 4;
      break;
    case 20003:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " file");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " pos");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      break;
    case 20005:
      ndo->ndo_efunc(ndo, " file");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      break;
    case 20006:
      ndo->ndo_efunc(ndo, " file");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " length");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " dbversion");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
    case 20007:
    case 20008:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
    case 20009:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " file");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      ndo->ndo_efunc(ndo, " length");
      if (p > ndo->ndo_snapend - 4) goto trunc;
      ndo->ndo_efunc(ndo, " %d", EXTRACT_32BITS(p));
      p += 4;
      break;
    case 20010:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
    case 20012:
      ndo->ndo_efunc(ndo, " tid");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " oldversion");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      ndo->ndo_efunc(ndo, " newversion");
      if (p > ndo->ndo_snapend - 8) goto trunc;
      ndo->ndo_efunc(ndo, " %d.%d", EXTRACT_32BITS(p), EXTRACT_32BITS(p + 4));
      p += 8;
      break;
  }
  return;
trunc:
  ndo->ndo_efunc(ndo, " [|ubik]");
}