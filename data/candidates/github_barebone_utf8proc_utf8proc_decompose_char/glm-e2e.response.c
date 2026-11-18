int64_t utf8proc_decompose_char(int32_t uc, int32_t *dst, int64_t bufsize, int32_t options, int *last_boundclass) {
    int64_t ret_val;
    const utf8proc_property_t *property;
    int16_t category;
    int32_t hangul_index;
    int32_t t;
    int8_t boundary;

    if (uc < 0 || uc >= 0x110000) {
        ret_val = UTF8PROC_ERROR_NOTASSIGNED;
        goto end;
    }

    property = (const utf8proc_property_t *)unsafe_get_property(uc);
    category = property->field0;
    hangul_index = uc - UTF8PROC_HANGUL_SBASE;

    if (options & 0x18) {
        if (hangul_index >= 0 && hangul_index < UTF8PROC_HANGUL_SCOUNT) {
            if (bufsize >= 1) {
                dst[0] = UTF8PROC_HANGUL_LBASE + hangul_index / UTF8PROC_HANGUL_NCOUNT;
                if (bufsize >= 2) {
                    dst[1] = UTF8PROC_HANGUL_VBASE + (hangul_index % UTF8PROC_HANGUL_NCOUNT) / UTF8PROC_HANGUL_TCOUNT;
                }
            }
            t = hangul_index % UTF8PROC_HANGUL_TCOUNT;
            if (t == 0) {
                ret_val = 2;
                goto end;
            }
            if (bufsize >= 3) {
                dst[2] = UTF8PROC_HANGUL_TBASE + t;
            }
            ret_val = 3;
            goto end;
        }
    }

    if (options & 0x40) {
        if (category == 0) {
            ret_val = UTF8PROC_ERROR_NOTASSIGNED;
            goto end;
        }
    }

    if (options & 0x20) {
        if ((property->field12 >> 18) & 1) {
            ret_val = 0;
            goto end;
        }
    }

    if (options & 0x4000) {
        if (category == 0) {
            ret_val = 0;
            goto end;
        }
    }

    if (options & 0x1000) {
        if (category == 0x17) {
            ret_val = utf8proc_decompose_char(0x20, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2018 || uc == 0x2019 || uc == 0x2BC || uc == 0x2C8) {
            ret_val = utf8proc_decompose_char(0x27, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (category == 0xD || uc == 0x2212) {
            ret_val = utf8proc_decompose_char(0x2D, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2044 || uc == 0x2215) {
            ret_val = utf8proc_decompose_char(0x2F, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2236) {
            ret_val = utf8proc_decompose_char(0x3A, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2039 || uc == 0x2329 || uc == 0x3008) {
            ret_val = utf8proc_decompose_char(0x3C, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x203A || uc == 0x232A || uc == 0x3009) {
            ret_val = utf8proc_decompose_char(0x3E, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2216) {
            ret_val = utf8proc_decompose_char(0x5C, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2C4 || uc == 0x2C6 || uc == 0x2038 || uc == 0x2303) {
            ret_val = utf8proc_decompose_char(0x5E, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (category == 0xC || uc == 0x2CD) {
            ret_val = utf8proc_decompose_char(0x5F, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2CB) {
            ret_val = utf8proc_decompose_char(0x60, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x2223) {
            ret_val = utf8proc_decompose_char(0x7C, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if (uc == 0x223C) {
            ret_val = utf8proc_decompose_char(0x7E, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
            goto end;
        }
        if ((options & 0x80) && (options & 0x100)) {
            if (category == 0x18 || category == 0x19) {
                ret_val = utf8proc_decompose_char(0xA, dst, bufsize, options & 0xFFFFEFFF, last_boundclass);
                goto end;
            }
        }
    }

    if (options & 0x2000) {
        if (category == 0x6 || category == 0x7 || category == 0x8) {
            ret_val = 0;
            goto end;
        }
    }

    if (options & 0x400) {
        if (property->field10 != 0xFFFF) {
            ret_val = seqindex_write_char_decomposed(property->field10, dst, bufsize, options, last_boundclass);
            goto end;
        }
    }

    if (options & 0x18) {
        if (property->field8 != 0xFFFF) {
            if (property->field6 != 0 && !(options & 0x4)) {
                // Do nothing
            } else {
                ret_val = seqindex_write_char_decomposed(property->field8, dst, bufsize, options, last_boundclass);
                goto end;
            }
        }
    }

    if (options & 0x800) {
        boundary = grapheme_break_extended(0, (property->field12 >> 24) & 0x3F, property->field12 >> 30, last_boundclass) & 1;
        if (boundary) {
            if (bufsize >= 1) dst[0] = -1;
            if (bufsize >= 2) dst[1] = uc;
            ret_val = 2;
            goto end;
        }
    }

    if (bufsize >= 1) {
        dst[0] = uc;
    }
    ret_val = 1;

end:
    return ret_val;
}