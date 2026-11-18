void print(L x) {
  switch (T(x)) {
    case NIL:  fprintf(out, "()");                   break;
    case PRIM: fprintf(out, "<%s>", prim[ord(x)].s); break;
    case ATOM: fprintf(out, "%s", A+ord(x));         break;
    case STRG: fprintf(out, "\"%s\"", A+ord(x));     break;
    case CONS: printlist(x);                         break;
    case CLOS: fprintf(out, "{%u}", ord(x));         break;
    case MACR: fprintf(out, "[%u]", ord(x));         break;
    default:   fprintf(out, FLOAT, x);               break;
  }
}