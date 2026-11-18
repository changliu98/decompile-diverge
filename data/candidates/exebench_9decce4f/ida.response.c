void __cdecl nextPage(int numPages, int *page)
{
  if ( *page != numPages - 1 )
    ++*page;
}