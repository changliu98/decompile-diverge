define FLAG_NOTBOL 4

int __cdecl match(Reinst *pc, const char *sp, const char *bol, int flags, Resub *out)
{
    Rune c;
    int i;
    bool prev_word;
    Resub scratch;
    Reclass *cc;

    while (true)
    {
        switch (pc->opcode)
        {
            case OP_END:
                return 1;

            case OP_SPLIT:
                memcpy(&scratch, out, sizeof(scratch));
                if (!match(pc->x, sp, bol, flags, &scratch))
                {
                    pc = pc->y;
                    continue;
                }
                memcpy(out, &scratch, sizeof(Resub));
                return 1;

            case OP_JMP:
                pc = pc->x;
                continue;

            case OP_NEEDMATCH:
                if (!match(pc->x, sp, bol, flags, out))
                    return 0;
                pc = pc->y;
                continue;

            case OP_NEEDNOMATCH:
                memcpy(&scratch, out, sizeof(scratch));
                if (match(pc->x, sp, bol, flags, &scratch))
                    return 0;
                pc = pc->y;
                continue;

            case OP_ANY:
                sp += chartorune(&c, sp);
                if (!c)
                    return 0;
                pc++;
                continue;

            case OP_ANYNL:
                sp += chartorune(&c, sp);
                if (!c || isnewline(c))
                    return 0;
                pc++;
                continue;

            case OP_CHAR:
                sp += chartorune(&c, sp);
                if (!c)
                    return 0;
                if ((flags & FLAG_CASELESS) != 0)
                    c = canon(c);
                if (c != pc->c)
                    return 0;
                pc++;
                continue;

            case OP_CLASS:
                sp += chartorune(&c, sp);
                if (!c)
                    return 0;
                cc = pc->cc;
                if ((flags & FLAG_CASELESS) != 0) {
                    if (!incclasscanon(cc, canon(c)))
                        return 0;
                } else if (!incclass(cc, c)) {
                    return 0;
                }
                pc++;
                continue;

            case OP_NCLASS:
                sp += chartorune(&c, sp);
                if (!c)
                    return 0;
                cc = pc->cc;
                if ((flags & FLAG_CASELESS) != 0) {
                    if (incclasscanon(cc, canon(c)))
                        return 0;
                } else if (incclass(cc, c)) {
                    return 0;
                }
                pc++;
                continue;

            case OP_BACKREF:
                i = out->sub[pc->n].ep - out->sub[pc->n].sp;
                if ((flags & FLAG_CASELESS) != 0) {
                    if (strncmpcanon(sp, out->sub[pc->n].sp, i))
                        return 0;
                } else if (strncmp(sp, out->sub[pc->n].sp, i)) {
                    return 0;
                }
                if (i > 0)
                    sp += i;
                pc++;
                continue;

            case OP_BOL:
                if (sp != bol && ((flags & FLAG_MULTILINE) == 0 || sp <= bol || !isnewline(*(sp - 1))))
                    return 0;
                pc++;
                continue;

            case OP_EOL:
                if (*sp && ((flags & FLAG_MULTILINE) == 0 || !isnewline(*sp)))
                    return 0;
                pc++;
                continue;

            case OP_WB:
                prev_word = (sp > bol) && (iswordchar(*(sp - 1)) != 0);
                if (prev_word == (iswordchar(*sp) != 0))
                    return 0;
                pc++;
                continue;

            case OP_NWB:
                prev_word = (sp > bol) && (iswordchar(*(sp - 1)) != 0);
                if (prev_word != (iswordchar(*sp) != 0))
                    return 0;
                pc++;
                continue;

            case OP_SAVE:
                out->sub[pc->n].sp = sp;
                pc++;
                continue;

            case OP_RESTORE:
                out->sub[pc->n].ep = sp;
                pc++;
                continue;

            default:
                return 0;
        }
    }
}