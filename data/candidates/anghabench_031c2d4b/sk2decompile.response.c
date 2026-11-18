static bool tomoyo_invalid(const unsigned char c) {
  if (!c) return false;
  if (c <= 32) return true;
  if (c >= 127) return true;
  return false;
}