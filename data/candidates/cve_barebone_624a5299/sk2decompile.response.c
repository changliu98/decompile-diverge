Jsi_RC Jsi_RC jsi_ArraySpliceCmd(Jsi_Interp *interp, Jsi_Value *args,
                                 Jsi_Value *obj, Jsi_Value **ret,
                                 Jsi_HostRef *hostRef) {
  Jsi_Value *v0, *v1, *v2;
  Jsi_Object *o, *a;
  Jsi_Float f0, f1, f2, i, j, k, l, m, n;
  if (obj->u.type != 4 || !Jsi_ObjIsArray(interp, obj->value.object)) {
    return Jsi_LogMsg(interp, 1, "expected array object");
  }
  o = obj->value.object;
  v0 = Jsi_ValueArrayIndex(interp, args, 0);
  v1 = Jsi_ValueArrayIndex(interp, args, 1);
  n = Jsi_ValueGetLength(interp, args);
  j = 0;
  k = (n > 1) ? n - 2 : 0;
  l = Jsi_ObjGetLength(interp, o);
  m = l;
  if (!v0) {
    Jsi_ValueMakeNull(interp, ret);
    return 0;
  }
  a = Jsi_ObjNewType(interp, Jsi_TypeArray);
  Jsi_ValueMakeArrayObject(interp, ret, a);
  Jsi_ObjSetLength(interp, a, 0);
  if (Jsi_GetNumberFromValue(interp, v0, &f0) == JSI_OK) {
    j = (int)f0;
    if (j > l) return 0;
    if (j < 0) j += l;
    if (j < 0) j = 0;
  }
  f1 = l - j;
  if (v1 && Jsi_GetNumberFromValue(interp, v1, &f2) == JSI_OK) {
    f1 = (int)f2;
    if (f1 > l - j) f1 = l - j;
    if (f1 < 0) f1 = l - j;
    if (f1 < 0) return 0;
  }
  if (m < 0) Jsi_ObjSetLength(interp, o, 0);
  Jsi_ObjListifyArray(interp, o);
  Jsi_ObjArraySizer(interp, a, f1);
  i = 0;
  f2 = 0;
  for (j = j; i < f1 && i < m; i++, f2++) {
    if (o->data[j]) {
      a->data[i] = o->data[j];
      o->data[j] = NULL;
    }
  }
  Jsi_ObjSetLength(interp, a, i);
  for (; f1 && j < m; j++) {
    o->data[j - f1] = o->data[j];
    o->data[j] = NULL;
  }
  m -= f2;
  n = n - 1 + m - (k > 0 ? 2 : 1);
  if (Jsi_ObjArraySizer(interp, o, n + 3) <= 0) {
    Jsi_LogMsg(interp, 1, "too long");
    Jsi_ValueMakeUndef(interp, ret);
    return 1;
  }
  if (k > 0) {
    for (j = m - 1; j >= j; j--) {
      o->data[k + j] = o->data[j];
      o->data[j] = NULL;
    }
    for (j = j, f2 = 2; f2 < n; j++, f2++) {
      v2 = Jsi_ValueArrayIndex(interp, args, f2);
      if (v2) {
        o->data[j] = NULL;
        Jsi_ValueDup2(interp, &o->data[j], v2);
      }
    }
  }
  Jsi_ObjSetLength(interp, o, n);
  return 0;
}