char *gdb_to_rz_profile(const char *gdb_profile) {
    void *sb = NULL;
    char *p = NULL;
    char *nl = NULL;
    char name[0xc0];
    char type[0xd0];
    int size = 0;
    int reg_size = 0;
    int offset = 0;
    int flags = 0;
    int count = 0;
    int sizes[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

    if (!gdb_profile) {
        return NULL;
    }

    sb = rz_strbuf_new("");
    if (!sb) {
        return NULL;
    }

    p = rz_str_trim_head_ro(gdb_profile);

    if (rz_str_startswith(p, "l ")) {
        p = strchr(p, '\n');
        if (!p) {
            rz_strbuf_free(sb);
            return NULL;
        }
        p++;
    }

    while (*p) {
        // Skip whitespaces
        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        nl = strchr(p, '\n');
        if (nl) {
            *nl = '\0';
        } else {
            fprintf(stderr, "Missing newline in profile: %s\n", p);
            rz_strbuf_free(sb);
            return NULL;
        }

        count = sscanf(p, "%s %s %d %d:%d %d", name, type, &size, &reg_size, &offset, &count);
        if (count < 6) {
            if (*p == '*') {
                p = nl + 1;
                continue;
            } else {
                fprintf(stderr, "Invalid register profile: %s\n", p);
                rz_strbuf_free(sb);
                return NULL;
            }
        }

        if (rz_str_startswith(name, "rflags")) {
            if (!nl) break;
            p = nl + 1;
            continue;
        }

        if (offset == 0) {
            if (!nl) break;
            p = nl + 1;
            continue;
        }

        flags = 0;
        if (count >= 7) {
            char *t = type;
            char *comma;
            while ((comma = strchr(t, ','))) {
                *comma = '\0';
                if (rz_str_startswith(t, "code")) {
                    flags |= 2;
                } else if (rz_str_startswith(t, "int")) {
                    flags |= 1;
                } else if (rz_str_startswith(t, "float")) {
                    flags |= 4;
                } else if (rz_str_startswith(t, "mmx")) {
                    flags |= 8;
                } else if (rz_str_startswith(t, "xmm")) {
                    flags |= 16;
                } else if (rz_str_startswith(t, "ymm")) {
                    flags |= 32;
                } else if (rz_str_startswith(t, "seg")) {
                    flags |= 256;
                } else if (rz_str_startswith(t, "fpu")) {
                    flags |= 64;
                } else if (rz_str_startswith(t, "mm")) {
                    flags |= 128;
                }
                t = comma + 1;
            }
        }

        if (type[0] == '\0') {
            if (!nl) break;
            p = nl + 1;
            continue;
        }

        if (!(flags & 32) && !(flags & 16)) {
            flags |= 2;
        }

        const char *flag_str = (flags & 256) ? "seg" : ((flags & 16) ? "xmm" : ((flags & 32) ? "ymm" : "gpr"));
        rz_strbuf_appendf(sb, "=PC %s\n", name); // Note: format string inferred from context
        rz_strbuf_appendf(sb, "%s %s %d %d:%d %d\n", flag_str, name, sizes[size], reg_size, offset, count);
        
        // The exact format string at 0x30c3 is not fully clear, but it uses the variables above.
        // Based on the logic, it appends the register definition to the string buffer.

        if (!nl) {
            break;
        }
        p = nl + 1;
    }

    return rz_strbuf_drain(sb);
}