const char* func0(const char* str) {
    int len = strlen(str);
    char last_char = str[len - 1];
    
    if (last_char == '0' || last_char == '2' || last_char == '4' || 
        last_char == '6' || last_char == '8' || last_char == 'A' || 
        last_char == 'C' || last_char == 'E') {
        return "True";
    } else {
        return "False";
    }
}