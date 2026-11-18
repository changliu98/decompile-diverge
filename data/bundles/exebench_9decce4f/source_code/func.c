#include <stdio.h>

#include <string.h>

#include <stdlib.h>

void nextPage(int numPages, int *page)
{

 if(*page != numPages - 1)
  ++*page;
 return;
}
