static char *hcfs2string(u_int8_t hcfs) {
  char *s;
  switch (hcfs) {
    case HCFS_OPERATIONAL:
      s = "operational";
      break;
    case HCFS_SUSPEND:
      s = "suspend";
      break;
    case HCFS_RESUME:
      s = "resume";
      break;
    case HCFS_RESET:
      s = "reset";
      break;
    default:
      s = "?";
      break;
  }
  return s;
}