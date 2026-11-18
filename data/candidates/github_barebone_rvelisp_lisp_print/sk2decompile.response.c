void print(double x) {
  switch (T(x)) {
    case 0xff:
      fprintf(stderr, "()");
      break;
    case 0x7fff:
      fprintf(stderr, "%.17lg", x);
      break;
    case 0x7fff - 1:
      fprintf(stderr, "{%u}", ord(x));
      break;
    case 0x7fff - 2:
      fprintf(stderr, "[%u]", ord(x));
      break;
    case 0x7fff - 3:
      fprintf(stderr, "<%s>", symtab[ord(x)].name);
      break;
    case 0x7fff - 4:
      fprintf(stderr, "%s", stringtab + ord(x));
      break;
    case 0x7fff - 5:
      fprintf(stderr, "\"%s\"", stringtab + ord(x));
      break;
    case 0x7fff - 6:
      printlist(x);
      break;
  }
}