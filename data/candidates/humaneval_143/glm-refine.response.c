void __cdecl func0(const char *sentence, char *out)
{
    int out_index = 0;
    int word_len = 0;
    int i;

    for (i = 0; sentence[i] != '\0'; ++i)
    {
        if (sentence[i] == ' ')
        {
            if (is_prime(word_len))
            {
                if (out_index > 0) {
                    out[out_index++] = ' ';
                }
                memcpy(&out[out_index], &sentence[i - word_len], word_len);
                out_index += word_len;
            }
            word_len = 0;
        }
        else
        {
            ++word_len;
        }
    }

    // Handle the last word (if the string doesn't end with a space)
    if (is_prime(word_len))
    {
        if (out_index > 0) {
            out[out_index++] = ' ';
        }
        memcpy(&out[out_index], &sentence[i - word_len], word_len);
        out_index += word_len;
    }
    
    out[out_index] = '\0';
}