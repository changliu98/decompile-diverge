static unsigned long cag_option_get_print_indention(struct cag_option *options, unsigned long option_count)
{
    unsigned long max_indention = 20;
    unsigned long option_index;
    for (option_index = 0; option_index < option_count; option_index++) {
        unsigned long indention = 4;
        struct cag_option *option = &options[option_index];
        if (option->access_letters && option->access_letters[0]) {
            indention += 2 * strlen(option->access_letters) - 2 + 4;
            if (option->access_name) {
                indention += strlen(option->access_name) + 4;
            }
        }
        else if (option->access_name) {
            indention += strlen(option->access_name) + 6;
        }
        if (option->value_name) {
            indention += strlen(option->value_name) + 1;
        }
        if (indention > max_indention) {
            max_indention = indention;
        }
    }
    return max_indention;
}