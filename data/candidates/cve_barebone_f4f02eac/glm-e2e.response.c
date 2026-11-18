define FLAG_NOT_AT_END       0x4

int match(Node *node, const char *sp, const char *end, int flags, MatchState *m) {
    uint16_t rune;
    MatchState m_local;

    while (1) {
        if (node->type > 0x10) {
            return 0;
        }

        switch (node->type) {
            case 0x0:
                return 1;

            case 0x1:
                node = node->left;
                break;

            case 0x2:
                memcpy(&m_local, m, 0xa8);
                if (match(node->left, sp, end, flags, &m_local)) {
                    memcpy(m, &m_local, 0xa8);
                    return 1;
                }
                node = node->right;
                break;

            case 0x3:
                if (!match(node->left, sp, end, flags, m)) {
                    return 0;
                }
                node = node->right;
                break;

            case 0x4:
                memcpy(&m_local, m, 0xa8);
                if (match(node->left, sp, end, flags, &m_local)) {
                    return 0;
                }
                node = node->right;
                break;

            case 0x5:
                sp += chartorune(&rune, sp);
                if (rune == 0) return 0;
                node += 1; // Equivalent to (Node*)((char*)node + 0x20)
                break;

            case 0x6:
                sp += chartorune(&rune, sp);
                if (rune == 0 || isnewline(rune)) return 0;
                node += 1;
                break;

            case 0x7:
                sp += chartorune(&rune, sp);
                if (rune == 0) return 0;
                if (flags & FLAG_CASE_INSENSITIVE) {
                    rune = canon(rune);
                }
                if (rune != node->rune) return 0;
                node += 1;
                break;

            case 0x8:
                sp += chartorune(&rune, sp);
                if (rune == 0) return 0;
                if (flags & FLAG_CASE_INSENSITIVE) {
                    if (!incclasscanon(node->cclass, canon(rune))) return 0;
                } else {
                    if (!incclass(node->cclass, rune)) return 0;
                }
                node += 1;
                break;

            case 0x9:
                sp += chartorune(&rune, sp);
                if (rune == 0) return 0;
                if (flags & FLAG_CASE_INSENSITIVE) {
                    if (incclasscanon(node->cclass, canon(rune))) return 0;
                } else {
                    if (incclass(node->cclass, rune)) return 0;
                }
                node += 1;
                break;

            case 0xA: {
                int len = (int)((uintptr_t)m->captures[node->group_id].end - (uintptr_t)m->captures[node->group_id].start);
                if (flags & FLAG_CASE_INSENSITIVE) {
                    if (strncmpcanon(sp, m->captures[node->group_id].start, len) != 0) return 0;
                } else {
                    if (strncmp(sp, m->captures[node->group_id].start, len) != 0) return 0;
                }
                if (len > 0) {
                    sp += len;
                }
                node += 1;
                break;
            }

            case 0xB:
                if (sp == end && !(flags & FLAG_NOT_AT_END)) {
                    node += 1;
                    break;
                }
                if (flags & FLAG_RIGHTMOST) {
                    if (sp > end && isnewline((signed char)sp[-1])) {
                        node += 1;
                        break;
                    }
                }
                return 0;

            case 0xC:
                if (*sp == '\0') {
                    node += 1;
                    break;
                }
                if (flags & FLAG_RIGHTMOST) {
                    if (isnewline((signed char)*sp)) {
                        node += 1;
                        break;
                    }
                }
                return 0;

            case 0xD: {
                int prev_is_word = 0;
                if (sp > end) {
                    prev_is_word = iswordchar((signed char)sp[-1]) != 0;
                }
                int curr_is_word = iswordchar((signed char)*sp);
                if ((prev_is_word ^ curr_is_word) == 0) return 0;
                node += 1;
                break;
            }

            case 0xE: {
                int prev_is_word = 0;
                if (sp > end) {
                    prev_is_word = iswordchar((signed char)sp[-1]) != 0;
                }
                int curr_is_word = iswordchar((signed char)*sp);
                if ((prev_is_word ^ curr_is_word) != 0) return 0;
                node += 1;
                break;
            }

            case 0xF:
                m->captures[node->group_id].start = sp;
                node += 1;
                break;

            case 0x10:
                m->captures[node->group_id].end = sp;
                node += 1;
                break;
        }
    }
}