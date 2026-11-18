static int match(Node *np, const char *s, const char *send, int flags,
                 MatchState *ms) {
  MatchState m2;
  Rune c;
  int i;
  for (;;) {
    switch (np->op) {
      case 0:
        return 1;
      case 1:
        np = np->x;
        continue;
      case 2:
        memcpy(&m2, ms, sizeof(m2));
        if (match(np->x, s, send, flags, &m2)) {
          memcpy(ms, &m2, sizeof(m2));
          return 1;
        }
        np = np->y;
        continue;
      case 3:
        if (match(np->x, s, send, flags, ms)) {
          np = np->y;
          continue;
        }
        return 0;
      case 4:
        memcpy(&m2, ms, sizeof(m2));
        if (match(np->x, s, send, flags, &m2)) return 0;
        np = np->y;
        continue;
      case 5:
        s += chartorune(&c, s);
        if (c == 0) return 0;
        np++;
        continue;
      case 6:
        s += chartorune(&c, s);
        if (c == 0) return 0;
        if (isnewline(c)) return 0;
        np++;
        continue;
      case 7:
        s += chartorune(&c, s);
        if (c == 0) return 0;
        if (flags & 1) c = canon(c);
        if (c != np->c) return 0;
        np++;
        continue;
      case 8:
        s += chartorune(&c, s);
        if (c == 0) return 0;
        if (flags & 1) {
          if (incclasscanon(np->cc, canon(c)) == 0) return 0;
        } else {
          if (incclass(np->cc, c) == 0) return 0;
        }
        np++;
        continue;
      case 9:
        s += chartorune(&c, s);
        if (c == 0) return 0;
        if (flags & 1) {
          if (incclasscanon(np->cc, canon(c)) != 0) return 0;
        } else {
          if (incclass(np->cc, c) != 0) return 0;
        }
        np++;
        continue;
      case 10:
        i = ms->level[np->nesting].rend - ms->level[np->nesting].rstart;
        if (flags & 1) {
          if (strncmpcanon(s, ms->level[np->nesting].rstart, i) != 0) return 0;
        } else {
          if (strncmp(s, ms->level[np->nesting].rstart, i) != 0) return 0;
        }
        if (i > 0) s += i;
        np++;
        continue;
      case 11:
        if (s == send && !(flags & 4)) {
          np++;
          continue;
        }
        if ((flags & 2) && s > send && isnewline(s[-1])) {
          np++;
          continue;
        }
        return 0;
      case 12:
        if (*s == 0) {
          np++;
          continue;
        }
        if ((flags & 2) && isnewline(*s)) {
          np++;
          continue;
        }
        return 0;
      case 13:
        i = (s > send && iswordchar(s[-1]));
        i ^= iswordchar(*s);
        if (i == 0) return 0;
        np++;
        continue;
      case 14:
        i = (s > send && iswordchar(s[-1]));
        i ^= iswordchar(*s);
        if (i != 0) return 0;
        np++;
        continue;
      case 15:
        ms->level[np->nesting].rstart = s;
        np++;
        continue;
      case 16:
        ms->level[np->nesting].rend = s;
        np++;
        continue;
    }
    return 0;
  }
}