void utf8_int_string(unsigned int unicode_value, char *string)
{
    if (string != NULL) {
        string[0] = '\0';
        if (unicode_value <= 0x7f) {
            string[0] = (char) unicode_value;
            string[1] = '\0';
        } else if (unicode_value <= 0x7ff) {
            string[0] = (char) ((unicode_value >> 6) & 0x1f | 0xc0);
            string[1] = (char) ((unicode_value) & 0x3f | 0x80);
            string[2] = '\0';
        } else if (unicode_value <= 0xffff) {
            string[0] = (char) ((unicode_value >> 12) & 0x0f | 0xe0);
            string[1] = (char) ((unicode_value >> 6) & 0x3f | 0x80);
            string[2] = (char) ((unicode_value) & 0x3f | 0x80);
            string[3] = '\0';
        } else if (unicode_value <= 0x1fffff) {
            string[0] = (char) ((unicode_value >> 18) & 0x07 | 0xf0);
            string[1] = (char) ((unicode_value >> 12) & 0x3f | 0x80);
            string[2] = (char) ((unicode_value >> 6) & 0x3f | 0x80);
            string[3] = (char) ((unicode_value) & 0x3f | 0x80);
            string[4] = '\0';
        }
    }
}