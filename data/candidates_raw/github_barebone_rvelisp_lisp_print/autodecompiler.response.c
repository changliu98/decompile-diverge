void print(double d) {
 int t = T(d);
 if (t == 32761)
  fprintf(out, "()");
 else if (t == 32762)
  fprintf(out, "<%s>", prim[ord(d)]);
 else if (t == 32763)
  fprintf(out, "%s", cell + ord(d));
 else if (t == 32764)
  fprintf(out, "\"%s\"", cell + ord(d));
 else if (t == 32766)
  printlist(d);
 else if (t == 32767)
  fprintf(out, "{%u}", ord(d));
 else if (t == 32768)
  fprintf(out, "[%u]", ord(d));
 else if (t == 65535)
  fprintf(out, "()");
 else
  fprintf(out, "%.17lg", d);
}