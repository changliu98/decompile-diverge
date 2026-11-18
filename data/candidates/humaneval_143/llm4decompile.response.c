void func0(char *sentence, char *out)
{
    int word_len = 0;
    int out_index = 0;
    int sentence_index = 0;
    int index;
    int is_prime;

    while (sentence[sentence_index] != '\0') {
        if (sentence[sentence_index] == ' ') {
            is_prime = 1;
            if (word_len > 1) {
                for (index = 2; index * index <= word_len; index++) {
                    if (word_len % index == 0) {
                        is_prime = 0;
                        break;
                    }
                }
            } else {
                is_prime = 0;
            }
            if (is_prime) {
                if (out_index > 0) {
                    out[out_index] = ' ';
                    out_index++;
                }
                memcpy(out + out_index, sentence + sentence_index - word_len,
                       (size_t) word_len);
                out_index += word_len;
            }
            word_len = 0;
        } else {
            word_len++;
        }
        sentence_index++;
    }

    is_prime = 1;
    if (word_len > 1) {
        for (index = 2; index * index <= word_len; index++) {
            if (word_len % index == 0) {
                is_prime = 0;
                break;
            }
        }
    } else {
        is_prime = 0;
    }
    if (is_prime) {
        if (out_index > 0) {
            out[out_index] = ' ';
            out_index++;
        }
        memcpy(out + out_index, sentence + sentence_index - word_len,
               (size_t) word_len);
        out_index += word_len;
    }
    out[out_index] = '\0';
}