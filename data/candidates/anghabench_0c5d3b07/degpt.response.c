/*
 * get_priority_string - Converts a priority code to its string representation.
 *
 * @prio: The priority code to convert.
 *
 * Returns: A static string describing the priority level.
 *          Returns "Invalid" for unknown priority codes.
 */
char * get_priority_string(int priority_code)
{
  switch(priority_code) {
  case 0x80:
    return "Unavailable";
  case 0x81:
    return "Preferred";
  case 0x82:
    return "Neutral";
  case 0x83:
    return "Low";
  default:
    return "Invalid";
  }
}