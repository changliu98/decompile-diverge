void scsi_sanitize_inquiry_string(uchar *string_buffer, int buffer_length)
{
    // Iterate through each character in the string up to the specified length
    for (int index = 0; index < buffer_length; index++) {
        // Stop processing if the null terminator is encountered
        if (string_buffer[index] == '\0') {
            break;
        }
        // Replace non-printable ASCII characters (outside the range 0x20 to 0x7e) with a space
        if (string_buffer[index] < 0x20 || string_buffer[index] > 0x7e) {
            string_buffer[index] = ' ';
        }
    }
}