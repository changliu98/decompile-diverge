char *__cdecl cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
  size_t new_len;
  size_t old_len;
  char *copy;

  // 1. Validate object: must not be null, must be of type string (0x10), 
  //    and must not be marked as constant/immutable (0x100).
  if (!object || (object->type & 0x10) == 0 || (object->type & 0x100) != 0)
    return NULL;
    
  // 2. Ensure both the current and new strings are valid
  if (!object->valuestring || !valuestring)
    return NULL;

  new_len = strlen(valuestring);
  old_len = strlen(object->valuestring);

  // 3. If the new string is longer than the existing buffer, allocate new memory
  if (new_len > old_len)
  {
    copy = (char *)cJSON_strdup((const unsigned __int8 *)valuestring, &global_hooks);
    if (copy)
    {
      // Free the old string and assign the newly allocated one
      cJSON_free(object->valuestring);
      object->valuestring = copy;
      return copy;
    }
    else
    {
      return NULL;
    }
  }
  // 4. If the new string fits in the existing buffer, check for memory overlap
  else if (valuestring + new_len < object->valuestring || object->valuestring + old_len < valuestring)
  {
    // Safe to copy directly since the memory regions do not overlap
    strcpy(object->valuestring, valuestring);
    return object->valuestring;
  }
  else
  {
    // Overlapping memory regions, refuse to copy to prevent corruption
    return NULL;
  }
}