Optimized and annotated for reverse engineering
void __cdecl previousPage(int numPages, int *page)
{
    /*
    * Analysis:
    * 1. The 'numPages' parameter is completely unused within this function. 
    *    It might be a leftover from a larger refactored function, used for 
    *    alignment, or expected by a standardized callback interface.
    * 2. The function acts as a decrementer for a zero-based page index.
    * 3. The 'if (*page)' check ensures the page index does not underflow 
    *    below 0 (acting as a floor/limit guard).
    */
    if (*page > 0) // Semantically identical to 'if (*page)' but explicitly shows the zero-bound check
    {
        --*page;
    }
}