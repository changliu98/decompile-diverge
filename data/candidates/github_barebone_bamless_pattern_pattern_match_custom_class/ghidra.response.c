_Bool pattern_match_custom_class(char c,char *pattern_ptr,char *class_end)

{
  _Bool _Var1;
  char *pcVar2;
  char *pcVar3;
  _Bool ret;
  char *class_end_local;
  char *pattern_ptr_local;
  char c_local;
  
  pattern_ptr_local = pattern_ptr;
  if (pattern_ptr[1] == '^') {
    pattern_ptr_local = pattern_ptr + 1;
  }
  ret = pattern_ptr[1] != '^';
  do {
    while( true ) {
      while( true ) {
        pcVar2 = pattern_ptr_local + 1;
        if (class_end <= pcVar2) {
          return !ret;
        }
        if (*pcVar2 != '%') break;
        pattern_ptr_local = pattern_ptr_local + 2;
        _Var1 = pattern_match_class(c,*pattern_ptr_local);
        if (_Var1) {
          return ret;
        }
      }
      if ((pattern_ptr_local[2] == '-') && (pattern_ptr_local + 3 < class_end)) break;
      pattern_ptr_local = pcVar2;
      if (*pcVar2 == c) {
        return ret;
      }
    }
    pcVar3 = pattern_ptr_local + 3;
    pcVar2 = pattern_ptr_local + 1;
    pattern_ptr_local = pcVar3;
  } while ((c < *pcVar2) || (*pcVar3 < c));
  return ret;
}