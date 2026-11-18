void print(double x)
{
  switch (type(x)) {
  case 0x7ff0:
    print_int((int) x);
    break;
  case 0x7ff1:
    print_int((int) x);
    break;
  case 0x7ff2:
    print_int((int) x);
    break;
  case 0x7ff3:
    print_int((int) x);
    break;
  case 0x7ff4:
    print_int((int) x);
    break;
  case 0x7ff5:
    print_int((int) x);
    break;
  case 0x7ff6:
    print_int((int) x);
    break;
  case 0x7ff7:
    print_int((int) x);
    break;
  case 0x7ff8:
    print_int((int) x);
    break;
  case 0x7ff9:
    {
      char *s = (char *) x;
      int i = index(s);
      fprintf(out, "<%s>", prim[i]);
    }
    break;
  case 0x7ffa:
    {
      char *s = (char *) x;
      int i = index(s);
      fprintf(out, "%s", cell[i]);
    }
    break;
  case 0x7ffb:
    {
      char *s = (char *) x;
      int i = index(s);
      fprintf(out, "\"%s\"", cell[i]);
    }
    break;
  case 0x7ffc:
    print_int((int) x);
    break;
  case 0x7ffe:
    {
      int i = index((char *) x);
      fprintf(out, "{%u}", i);
    }
    break;
  case 0x7fff:
    {
      int i = index((char *) x);
      fprintf(out, "[%u]", i);
    }
    break;
  case 0xffff:
    fprintf(out, "()");
    break;
  default:
    fprintf(out, "%.17lg", x);
    break;
  }
}