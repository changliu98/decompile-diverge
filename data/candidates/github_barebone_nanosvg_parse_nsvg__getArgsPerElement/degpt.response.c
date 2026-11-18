// Returns the number of arguments expected for a given SVG path command character.
// Returns -1 if the command is invalid or unrecognized.
int nsvg__getArgsPerElement(char command)
{
    switch(command) {
    // Arc command (absolute): 7 arguments (rx, ry, x-axis-rotation, large-arc-flag, sweep-flag, x, y)
    case 'A':
    case 'a':
        return 7;
    // Cubic Bezier curve command (absolute): 6 arguments (x1, y1, x2, y2, x, y)
    case 'C':
    case 'c':
        return 6;
    // Horizontal/Vertical line commands (absolute/relative): 1 argument (x for H/h, y for V/v)
    case 'H':
    case 'V':
    case 'h':
    case 'v':
        return 1;
    // Line, Move, and Smooth Quadratic Bezier commands (absolute/relative): 2 arguments (x, y)
    case 'L':
    case 'M':
    case 'T':
    case 'l':
    case 'm':
    case 't':
        return 2;
    // Quadratic Bezier and Smooth Cubic Bezier commands (absolute/relative): 4 arguments (x1, y1, x, y)
    case 'Q':
    case 'S':
    case 'q':
    case 's':
        return 4;
    // Close path command: 0 arguments
    case 'Z':
    case 'z':
        return 0;
    // Invalid or unrecognized command
    default:
        return -1;
    }
}