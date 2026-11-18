// Maps a type marker byte to a comparison type character.
// Returns true if the mapping is successful, false otherwise.
_Bool type_marker_to_cmp_type(uint8_t input_byte, uint8_t *output_char)
{
    // For type markers in range [0x00, 0x7F], the comparison type is null.
    if (input_byte < 0x80) {
        *output_char = '\0';
        return true;
    }
    // For type markers in range [0x80, 0x8F], the comparison type is 0x01.
    else if (input_byte < 0x90) {
        *output_char = '\x01';
        return true;
    }
    // For type markers in range [0x90, 0x9F], the comparison type is 0x02.
    else if (input_byte < 0xa0) {
        *output_char = '\x02';
        return true;
    }
    // For type markers in range [0xA0, 0xBF], the comparison type is 0x03.
    else if (input_byte < 0xc0) {
        *output_char = '\x03';
        return true;
    }
    // For type markers in range [0xC0, 0xDF], specific mappings are applied.
    else if (input_byte < 0xe0) {
        switch(input_byte) {
        case 0xc0:
            *output_char = '\x04';
            return true;
        case 0xc2:
        case 0xc3:
            *output_char = '\x05';
            return true;
        case 0xc4:
            *output_char = '\x06';
            return true;
        case 0xc5:
            *output_char = '\a';
            return true;
        case 0xc6:
            *output_char = '\b';
            return true;
        case 199:
            *output_char = '\t';
            return true;
        case 200:
            *output_char = '\n';
            return true;
        case 0xc9:
            *output_char = '\v';
            return true;
        case 0xca:
            *output_char = '\f';
            return true;
        case 0xcb:
            *output_char = '\r';
            return true;
        case 0xcc:
            *output_char = '\x0e';
            return true;
        case 0xcd:
            *output_char = '\x0f';
            return true;
        case 0xce:
            *output_char = '\x10';
            return true;
        case 0xcf:
            *output_char = '\x11';
            return true;
        case 0xd0:
            *output_char = '\x12';
            return true;
        case 0xd1:
            *output_char = '\x13';
            return true;
        case 0xd2:
            *output_char = '\x14';
            return true;
        case 0xd3:
            *output_char = '\x15';
            return true;
        case 0xd4:
            *output_char = '\x16';
            return true;
        case 0xd5:
            *output_char = '\x17';
            return true;
        case 0xd6:
            *output_char = '\x18';
            return true;
        case 0xd7:
            *output_char = '\x19';
            return true;
        case 0xd8:
            *output_char = '\x1a';
            return true;
        case 0xd9:
            *output_char = '\x1b';
            return true;
        case 0xda:
            *output_char = '\x1c';
            return true;
        case 0xdb:
            *output_char = '\x1d';
            return true;
        case 0xdc:
            *output_char = '\x1e';
            return true;
        case 0xdd:
            *output_char = '\x1f';
            return true;
        case 0xde:
            *output_char = ' ';
            return true;
        case 0xdf:
            *output_char = '!';
            return true;
        default:
            // Unsupported type marker in this range.
            return false;
        }
    }
    // For type markers >= 0xE0, the comparison type is a double quote.
    else {
        *output_char = '\"';
        return true;
    }
}