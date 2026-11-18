




















int ISORegexp__get_cclass(char *pattern, int ppos, int *len, int *from, int *to, int *reverse) {
 if (pattern[ppos] == '^') { ppos++; *reverse = 1; } else { *reverse = 0; }
 switch (pattern[ppos]) {
  case '%':
   ppos++;
   *len = 2;
   switch (pattern[ppos]) {
    case 'd': return 2;
    case 'c': return 1;
    case 'C': return 4;
    case 'i': return 5;
    case 'p': return 6;
    case 'P': return 7;
    case 't': return 9;
   }
   *from = ppos; *to = ppos; return 8;
  case '[':
   *from = ppos+2;
   while ((pattern[ppos]) && (pattern[ppos] != ']')) ppos++;
   *to = ppos - 1; *len = ppos - *from + 1;
   return 8;
  case ' ':
   *len = 1; return 3;
 }
 *len = 1; *from = ppos; *to = ppos; return 8;
}
