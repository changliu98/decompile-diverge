define FLAGS_HAS_CORE_NOTE    0x800

int do_core_note(void *fp, unsigned char *nbuf, int type, int swap, uint32_t namesz, uint32_t descsz, size_t off, size_t size, int is_32bit, uint32_t *flags) {
    int os_style = -1;
    int ret = 0;

    // Determine OS style based on name
    if (namesz == 4 && strncmp((const char *)(nbuf + off), "Core", 4) == 0) {
        os_style = 0;
    } else if (namesz == 5 && strcmp((const char *)(nbuf + off), "Core") == 0) {
        os_style = 0;
    } else if (namesz == 8 && strcmp((const char *)(nbuf + off), "FreeBSD") == 0) {
        os_style = 1;
    } else if (namesz >= 11 && strncmp((const char *)(nbuf + off), "Linux/CORE", 11) == 0) {
        os_style = 2;
    }

    if (os_style != -1 && !(*flags & FLAGS_OS_STYLE_PRINTED)) {
        if (file_printf(fp, ", OS: %s", os_style_names[os_style]) == -1) {
            return 1;
        }
        *flags |= FLAGS_OS_STYLE_PRINTED;
        *flags |= os_style;
    }

    if (os_style == 2) {
        if (type == 1) { // NT_PRSTATUS
            unsigned char buf[0xa0];
            char printable_buf[0x200];
            char *printable_str;
            uint32_t sig, code, cursig, pid, ppid, pgrp, sid;

            memset(buf, 0, sizeof(buf));
            memcpy(buf, nbuf + off + 0x18, descsz);

            printable_str = file_printable(printable_buf, sizeof(printable_buf), (const char *)(buf + 0x7c));
            sig = getu32(swap, *(uint32_t *)(buf + 0x50));
            code = getu32(swap, *(uint32_t *)(buf + 0x54));
            cursig = getu32(swap, *(uint32_t *)(buf + 0x60));
            pid = getu32(swap, *(uint32_t *)(buf + 0x8c));
            ppid = getu32(swap, *(uint32_t *)(buf + 0x90));
            pgrp = getu32(swap, *(uint32_t *)(buf + 0xb4));
            sid = getu32(swap, *(uint32_t *)(buf + 0xb8));

            if (file_printf(fp, " %s: signal=%u, code=%u, cursig=%u, pid=%u, ppid=%u, pgrp=%u, sid=%u",
                            printable_str, sig, code, cursig, pid, ppid, pgrp, sid) == -1) {
                return 1;
            }
            *flags |= FLAGS_CORE_DUMP_INFO;
            return 1;
        } else if (type == 3 && (*flags & FLAGS_HAS_CORE_NOTE)) { // NT_PRPSINFO
            size_t i, j;
            size_t *offsets;

            for (i = 0; i < 5; i++) {
                size_t offset, limit;
                const char *base;

                offsets = is_32bit ? prpsoffsets32 : prpsoffsets64;
                offset = off + offsets[i];
                limit = off + descsz;
                base = (const char *)(nbuf + offset);

                for (j = 0; j < 16; j++) {
                    if (offset + j >= size || offset + j >= limit) {
                        break;
                    }
                    if (base[j] == '\0') {
                        if (j != 0) break;
                        else goto next_i;
                    }
                    if (isprint((unsigned char)base[j]) && strchr(" \t\n\r", base[j]) == NULL) {
                        break;
                    }
                }

                for (j = i + 1; j < 5; j++) {
                    size_t next_offset, next_limit;
                    const char *next_base;
                    int printable = 1;

                    offsets = is_32bit ? prpsoffsets32 : prpsoffsets64;
                    next_offset = off + offsets[j];
                    next_limit = off + descsz;
                    next_base = (const char *)(nbuf + next_offset);

                    while (next_offset < next_limit + offsets[i]) {
                        if (printable && !isprint((unsigned char)nbuf[next_offset])) {
                            printable = 0;
                        }
                        next_offset++;
                    }
                    if (printable) {
                        i = j;
                        break;
                    }
                }

                {
                    const char *start = (const char *)(nbuf + off + offsets[i]);
                    const char *end = start;

                    while (*end != '\0' && isprint((unsigned char)*end)) {
                        end++;
                    }
                    while (end > start && isspace((unsigned char)end[-1])) {
                        end--;
                    }

                    if (file_printf(fp, " %.*s", (int)(end - start), start) == -1) {
                        return 1;
                    }
                    *flags |= FLAGS_CORE_DUMP_INFO;
                    return 1;
                }

            next_i:
                continue;
            }
        }
    }

    return 0;
}