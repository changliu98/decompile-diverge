char base64_encode_value(char value_in) {
  const char* base64 =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  if (value_in >= 64) return '=';
  return base64[value_in];
}