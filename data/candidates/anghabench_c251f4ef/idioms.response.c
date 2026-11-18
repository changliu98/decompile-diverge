char *hcfs2string(int state)
{
  char *name;
  switch (state) {
  case 0x80:
    name = "suspend";
    break;
  case 0x81:
    name = "resume";
    break;
  case 0x82:
    name = "reset";
    break;
  case 0x83:
    name = "operational";
    break;
  default:
    name = "?";
  }
  return name;
}