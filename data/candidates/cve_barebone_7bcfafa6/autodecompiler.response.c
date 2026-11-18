char *url_canonize2(char *out, char *in, size_t len, int escape_char,
                 unsigned int noescape_mask, unsigned int noescape_mask2,
                 unsigned int noescape_mask3)
{
    size_t i = 0;
    if (out == in) {
        while ((in[i] != 0) && (i < len)) {
            if ((in[i] == '%') || ((in[i] & 0xff) > 32 && (in[i] & 0xff) < 128 && !(noescape_mask & (1 << (63 - (in[i] & 0xff)))))) {
                out = url_canonize2(out, in + i, len - i, escape_char, noescape_mask, noescape_mask2, noescape_mask3);
                return out;
            }
            out++;
            i++;
        }
        *out = 0;
        return out;
    }

    while ((in[i] != 0) && (i < len)) {
        unsigned char c = in[i];
        if (c != '%') {
            if (!(escape_char & (1 << (c - 33))) && ((c < 33) || (c > 126) || ((c >= 65 && c <= 90) ? (noescape_mask2 & (1 << (95 - c))) : ((c >= 97 && c <= 122) ? (noescape_mask3 & (1 << (127 - c))) : (noescape_mask & (1 << (63 - c)))))) {
                *out = c;
            } else {
                *out = 0;
                return out;
            }
        } else {
            unsigned char c1 = in[i + 1];
            unsigned char c2 = in[i + 2];
            if (((c1 >= '0' && c1 <= '9') || (c1 >= 'A' && c1 <= 'F') || (c1 >= 'a' && c1 <= 'f')) && ((c2 >= '0' && c2 <= '9') || (c2 >= 'A' && c2 <= 'F') || (c2 >= 'a' && c2 <= 'f'))) {
                unsigned char c = ((c1 >= 'a' ? c1 - 'a' + 10 : c1 >= 'A' ? c1 - 'A' + 10 : c1 - '0') << 4) | (c2 >= 'a' ? c2 - 'a' + 10 : c2 >= 'A' ? c2 - 'A' + 10 : c2 - '0');
                if ((c < 33) || (c > 126) || ((c >= 65 && c <= 90) ? (noescape_mask2 & (1 << (95 - c))) : ((c >= 97 && c <= 122) ? (noescape_mask3 & (1 << (127 - c))) : (noescape_mask & (1 << (63 - c)))))) {
                    *out = c;
                    i += 2;
                } else {
                    if (c1 >= 'a')
                        c1 -= ('a' - 'A');
                    if (c2 >= 'a')
                        c2 -= ('a' - 'A');
                    *out++ = '%';
                    *out++ = c1;
                    *out++ = c2;
                    i += 2;
                }
            } else {
                *out = 0;
                return out;
            }
        }
        out++;
        i++;
    }
    *out = 0;
    return out;
}