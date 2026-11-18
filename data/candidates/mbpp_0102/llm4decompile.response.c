char *func0(char *word, char *output)
{
    int word_index = 0;
    int output_index = 0;
    int capitalize_next = 1;

    while (word[word_index] != '\0') {
        if (word[word_index] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                output[output_index] = toupper(word[word_index]);
                capitalize_next = 0;
            } else {
                output[output_index] = word[word_index];
            }
            output_index++;
        }
        word_index++;
    }
    output[output_index] = '\0';

    return output;
}