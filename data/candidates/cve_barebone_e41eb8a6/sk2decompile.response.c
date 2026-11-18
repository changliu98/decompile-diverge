int access_parse_oid(unsigned char *oid, unsigned int oid_len,
                     unsigned char **oid_name, unsigned int *oid_name_len,
                     unsigned char **oid_value, unsigned int *oid_value_len,
                     int *oid_type, int *oid_access) {
  int i, name_len, value_len;
  if (oid_len == 0 || oid == NULL) return 1;
  name_len = oid[0];
  value_len = oid[name_len + 1];
  if (oid_len != name_len + 2 + value_len + 2) return 1;
  if (oid_value == NULL || oid_name == NULL) return 1;
  *oid_name = malloc(name_len + 1);
  if (*oid_name == NULL) return 1;
  *oid_value = malloc(value_len + 1);
  if (*oid_value == NULL) {
    free(*oid_name);
    return 1;
  }
  *oid_value_len = value_len;
  *oid_name_len = name_len;
  for (i = 0; i < name_len; i++) {
    if (oid[i + 1] > 255) {
      free(*oid_name);
      free(*oid_value);
      return 1;
    }
    (*oid_name)[i] = oid[i + 1];
  }
  (*oid_name)[name_len] = 0;
  for (i = 0; i < value_len; i++) {
    if (oid[name_len + 2 + i] > 255) {
      free(*oid_name);
      free(*oid_value);
      return 1;
    }
    (*oid_value)[i] = oid[name_len + 2 + i];
  }
  (*oid_value)[value_len] = 0;
  *oid_type = oid[name_len + 2 + value_len + 1];
  *oid_access = oid[name_len + 2 + value_len + 2];
  return 0;
}