char* func0(char* param1) {
    int i;
    
    strcpy(toggled_string, param1);
    
    for (i = 0; toggled_string[i] != '\0'; i++) {
        if (isupper(toggled_string[i])) {
            toggled_string[i] = tolower(toggled_string[i]);
        } else if (islower(toggled_string[i])) {
            toggled_string[i] = toupper(toggled_string[i]);
        }
    }
    
    return toggled_string;
}