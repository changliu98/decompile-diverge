char *__cdecl func0(const char *word)
{
    int len = strlen(word);
    char found_vowel = 0;

    // Iterate backwards through the word, skipping the first and last characters
    for (int i = len - 2; i >= 1; --i)
    {
        char prev = word[i - 1];
        char curr = word[i];
        char next = word[i + 1];

        // Check if the current character is a vowel, 
        // and is surrounded by non-vowels (consonants or other non-vowel characters)
        if (is_vowel(curr) && !is_vowel(next) && !is_vowel(prev))
        {
            found_vowel = curr;
            break; // Found the last matching vowel, no need to keep searching
        }
    }

    func0_out = found_vowel;
    return &func0_out;
}