void __cdecl nextPage(int numPages, int *page)
{
    // Check if the current page is not the last page (0-based index)
    if (*page != numPages - 1)
    {
        // Increment the current page index
        (*page)++;
    }
}