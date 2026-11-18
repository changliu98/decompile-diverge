void __cdecl print(double x)
{
  uint32_t v1; // eax
  uint32_t v2; // eax
  uint32_t v3; // eax
  uint32_t v4; // eax
  uint32_t v5; // eax
  uint32_t v6; // eax
  FILE *v7; // [rsp+8h] [rbp-38h]
  FILE *v8; // [rsp+10h] [rbp-30h]
  FILE *v9; // [rsp+18h] [rbp-28h]
  FILE *v10; // [rsp+20h] [rbp-20h]
  FILE *stream; // [rsp+28h] [rbp-18h]

  v1 = T(x);
  switch ( v1 )
  {
    case 0x7FF9u:
      stream = out;
      v2 = ord(x);
      fprintf(stream, "<%s>", (&prim)[3 * v2]);
      break;
    case 0x7FFAu:
      v10 = out;
      v3 = ord(x);
      fprintf(v10, "%s", (const char *)cell + v3);
      break;
    case 0x7FFBu:
      v9 = out;
      v4 = ord(x);
      fprintf(v9, "\"%s\"", (const char *)cell + v4);
      break;
    case 0x7FFCu:
      printlist(x);
      break;
    case 0x7FFEu:
      v8 = out;
      v5 = ord(x);
      fprintf(v8, "{%u}", v5);
      break;
    case 0x7FFFu:
      v7 = out;
      v6 = ord(x);
      fprintf(v7, "[%u]", v6);
      break;
    case 0xFFFFu:
      fprintf(out, "()");
      break;
    default:
      fprintf(out, "%.17lg", x);
      break;
  }
}