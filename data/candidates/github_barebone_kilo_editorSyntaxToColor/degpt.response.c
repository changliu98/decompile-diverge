int editorSyntaxToColor(int syntaxType)
{
    // Map syntax highlighting type to a color code
    switch(syntaxType) {
    case 2:
    case 3:
        // Return color code for syntax types 2 and 3
        return 0x24;
    case 4:
        // Return color code for syntax type 4
        return 0x21;
    case 5:
        // Return color code for syntax type 5
        return 0x20;
    case 6:
        // Return color code for syntax type 6
        return 0x23;
    case 7:
        // Return color code for syntax type 7
        return 0x1f;
    case 8:
        // Return color code for syntax type 8
        return 0x22;
    default:
        // Return default color code for unrecognized syntax types
        return 0x25;
    }
}