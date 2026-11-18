char* func0(char* text){
    regex_t regex;
    int ret;
    ret = regcomp(&regex, "ab*?", 1);
    if(ret){
        return "Regex compilation failed";
    }
    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);
    if(!ret){
        return "Found a match!";
    }
    return "Not matched!";
}