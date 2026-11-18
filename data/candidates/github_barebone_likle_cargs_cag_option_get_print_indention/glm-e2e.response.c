size_t cag_option_get_print_indention(struct cag_option *options, size_t option_count) {
    size_t max_indention = 20;
    size_t i;
    
    for (i = 0; i < option_count; ++i) {
        size_t current_indention = 4;
        struct cag_option *option = &options[i];
        
        if (option->name != NULL && option->name[0] != '\0') {
            current_indention += strlen(option->name) * 4 - 2;
            
            if (option->value_name != NULL) {
                current_indention += strlen(option->value_name) + 4;
            }
        } else {
            if (option->value_name != NULL) {
                current_indention += strlen(option->value_name) + 2;
            }
        }
        
        if (option->description != NULL) {
            current_indention += strlen(option->description) + 1;
        }
        
        if (current_indention > max_indention) {
            max_indention = current_indention;
        }
    }
    
    return max_indention;
}