int SortedArraySearch(ARRAY *arr, char *key)
{
unsigned int i, j, k;
int cmp;
int idx;

if (!arr)
  return(-1);

i = 0;
j = arr->cur;
k = 0;

if ((j == 0) || (j == 1))
  k = j;

while (i != j)
{
  k = (i + j) / 2;
  cmp = (*arr->compare)(key, arr->data[k]);
  if (cmp < 0)
    j = k;
  else
  if (cmp > 0)
    i = k + 1;
  else
  {
    idx = k;
    goto done;
  }
}

idx = -1;

done:
return(idx);
}