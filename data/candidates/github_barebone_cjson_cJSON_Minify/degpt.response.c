void cJSON_Minify(char *json)

{
  int iVar1;
  char *into;
  char *json_local;
  
  into = json;
  json_local = json;
  if (json != (char *)0x0) {
    while (*json_local != '\0') {
      iVar1 = (int)*json_local;
      if (((iVar1 - 9U < 2) || (iVar1 == 0xd)) || (iVar1 == 0x20)) {
        json_local = json_local + 1;
      }
      else if (iVar1 == 0x22) {
        minify_string(&json_local,&into);
      }
      else if (iVar1 == 0x2f) {
        if (json_local[1] == '/') {
          skip_oneline_comment(&json_local);
        }
        else if (json_local[1] == '*') {
          skip_multiline_comment(&json_local);
        }
        else {
          json_local = json_local + 1;
        }
      }
      else {
        *into = *json_local;
        json_local = json_local + 1;
        into = into + 1;
      }
    }
    *into = '\0';
  }
  return;
}