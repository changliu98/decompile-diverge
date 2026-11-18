int endGB(char *inputString, int *offsetValue)
{
    // Search for the first occurrence of "//" in the string s
    char *markerPosition = strstr(inputString, "//");
    // If "//" is not found, search for "LOCUS" instead
    if (markerPosition == NULL) {
        markerPosition = strstr(inputString, "LOCUS");
        // Set addend to 0 when "LOCUS" is used as the marker
        *offsetValue = 0;
        // Return 1 if "LOCUS" is found at the beginning of the string, 0 otherwise
        return markerPosition == inputString;
    }
    // If "//" is found, set addend to 0
    *offsetValue = 0;
    // Return 1 to indicate that "//" was found
    return 1;
}