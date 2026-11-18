void parse_string_node(char **input, size_t len) {
    struct input_t *inp = malloc(sizeof(struct input_t));
    inp->version = 3;
    inp->str = (char *)malloc(sizeof(char) * (len + 1));
    memcpy(inp->str, *input, len);
    inp->str[len] = '\0';
    inp->len = strlen(inp->str);
    set_input(0, inp);
}