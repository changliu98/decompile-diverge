static int ensureNodeTransitionCapacity(ValArray *AL,size_t newcapacity)
{
 size_t oldcapacity;
 size_t newsize;
 ElementType *p;
 char result;

 if (AL == NULL) {
  result = 0;
 }
 else if (newcapacity <= AL->capacity) {
  result = 1;
 }
 else {
  if (AL->capacity > 0) {
   oldcapacity = AL->capacity;
  } else {
   oldcapacity = sizeof(ElementType);
  }
  newsize = oldcapacity;
  while (1) {
   if (newsize >= newcapacity) break;
   if (newsize >= ((size_t)-1)/2) {
    newsize = newcapacity;
    break;
   }
   newsize *= 2;
  }
  p = (ElementType*)realloc(AL->contents,newsize*sizeof(ElementType));
  if (p == NULL) {
   result = 0;
  } else {
   memset(p+AL->capacity,0,(newsize-AL->capacity)*sizeof(ElementType));
   AL->contents = p;
   AL->capacity = newsize;
   result = 1;
  }
 }
 return result;
}