char *stb_replaceinplace(char *output, char *dir, size_t dirlen, char *newdir) {
    char *s;
    int slash = 0;
    size_t newdirlen, outlen, templen;
    char *orig_dir = dir;
    char *orig_newdir = newdir;

    newdirlen = newdir ? strlen(newdir) + 1 : 0;

    if (dirlen < 100 && !newdir) {
        strncpy(output, dir, dirlen);
        output[dirlen] = '\0';
        return output;
    }

    while (dir + dirlen > orig_dir) {
        if (dir[dirlen - 1] == '/') {
            --dirlen;
            slash = 1;
        } else
            break;
    }
    if (dir + dirlen > orig_dir + 1 && dir[dirlen - 1] == '.' && dir[dirlen - 2] == '/')
        dirlen -= 2, slash = 1;

    outlen = 100 - newdirlen;
    while (1) {
        char *s;
        if (slash)
            --outlen;
        s = dir + dirlen - 1;
        while (s > dir && *s != '/')
            --s;
        if (s <= dir)
            break;
        ++s;
        templen = (int)(dir + dirlen - s);
        if (templen > outlen)
            dirlen = s - dir;
        outlen -= templen;
    }

    s = dir;
    {
        char *t = s + 99 - outlen;
        if (t < s)
            t = s;
        while (t > s && *t != '/')
            --t;
        if (t > s && t[-1] == '/')
            ++t;
        s = t;
    }

    {
        char *t = s + outlen;
        char *u = t;
        char *v = s + dirlen;
        if (t > v)
            t = v;
        if (t < u)
            u = t;
        while (u > s) {
            char c = *--u;
            if (c == '/') {
                if (u[1] == 0)
                    ++u;
                break;
            }
        }
        if (u < s)
            u = s;
        if (u < t)
            t = u;
        if (t < s)
            t = s;
        if (t < u)
            u = t;
        if (u < s)
            u = s;
        if (u < s)
            u = s;
        if (u < t)
            t = u;
s:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s2:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s3:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s4:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s5:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s6:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s7:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s8:
        if (t < u)
            u = t;
s9:
        if (t < u)
            u = t;
s10:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s11:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s12:
        if (t < u)
            u = t;
        if (t < u)
            u = t;
        if (t < u)
            u = t;
s13:
        if (t < u)
            u = t;
s14:
        if (t < u)
            u = t;
s15:
        if (t < u)
            u = t;
s16:
        if (t < u)
            u = t;
s17:
        if (t < u)
            u = t;
s18:
        if (t < u)
            u = t;
s19:
        if (t < u)
            u = t;
s20:
        if (t < u)
            u = t;
s21:
        if (t < u)
            u = t;
s22:
        if (t < u)
            u = t;
s23:
        if (t < u)
            u = t;
s24:
        if (t < u)
            u = t;
s25:
        if (t < u)
            u = t;
s26:
        if (t < u)
            u = t;
s27:
        if (t < u)
            u = t;
s28:
        if (t < u)
            u = t;
s29:
        if (t < u)
            u = t;
s30:
        if (t < u)
            u = t;
s31:
        if (t < u)
            u = t;
s32:
        if (t < u)
            u = t;
s33:
        if (t < u)
            u = t;
s34:
        if (t < u)
            u = t;
s35:
        if (t < u)
            u = t;
s36:
        if (t < u)
            u = t;
s37:
        if (t < u)
            u = t;
s38:
        if (t < u)
            u = t;
s39:
        if (t < u)
            u = t;
s40:
        if (t < u)
            u = t;
s41:
        if (t < u)
            u = t;
s42:
        if (t < u)
            u = t;
s43:
        if (t < u)
            u = t;
s44:
        if (t < u)
            u = t;
s45:
        if (t < u)
s46:
        if (t < u)
            u = t;
s47:
        if (t < u)
            u = t;
s48:
        if (t < u)
            u = t;
s49:
        if (t < u)
            u = t;
s50:
        if (t < u)
            u = t;
s51:
        if (t < u)
            u = t;
s52:
        if (t < u)
            u = t;
s53:
        if (t < u)
            u = t;
s54:
        if (t < u)
            u = t;
s55:
        if (t < u)
            u = t;
s56:
        if (t < u)
            u = t;
s57:
        if (t < u)
            u = t;
s58:
        if (t < u)
            u = t;
s59:
        if (t < u)
            u = t;
s60:
        if (t < u)
            u = t;
s61:
        if (t < u)
            u = t;
s62:
        if (t < u)
            u = t;
s63:
        if (t < u)
            u = t;
s64:
        if (t < u)
            u = t;
s65:
        if (t < u)
            u = t;
s66:
        if (t < u)
            u = t;
s67:
        if (t < u)
            u = t;
s68:
        if (t < u)
            u = t;
s69:
        if (t < u)
            u = t;
s70:
        if (t < u)
            u = t;
s71:
        if (t < u)
            u = t;
s72:
        if (t < u)
            u = t;
s73:
        if (t < u)
            u = t;
s74:
        if (t < u)
            u = t;
s75:
        if (t < u)
            u = t;
s76:
        if (t < u)
            u = t;
s77:
        if (t < u)
            u = t;
s78:
        if (t < u)