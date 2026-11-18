cJSON *__cdecl cJSON_CreateDoubleArray(const double *numbers, int count)
{
  bool v3; // [rsp+7h] [rbp-39h]
  cJSON *a; // [rsp+8h] [rbp-38h]
  cJSON *p; // [rsp+10h] [rbp-30h]
  cJSON *n; // [rsp+18h] [rbp-28h]
  size_t i; // [rsp+20h] [rbp-20h]

  n = 0LL;
  p = 0LL;
  if ( count < 0 || !numbers )
    return 0LL;
  a = cJSON_CreateArray();
  for ( i = 0LL; ; ++i )
  {
    v3 = 0;
    if ( a )
      v3 = i < count;
    if ( !v3 )
      break;
    n = cJSON_CreateNumber(numbers[i]);
    if ( !n )
    {
      cJSON_Delete(a);
      return 0LL;
    }
    if ( i )
      suffix_object(p, n);
    else
      a->child = n;
    p = n;
  }
  if ( a && a->child )
    a->child->prev = n;
  return a;
}