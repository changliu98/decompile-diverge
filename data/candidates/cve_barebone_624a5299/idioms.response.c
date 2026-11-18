int jsi_ArraySpliceCmd(struct Jsi_Interp *interp, struct Jsi_Value *args, struct Jsi_Value *this, struct Jsi_Value **ret, struct Jsi_Func *funcPtr)
{
  struct Jsi_Value *start;
  struct Jsi_Value *howmany;
  struct Jsi_Number nstart;
  struct Jsi_Number nhow;
  struct Jsi_Obj *obj;
  struct Jsi_Obj *nobj;
  int argc;
  int ilen;
  int newlen;
  int curlen;
  int i;
  int j;
  int k;
  int istart;
  int rhowmany;
  int n;
  if (this->type != JSI_OT_OBJECT || !jsi_is_array(interp, this->d.obj))
  {
    jsi_error(interp, JSI_ERR_TYPE, "expected array object");
    return 1;
  }
  obj = this->d.obj;
  start = jsi_get_arg(interp, args, 0);
  howmany = jsi_get_arg(interp, args, 1);
  argc = jsi_get_argc(interp, args);
  istart = 0;
  ilen = (argc > 1) ? (argc - 2) : 0;
  curlen = (int)jsi_get_arraylen(interp, obj);
  if (start == ((void *)0))
  {
    jsi_set_null(interp, ret);
    return 0;
  }
  nobj = jsi_new_obj(interp, JSI_OT_ARRAY);
  jsi_set_ret(interp, ret, nobj);
  jsi_set_arraylen(interp, nobj, 0);
  if (jsi_get_number(interp, start, &nstart) == JSI_OK)
  {
    istart = (int)nstart;
    if (istart > curlen)
      return 0;
    if (istart < 0)
      istart += curlen;
    if (istart < 0)
      istart = 0;
  }
  rhowmany = curlen - istart;
  if (howmany == ((void *)0))
    goto done;
  if (jsi_get_number(interp, howmany, &nhow) != JSI_OK)
    goto done;
  rhowmany = (int)nhow;
  if (rhowmany >= (curlen - istart))
    rhowmany = (curlen - istart);
  if (rhowmany < 0)
    rhowmany = (curlen - istart);
  if (rhowmany < 0)
    goto done;
done:
  if (curlen < 0)
    jsi_set_arraylen(interp, obj, 0);
  jsi_get_arraylen(interp, obj);
  jsi_set_arraylen(interp, nobj, rhowmany);
  for (i = k = j = 0; i < rhowmany && i < curlen; i++)
  {
    if (obj->arr[i] != ((void *)0))
    {
      nobj->arr[k] = obj->arr[i];
      obj->arr[i] = ((void *)0);
    }
    k++;
    j++;
  }
  jsi_set_arraylen(interp, nobj, k);
  for (; i < curlen && rhowmany > 0; i++)
  {
    obj->arr[i - rhowmany] = obj->arr[i];
    obj->arr[i] = ((void *)0);
  }
  curlen -= j;
  newlen = curlen + argc - (1 + (argc > 1 ? 1 : 0));
  if (jsi_set_arraylen(interp, obj, newlen) <= 0)
  {
    jsi_error(interp, JSI_ERR_RANGE, "too long");
    jsi_set_null(interp, ret);
    return 1;
  }
  if (ilen > 0)
  {
    for (i = curlen - 1; i >= istart; i--)
    {
      obj->arr[ilen + i] = obj->arr[i];
      obj->arr[i] = ((void *)0);
    }
    for (i = istart, k = 2; k < argc; k++)
    {
      struct Jsi_Value *va = jsi_get_arg(interp, args, k);
      if (va != ((void *)0))
      {
        obj->arr[i] = ((void *)0);
        jsi_set_array(interp, &obj->arr[i], va);
      }
      i++;
    }
  }
  jsi_set_arraylen(interp, obj, newlen);
  return 1;
}