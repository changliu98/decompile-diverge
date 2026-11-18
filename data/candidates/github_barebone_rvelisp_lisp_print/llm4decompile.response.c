void print(double x) {
  if (T(x)==32753) fprintf(out,"<%s>",prim[ord(x)].s);
  else if (T(x)==32754) fprintf(out,"%s",cell+ord(x));
  else if (T(x)==32755) fprintf(out,"\"%s\"",cell+ord(x));
  else if (T(x)==32756) printlist(x);
  else if (T(x)==32758) fprintf(out,"{%u}",ord(x));
  else if (T(x)==32759) fprintf(out,"[%u]",ord(x));
  else if (T(x)==65535) fprintf(out,"()");
  else fprintf(out,"%.17lg",x);
}