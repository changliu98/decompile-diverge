BINN_PRIVATE BOOL is_bool_str(char *str, BOOL *pbool) {
  int64  vint;
  double vdouble;

  if (str == NULL || pbool == NULL) return FALSE;

  if (stricmp(str, "true") == 0) goto loc_true;
  if (stricmp(str, "yes") == 0) goto loc_true;
  if (stricmp(str, "on") == 0) goto loc_true;
  //if (stricmp(str, "1") == 0) goto loc_true;

  if (stricmp(str, "false") == 0) goto loc_false;
  if (stricmp(str, "no") == 0) goto loc_false;
  if (stricmp(str, "off") == 0) goto loc_false;
  //if (stricmp(str, "0") == 0) goto loc_false;

  if (is_integer(str)) {
    vint = atoi64(str);
    *pbool = (vint != 0) ? TRUE : FALSE;
    return TRUE;
  } else if (is_float(str)) {
    vdouble = atof(str);
    *pbool = (vdouble != 0) ? TRUE : FALSE;
    return TRUE;
  }

  return FALSE;

loc_true:
  *pbool = TRUE;
  return TRUE;

loc_false:
  *pbool = FALSE;
  return TRUE;

}