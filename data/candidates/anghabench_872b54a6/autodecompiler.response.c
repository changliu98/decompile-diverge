int
byte_row_johab_hangul (
    int char_set)
{
    int index;

    if ((char_set >= _DtHelpCeIconvCharSetISO8859_1) &&
 (char_set < _DtHelpCeIconvCharSetMAX)) {
 index = char_set - _DtHelpCeIconvCharSetISO8859_1;
    }
    else {
 index = -1;
    }

    return index;
}