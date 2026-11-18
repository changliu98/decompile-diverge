void free_grib_array(grib_accessor* a)
{
  grib_accessor* next;

  if(a->name) free(a->name);
  if(a->type) free(a->type);
  if(a->length) free(a->length);
  if(a->grib) free(a->grib);
  if(a->grib_buffer) free(a->grib_buffer);

  a=array->first;
  while(a)
  {
    next=a->same;
    free(a);
    a=next;
  }
  array->first=NULL;
}