0xBC

void __cdecl extract(
        char *instring,
        int inlength,
        int fieldno,
        int valueno,
        int subvalueno,
        int *outstart,
        int *outlength)
{
    int subvalue_end_pos;
    int value_end_pos;
    int field_end_pos;
    int start_pos = 0;
    int eff_fieldno = fieldno;
    int eff_valueno = valueno;

    *outstart = 0;
    *outlength = 0;

    // Validate field number
    if (fieldno <= 0) {
        if (fieldno < 0)
            return;
        if (!valueno && !subvalueno) {
            *outlength = inlength;
            return;
        }
        eff_fieldno = 1;
    }

    // Skip to the requested field
    for (int curr_field = 1; curr_field < eff_fieldno; ++curr_field) {
        while (start_pos < inlength && 
               !(instring[start_pos] == FIELD_DELIM_1 && instring[start_pos + 1] == FIELD_DELIM_2)) {
            ++start_pos;
        }
        if (start_pos >= inlength)
            return;
        start_pos += 2;
    }

    // Find the end of the current field
    for (field_end_pos = start_pos; 
         field_end_pos < inlength && 
         !(instring[field_end_pos] == FIELD_DELIM_1 && instring[field_end_pos + 1] == FIELD_DELIM_2); 
         ++field_end_pos) {
        ;
    }

    // Validate value number
    if (valueno <= 0) {
        if (valueno < 0)
            return;
        if (!subvalueno) {
            *outstart = start_pos;
            *outlength = field_end_pos - start_pos;
            return;
        }
        eff_valueno = 1;
    }

    // Skip to the requested value
    for (int curr_value = 1; curr_value < eff_valueno; ++curr_value) {
        while (start_pos < inlength && 
               !(instring[start_pos] == FIELD_DELIM_1 && instring[start_pos + 1] == VALUE_DELIM_2)) {
            ++start_pos;
        }
        if (start_pos >= inlength)
            return;
        start_pos += 2;
        if (start_pos > field_end_pos)
            return;
    }

    // Find the end of the current value
    for (value_end_pos = start_pos; 
         value_end_pos < field_end_pos && 
         !(instring[value_end_pos] == FIELD_DELIM_1 && instring[value_end_pos + 1] == VALUE_DELIM_2); 
         ++value_end_pos) {
        ;
    }

    // Validate subvalue number
    if (subvalueno <= 0) {
        if (subvalueno < 0)
            return;
        *outstart = start_pos;
        *outlength = value_end_pos - start_pos;
        return; // Added explicit return for clarity, though original falls through safely
    }

    // Skip to the requested subvalue
    for (int curr_subvalue = 1; curr_subvalue < subvalueno; ++curr_subvalue) {
        while (start_pos < field_end_pos && 
               !(instring[start_pos] == FIELD_DELIM_1 && instring[start_pos + 1] == SUBVALUE_DELIM_2)) {
            ++start_pos;
        }
        if (start_pos >= inlength)
            return;
        if (++start_pos > value_end_pos)
            return;
    }

    // Find the end of the current subvalue
    for (subvalue_end_pos = start_pos; 
         subvalue_end_pos < value_end_pos && 
         !(instring[subvalue_end_pos] == FIELD_DELIM_1 && instring[subvalue_end_pos + 1] == SUBVALUE_DELIM_2); 
         ++subvalue_end_pos) {
        ;
    }

    *outstart = start_pos;
    *outlength = (subvalue_end_pos < value_end_pos) ? 
                 (subvalue_end_pos - start_pos) : 
                 (value_end_pos - start_pos);
}