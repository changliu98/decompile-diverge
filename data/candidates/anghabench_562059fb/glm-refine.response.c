const char *selectOpName(int id)
{
    // Lookup table for the supported set operations.
    // Indices 128, 129, and 130 map to INTERSECT, EXCEPT, and UNION ALL respectively.
    static const char *const op_names[] = {
        "INTERSECT",
        "EXCEPT",
        "UNION ALL"
    };

    // Check if the ID falls within the valid range of the lookup table
    if (id >= 128 && id <= 130)
    {
        return op_names[id - 128];
    }

    // Default fallback
    return "UNION";
}