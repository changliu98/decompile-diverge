const char *__cdecl get_priority_string(int prio)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( prio )
  {
    case 128:
      v2 = "Unavailable";
      break;
    case 129:
      v2 = "Preferred";
      break;
    case 130:
      v2 = "Neutral";
      break;
    case 131:
      v2 = "Low";
      break;
    default:
      v2 = "Invalid";
      break;
  }
  return v2;
}