char* func0(char* text, int n) {
    strcpy(new_text, text);
    
    regex_t regex;
    regmatch_t match;
    regcomp(&regex, "[aeiou]", REG_EXTENDED);
    
    int count = 0;
    char found = 0;
    
    // The assembly implements a do-while loop with a break condition
    do {
        if (count >= n) {
            found = 0;
        } else {
            found = (regexec(&regex, new_text, 1, &match, 0) == 0);
        }
        
        if (!found) {
            break;
        }
        
        new_text[match.rm_so] = ':';
        count++;
    } while (1);
    
    regfree(&regex);
    return new_text;
}