size_t utf8NextCharLen(const char *s, size_t index, size_t length) {
    size_t total_len = 0;

    if (index >= length) {
        return 0;
    }

    size_t current_index = index;
    size_t char_len;
    uint32_t codepoint = utf8DecodeChar(s + current_index, &char_len);
    
    total_len += char_len;
    current_index += char_len;
    int current_width = utf8CharWidth(codepoint);

    while (current_index < length) {
        codepoint = utf8DecodeChar(s + current_index, &char_len);
        
        if (isCombiningMark(codepoint) != 0 && (current_index + char_len) < length) {
            total_len += char_len;
            current_index += char_len;
            
            codepoint = utf8DecodeChar(s + current_index, &char_len);
            total_len += char_len;
            current_index += char_len;
        } else if (isVariationSelector(codepoint) != 0) {
            total_len += char_len;
            current_index += char_len;
        } else if (current_width != 0 && isGraphemeExtend(codepoint) != 0) {
            total_len += char_len;
            current_index += char_len;
            current_width = 0;
        } else {
            break;
        }
    }

    return total_len;
}