char *strip_comments( char *string ) {

    char *stripped = malloc( strlen(string)+1 );
    strcpy( stripped, string );

    regex_t regex;
    int reti;
    regmatch_t matches[2];
    char *begin, *end;

    reti = regcomp(&regex, " ?\\([^)]+\\)", 1);
    if( !reti ) {
        while( !regexec(&regex, stripped, 2, matches, 0) ) {
            begin = matches[0].rm_so + stripped;
            end = matches[0].rm_eo + stripped;
            memmove( begin, end, strlen(stripped)-matches[0].rm_eo+1 );
        }
        regfree(&regex);
    }

    return stripped;
}