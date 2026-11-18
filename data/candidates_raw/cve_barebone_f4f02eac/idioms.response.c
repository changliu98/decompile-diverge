int regexec(struct Reinst *re, char *sp, char *bol, int flags, struct Resub *out)
{
  struct Resub scratch;
  struct Reinst *r = re;
  char c;
  while (1) {
    switch (r->opcode) {
    case RE_OP_END:
      return 1;
    case RE_OP_FORK:
      r = r->x;
      break;
    case RE_OP_OR:
      reinit(&scratch, out, sizeof(scratch));
      if (regexec(r->x, sp, bol, flags, &scratch)) {
        reinit(out, &scratch, sizeof(scratch));
        return 1;
      }
      r = r->y;
      break;
    case RE_OP_AND:
      if (!regexec(r->x, sp, bol, flags, out))
        return 0;
      r = r->y;
      break;
    case RE_OP_NOT:
      reinit(&scratch, out, sizeof(scratch));
      if (regexec(r->x, sp, bol, flags, &scratch))
        return 0;
      r = r->y;
      break;
    case RE_OP_ANY:
      sp += getrune(&c);
      if (c == 0)
        return 0;
      r++;
      break;
    case RE_OP_ANYNOBR:
      sp += getrune(&c);
      if (c == 0)
        return 0;
      if (isbreak(c))
        return 0;
      r++;
      break;
    case RE_OP_CHAR:
      sp += getrune(&c);
      if (c == 0)
        return 0;
      if (flags & 1)
        c = tolower(c);
      if (c != r->c)
        return 0;
      r++;
      break;
    case RE_OP_IN:
      sp += getrune(&c);
      if (c == 0)
        return 0;
      if (flags & 1) {
        struct Reclass *cc = r->cc;
        if (!inreclass(cc, tolower(c)))
          return 0;
      } else {
        if (!inreclass(r->cc, c))
          return 0;
      }
      r++;
      break;
    case RE_OP_NOTIN:
      sp += getrune(&c);
      if (c == 0)
        return 0;
      if (flags & 1) {
        struct Reclass *cc = r->cc;
        if (inreclass(cc, tolower(c)))
          return 0;
      } else {
        if (inreclass(r->cc, c))
          return 0;
      }
      r++;
      break;
    case RE_OP_SUB:
      {
        int len = out->sub[r->n].ep - out->sub[r->n].sp;
        if (flags & 1) {
          if (strnequ(sp, out->sub[r->n].sp, len))
            return 0;
        } else {
          if (strneq(sp, out->sub[r->n].sp, len))
            return 0;
        }
        if (len > 0)
          sp += len;
      }
      r++;
      break;
    case RE_OP_WORDSTART:
      if (sp == bol && !(flags & 4))
        r++;
      else if (flags & 2 && sp > bol && isbreak(*sp))
        r++;
      else
        return 0;
      break;
    case RE_OP_WORDEND:
      if (*sp == 0 && !(flags & 4))
        r++;
      else if (flags & 2 && *sp > 0 && !isbreak(*sp))
        r++;
      else
        return 0;
      break;
    case RE_OP_WORDBOUND:
      {
        int i;
        i = 0;
        if (sp > bol)
          i = isword(*sp - 1);
        i ^= isword(*sp);
        if (i == 0)
          return 0;
      }
      r++;
      break;
    case RE_OP_NOWORDBOUND:
      {
        int i;
        i = 0;
        if (sp > bol)
          i = isword(*sp - 1);
        i ^= isword(*sp);
        if (i != 0)
          return 0;
      }
      r++;
      break;
    case RE_OP_STAR:
      out->sub[r->n].sp = sp;
      r++;
      break;
    case RE_OP_PLUS:
      out->sub[r->n].ep = sp;
      r++;
      break;
    default:
      return 0;
    }
  }
}