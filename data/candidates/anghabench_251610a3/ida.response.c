const char *__cdecl get_level_str(int level)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( level )
  {
    case 128:
      v2 = "warning";
      break;
    case 129:
      v2 = "verbose";
      break;
    case 130:
      v2 = "quiet";
      break;
    case 131:
      v2 = "panic";
      break;
    case 132:
      v2 = "info";
      break;
    case 133:
      v2 = "fatal";
      break;
    case 134:
      v2 = "error";
      break;
    case 135:
      v2 = "debug";
      break;
    default:
      v2 = "";
      break;
  }
  return v2;
}