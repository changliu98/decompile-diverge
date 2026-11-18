char *__cdecl hcfs2string(int state)
{
  char *v2; // [rsp+10h] [rbp-8h]

  switch ( state )
  {
    case 128:
      v2 = "suspend";
      break;
    case 129:
      v2 = "resume";
      break;
    case 130:
      v2 = "reset";
      break;
    case 131:
      v2 = "operational";
      break;
    default:
      v2 = "?";
      break;
  }
  return v2;
}