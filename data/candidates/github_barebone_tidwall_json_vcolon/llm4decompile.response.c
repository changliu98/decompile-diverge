int64_t vcolon(const uint8_t *json, int64_t len, int64_t i)
{
 if (i == len) return -(i + 1);
 if (json[i] == ':') return i + 1;
 while (json[i] == ' ' || json[i] == '\t' || json[i] == '\n' || json[i] == '\r') {
  if (++i >= len) return -(i + 1);
 }
 return json[i] == ':' ? i + 1 : -(i + 1);
}