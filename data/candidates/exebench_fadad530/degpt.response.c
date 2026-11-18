/**
 * Converts a sequence string to IUPAC nucleotide codes.
 * 
 * @param seq   Pointer to the null-terminated sequence string to be processed.
 *              The string is modified in place.
 * @param is_aseq Flag indicating the type of sequence:
 *                - 0: DNA/RNA sequence. Only valid IUPAC nucleotide characters are allowed.
 *                - Non-zero: Amino acid sequence. In addition to valid IUPAC nucleotide 
 *                  characters, whitespace and common alignment characters (' ', '.', '_', '-', '~') 
 *                  are also allowed.
 * 
 * Any character not recognized as valid for the specified sequence type is replaced with 'N'.
 */
void ToIUPAC(char *sequence, int is_amino_acid)
{
    // Iterate through each character of the sequence until the null terminator
    for (; *sequence != '\0'; sequence++) {
        if (is_amino_acid == 0) {
            // For DNA/RNA sequences: check if the character is a valid IUPAC nucleotide
            // Valid characters: ACGTUNRYMKSWHBVD (both uppercase and lowercase)
            if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *sequence) == NULL) {
                // Replace invalid characters with 'N'
                *sequence = 'N';
            }
        } else {
            // For amino acid sequences: allow valid IUPAC nucleotides plus common alignment characters
            // Valid characters: ACGTUNRYMKSWHBVD (both cases), ' ', '.', '_', '-', '~'
            if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *sequence) == NULL &&
                *sequence != ' ' && *sequence != '.' && *sequence != '_' && *sequence != '-' && *sequence != '~') {
                // Replace invalid characters with 'N'
                *sequence = 'N';
            }
        }
    }
}