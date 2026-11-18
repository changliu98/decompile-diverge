// Function to apply Caesar cipher to the input text with a given offset
void ceasar(char *inputText, char shiftAmount)
{
    // Iterate through each character of the string until the null terminator
    for (uint charIndex = 0; inputText[charIndex] != '\0'; charIndex++) {
        // Check if the current character is an uppercase letter (A-Z) or lowercase letter (a-z)
        if (((inputText[charIndex] > '@' && inputText[charIndex] < '[') || (inputText[charIndex] > '`' && inputText[charIndex] < '{'))) {
            // Apply the offset by incrementing the character 'offset' times
            for (int shiftCounter = 0; shiftCounter < shiftAmount; shiftCounter++) {
                // Wrap around from 'Z' to before 'A' if the character is 'Z'
                if (inputText[charIndex] == 'Z') {
                    inputText[charIndex] = 'A' - 1;
                } 
                // Wrap around from 'z' to before 'a' if the character is 'z'
                else if (inputText[charIndex] == 'z') {
                    inputText[charIndex] = 'a' - 1;
                }
                // Increment the character to shift it by one position
                inputText[charIndex]++;
            }
        }
    }
}