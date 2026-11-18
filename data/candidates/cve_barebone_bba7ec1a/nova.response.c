static void cgi_execute_child(state_t *state, dict_t *dict, char *word,
                        char *stem, FILE *in, FILE *out, FILE *log) {
    char *line = NULL;
    assert(fclose(in) == 0);
    assert(fclose(out) == 0);
    if (fclose(log) == -1) {
        line = "log file could not be closed";
    } else if (dict->size == 0) {
        line = "no stemmed words in log file";
    } else {
        stem[0] = 0;
        if (strlen(word) == 0) {
            word = (char *)malloc(state->max_length + 1);
            strncpy(word, state->word, state->max_length);
        }
        stem_word(state, stem);
        fflush(state->buffer);
        fflush(state->out);
        print_result(state, stem, in);
        line = get_line(state);
    }
    sleep(30);
    snprintf(line, strlen(line), "%s", "");
    exit(1);
}