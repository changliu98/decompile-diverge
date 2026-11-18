/*
 * Converts a test command code to its corresponding string representation.
 *
 * @param test The integer command code to convert.
 * @return A static string representing the command, or "unknown" if the code is not recognized.
 */
char * test_to_str(int command_code)
{
    /* Check if the test code corresponds to the 'sendpage' command */
    if (command_code == 0x80) {
        return "sendpage";
    }
    /* Check if the test code corresponds to the 'sendmsg' command */
    else if (command_code == 0x81) {
        return "sendmsg";
    }
    /* Return "unknown" for any unrecognized test codes */
    else {
        return "unknown";
    }
}