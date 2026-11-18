// Function to validate if a string meets specific password complexity requirements.
// Returns true if the string is between 6 and 12 characters long and contains
// at least one lowercase letter, one uppercase letter, one digit, and one special character ('$','#','@').
// Returns false otherwise.
_Bool func0(char *password)
{
    // Calculate the length of the input string
    size_t passwordLength = strlen(password);
    
    // Check if the string length is within the valid range [6, 12]
    if (passwordLength < 6 || passwordLength > 12) {
        return false;
    }

    // Initialize flags to track the presence of required character types
    bool hasLowercase = false;
    bool hasUppercase = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    // Iterate through each character in the string
    for (size_t i = 0; i < len; i++) {
        // Cast to unsigned char to ensure safe behavior with islower, isupper, etc.
        unsigned char c = (unsigned char)p[i];
        
        // Check if the character is a lowercase letter
        if (islower(c)) {
            hasLower = true;
        } 
        // Check if the character is an uppercase letter
        else if (isupper(c)) {
            hasUpper = true;
        } 
        // Check if the character is a digit
        else if (isdigit(c)) {
            hasDigit = true;
        } 
        // Check if the character is one of the allowed special characters
        else if (c == '$' || c == '#' || c == '@') {
            hasSpecial = true;
        } 
        // If the character is not allowed, return false immediately
        else {
            return false;
        }
    }

    // Return true only if all required character types are present
    return hasLower && hasUpper && hasDigit && hasSpecial;
}