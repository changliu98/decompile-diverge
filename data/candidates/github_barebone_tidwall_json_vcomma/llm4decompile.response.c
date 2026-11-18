int64_t vcomma(const uint8_t *json, int64_t len, int64_t i, uint8_t end) {
  if (i == len) return -(i + 1);
  if (json[i] == ',') return i;
  do {
    if (json[i] == '\n' || json[i] == '\r' || json[i] == ' ') continue;
    if (json[i] == ',') return i;
    if (json[i] == end) return i;
    return -(i + 1);
  } while (++i < len);
  return -(i + 1);
}