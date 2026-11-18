utf8proc_ssize_t __cdecl utf8proc_decompose_char(
    utf8proc_int32_t uc,
    utf8proc_int32_t *dst,
    utf8proc_ssize_t bufsize,
    utf8proc_option_t options,
    int *last_boundclass)
{
    // Constants for Hangul decomposition
    const utf8proc_int32_t HANGUL_SBASE  = 0xAC00;  // 44032
    const utf8proc_int32_t HANGUL_LBASE  = 0x1100;  // 4352
    const utf8proc_int32_t HANGUL_VBASE  = 0x1161;  // 4449
    const utf8proc_int32_t HANGUL_TBASE  = 0x11A7;  // 4519
    const utf8proc_int32_t HANGUL_SCOUNT = 11172;
    const utf8proc_int32_t HANGUL_NCOUNT = 588;
    const utf8proc_int32_t HANGUL_TCOUNT = 28;

    if ((unsigned int)uc >= 0x110000)
        return UTF8PROC_ERROR_NOTASSIGNED; // -4

    const utf8proc_property_t *property = unsafe_get_property(uc);
    utf8proc_propval_t category = property->category;
    utf8proc_int32_t hangul_sindex = uc - HANGUL_SBASE;

    // Hangul Decomposition
    if ((options & (UTF8PROC_COMPOSE | UTF8PROC_DECOMPOSE)) != 0 && 
        (unsigned int)hangul_sindex <= HANGUL_SCOUNT - 1)
    {
        if (bufsize >= 1)
        {
            *dst = hangul_sindex / HANGUL_NCOUNT + HANGUL_LBASE;
            if (bufsize >= 2)
                dst[1] = (hangul_sindex % HANGUL_NCOUNT) / HANGUL_TCOUNT + HANGUL_VBASE;
        }
        
        if (hangul_sindex % HANGUL_TCOUNT)
        {
            if (bufsize >= 3)
                dst[2] = (hangul_sindex % HANGUL_TCOUNT) + HANGUL_TBASE;
            return 3;
        }
        return 2;
    }

    // Remove unassigned codepoints if requested
    if ((options & UTF8PROC_STRIP_NA) != 0 && !category)
        return 0;

    // Reject unassigned codepoints if requested
    if ((options & UTF8PROC_REJECTNA) != 0 && !category)
        return UTF8PROC_ERROR_NOTASSIGNED; // -4

    // Strip zero-width characters
    if ((options & UTF8PROC_IGNORE) != 0 && ((property->combining >> 18) & 1))
        return 0;

    // Strip default ignorable codepoints
    if ((options & UTF8PROC_STRIP_CC) != 0 && !category)
        return 0;

    // Character substitution (LUMP)
    if ((options & UTF8PROC_LUMP) != 0)
    {
        utf8proc_option_t sub_options = options & ~UTF8PROC_LUMP;
        
        if (category == UTF8PROC_CATEGORY_ZS)
            return utf8proc_decompose_char(' ', dst, bufsize, sub_options, last_boundclass);
        
        if (uc == 0x2018 || uc == 0x2019 || uc == 0x02BC || uc == 0x02C8)
            return utf8proc_decompose_char('\'', dst, bufsize, sub_options, last_boundclass);
            
        if (category == UTF8PROC_CATEGORY_PD || uc == 0x2212)
            return utf8proc_decompose_char('-', dst, bufsize, sub_options, last_boundclass);

        switch (uc)
        {
            case 0x2044: // ⁄
            case 0x2215: // ∕
                return utf8proc_decompose_char('/', dst, bufsize, sub_options, last_boundclass);
            case 0x2236: // ∶
                return utf8proc_decompose_char(':', dst, bufsize, sub_options, last_boundclass);
            case 0x2039: // ‹
            case 0x2329: // 〈
            case 0x3008: // 〈
                return utf8proc_decompose_char('<', dst, bufsize, sub_options, last_boundclass);
            case 0x203A: // ›
            case 0x232A: // 〉
            case 0x3009: // 〉
                return utf8proc_decompose_char('>', dst, bufsize, sub_options, last_boundclass);
            case 0x2216: // ∖
                return utf8proc_decompose_char('\\', dst, bufsize, sub_options, last_boundclass);
            case 0x02C4: // ˄
            case 0x02C6: // ˆ
            case 0x2038: // ‸
            case 0x2303: // ⌃
                return utf8proc_decompose_char('^', dst, bufsize, sub_options, last_boundclass);
            case 0x02CD: // ˍ
                return utf8proc_decompose_char('_', dst, bufsize, sub_options, last_boundclass);
            case 0x02CB: // ˋ
                return utf8proc_decompose_char('`', dst, bufsize, sub_options, last_boundclass);
            case 0x2223: // ∣
                return utf8proc_decompose_char('|', dst, bufsize, sub_options, last_boundclass);
            case 0x223C: // ∼
                return utf8proc_decompose_char('~', dst, bufsize, sub_options, last_boundclass);
        }

        if (category == UTF8PROC_CATEGORY_PC || uc == 0x02CD)
            return utf8proc_decompose_char('_', dst, bufsize, sub_options, last_boundclass);

        // Convert line breaks to newlines
        if ((options & UTF8PROC_COMPOSE) != 0 && 
            (options & UTF8PROC_DECOMPOSE) != 0 && 
            (category == UTF8PROC_CATEGORY_ZL || category == UTF8PROC_CATEGORY_ZP))
        {
            return utf8proc_decompose_char('\n', dst, bufsize, sub_options, last_boundclass);
        }
    }

    // Strip marks
    if ((options & UTF8PROC_NSMX) != 0 && 
        (category == UTF8PROC_CATEGORY_MN || category == UTF8PROC_CATEGORY_MC || category == UTF8PROC_CATEGORY_ME))
    {
        return 0;
    }

    // Case folding
    if ((options & UTF8PROC_CASEFOLD) != 0 && property->casefold_seqindex != 0xFFFF)
    {
        return seqindex_write_char_decomposed(property->casefold_seqindex, dst, bufsize, options, last_boundclass);
    }

    // Canonical decomposition
    if ((options & (UTF8PROC_COMPOSE | UTF8PROC_DECOMPOSE)) != 0 && 
        property->decomp_seqindex != 0xFFFF && 
        (!property->decomp_type || (options & UTF8PROC_COMPAT) != 0))
    {
        return seqindex_write_char_decomposed(property->decomp_seqindex, dst, bufsize, options, last_boundclass);
    }

    // Grapheme cluster segmentation (insert boundary marker)
    if ((options & UTF8PROC_CHARBOUND) != 0)
    {
        utf8proc_propval_t boundclass = (property->combining >> 24) & 0x3F;
        utf8proc_propval_t extended = (property->combining >> 30) & 0x3;
        
        if (grapheme_break_extended(0, boundclass, 0, extended, last_boundclass))
        {
            if (bufsize >= 1)
                *dst = -1;
            if (bufsize >= 2)
                dst[1] = uc;
            return 2;
        }
    }

    // Default: write the character as-is
    if (bufsize >= 1)
        *dst = uc;
    
    return 1;
}