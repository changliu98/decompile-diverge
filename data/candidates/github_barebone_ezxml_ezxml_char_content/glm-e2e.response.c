void ezxml_char_content(struct ezxml *root, char *s, size_t len, char t) {
    struct ezxml *xml = root->parse_str_ptr[0];
    char *old_s = s;

    if (!xml || !xml->name || !len) {
        return;
    }

    s[len] = '\0';
    s = ezxml_decode(s, root->parse_str_ptr[1], t);
    len = strlen(s) + 1;

    if (xml->name[0] == '\0') {
        xml->name = s;
    } else {
        char *new_name;
        size_t old_len;

        if (xml->off & 0x40) {
            old_len = strlen(xml->name);
            new_name = realloc(xml->name, old_len + len);
        } else {
            new_name = malloc(strlen(xml->name) + len);
            memmove(new_name, xml->name, strlen(xml->name));
            free(xml->name);
        }

        xml->name = new_name;
        memmove(xml->name + old_len, s, len);

        if (s != old_s) {
            free(s);
        }
    }

    if (xml->name != old_s) {
        ezxml_set_flag(xml, 0x40);
    }
}