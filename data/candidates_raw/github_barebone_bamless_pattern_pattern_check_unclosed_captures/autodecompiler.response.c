static void pattern_check_captures(struct pcre2_pattern *pattern) {
 int capture_count = 1;
 while (1) {
  if (capture_count >= pattern->num_captures) break;
  if (pattern->capture[capture_count].end_offset != ((PCRE2_SIZE)(-1))) continue;

  int captures = 0;
  char *c = pattern->pattern;
  while (1) {
   if (c >= pattern->pattern + strlen(pattern->pattern)) {
    pattern_set_error(pattern, 3, c - pattern->pattern);
    return;
   }
   switch (*c) {
    case '%':
     c += 2;
     continue;
    case '(':
     captures++;
     if (captures == capture_count) {
      pattern_set_error(pattern, 3, c - pattern->pattern);
      return;
     }
     continue;
    default:
     c++;
     continue;
   }
  }
  capture_count++;
 }
}