char *cJSON_SetValuestring(cJSON *object, const char *string) {
  char *newstring;
  unsigned int len, oldlen;
  if (!object || !(object->type & 16) || (object->type & 256)) return 0;
  if (!object->valuestring || !string) return 0;
  len = strlen(string);
  oldlen = strlen(object->valuestring);
  if (len <= oldlen) {
    if (string + len >= object->valuestring &&
        object->valuestring + oldlen >= string)
      return 0;
    strcpy(object->valuestring, string);
    return object->valuestring;
  }
  newstring = cJSON_strdup((const unsigned char *)string, &global_hooks);
  if (!newstring) return 0;
  if (object->valuestring) cJSON_free(object->valuestring);
  object->valuestring = newstring;
  return newstring;
}