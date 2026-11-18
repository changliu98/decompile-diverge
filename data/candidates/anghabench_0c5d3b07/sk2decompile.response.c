static const char *get_priority_string(u8 priority) {
  const char *str;
  switch (priority) {
    case PTP_PRIORITY_UNAVAILABLE:
      str = "Unavailable";
      break;
    case PTP_PRIORITY_PREFERRED:
      str = "Preferred";
      break;
    case PTP_PRIORITY_NEUTRAL:
      str = "Neutral";
      break;
    case PTP_PRIORITY_LOW:
      str = "Low";
      break;
    default:
      str = "Invalid";
      break;
  }
  return str;
}