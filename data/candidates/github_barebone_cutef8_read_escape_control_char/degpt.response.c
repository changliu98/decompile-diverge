// Reads an escape control character and returns its corresponding ASCII value.
// If the character is not a recognized escape sequence, returns the character itself.
char read_escape_control_char(char input_char)
{
    switch (input_char) {
        case 'n': return '\n'; // Newline
        case 't': return '\t'; // Horizontal tab
        case 'r': return '\r'; // Carriage return
        case 'e': return '\x1b'; // Escape character
        case 'b': return '\b'; // Backspace
        case 'f': return '\f'; // Form feed
        case 'v': return '\v'; // Vertical tab
        case 'a': return '\a'; // Alert (bell)
        default: return input_char; // Return the character unchanged if not a recognized escape
    }
}