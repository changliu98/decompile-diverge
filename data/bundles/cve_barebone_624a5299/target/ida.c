Jsi_RC __cdecl jsi_ArraySpliceCmd(
        Jsi_Interp *interp,
        Jsi_Value *args,
        Jsi_Value *_this,
        Jsi_Value **ret,
        Jsi_Func *funcPtr)
{
  int v5; // eax
  int v6; // ecx
  bool v8; // [rsp+6h] [rbp-9Ah]
  bool v9; // [rsp+7h] [rbp-99h]
  int v10; // [rsp+8h] [rbp-98h]
  signed int m; // [rsp+Ch] [rbp-94h]
  int ma; // [rsp+Ch] [rbp-94h]
  int j; // [rsp+10h] [rbp-90h]
  int i; // [rsp+14h] [rbp-8Ch]
  int ia; // [rsp+14h] [rbp-8Ch]
  int ib; // [rsp+14h] [rbp-8Ch]
  Jsi_Number nhow; // [rsp+18h] [rbp-88h] BYREF
  Jsi_Number nstart; // [rsp+20h] [rbp-80h] BYREF
  Jsi_Obj *obj; // [rsp+28h] [rbp-78h]
  Jsi_Obj *nobj; // [rsp+30h] [rbp-70h]
  Jsi_Value *howmany; // [rsp+38h] [rbp-68h]
  Jsi_Value *start; // [rsp+40h] [rbp-60h]
  Jsi_Value *va; // [rsp+48h] [rbp-58h]
  int curlen; // [rsp+54h] [rbp-4Ch]
  int ilen; // [rsp+58h] [rbp-48h]
  int rhowmany; // [rsp+5Ch] [rbp-44h]
  int n; // [rsp+60h] [rbp-40h]
  int istart; // [rsp+64h] [rbp-3Ch]
  int argc; // [rsp+68h] [rbp-38h]
  int newlen; // [rsp+6Ch] [rbp-34h]
  Jsi_Func *funcPtra; // [rsp+70h] [rbp-30h]
  Jsi_Value **reta; // [rsp+78h] [rbp-28h]
  Jsi_Value *_thisa; // [rsp+80h] [rbp-20h]
  Jsi_Value *argsa; // [rsp+88h] [rbp-18h]
  Jsi_Interp *interpa; // [rsp+90h] [rbp-10h]

  interpa = interp;
  argsa = args;
  _thisa = _this;
  reta = ret;
  funcPtra = funcPtr;
  if ( *((_BYTE *)_this + 4) == 4 && Jsi_ObjIsArray(interpa, _thisa->d.obj) )
  {
    obj = _thisa->d.obj;
    start = Jsi_ValueArrayIndex(interpa, argsa, 0);
    howmany = Jsi_ValueArrayIndex(interpa, argsa, 1);
    argc = Jsi_ValueGetLength(interpa, argsa);
    istart = 0;
    if ( argc < 2 )
      v10 = 0;
    else
      v10 = argc - 2;
    ilen = v10;
    n = Jsi_ObjGetLength(interpa, obj);
    curlen = n;
    if ( !start )
    {
      Jsi_ValueMakeNull(interpa, reta);
      return 0;
    }
    nobj = Jsi_ObjNewType(interpa, JSI_OT_ARRAY);
    Jsi_ValueMakeArrayObject(interpa, reta, nobj);
    Jsi_ObjSetLength(interpa, nobj, 0);
    if ( Jsi_GetNumberFromValue(interpa, start, &nstart) == JSI_OK )
    {
      istart = (int)nstart;
      if ( (int)nstart > n )
        return 0;
      if ( istart < 0 )
        istart += n;
      if ( istart < 0 )
        istart = 0;
    }
    rhowmany = n - istart;
    if ( !howmany || Jsi_GetNumberFromValue(interpa, howmany, &nhow) )
      goto LABEL_21;
    rhowmany = (int)nhow;
    if ( (int)nhow >= n - istart )
      rhowmany = n - istart;
    if ( rhowmany < 0 )
      rhowmany = n - istart;
    if ( rhowmany >= 0 )
    {
LABEL_21:
      if ( curlen < 0 )
        Jsi_ObjSetLength(interpa, obj, 0);
      Jsi_ObjListifyArray(interpa, obj);
      Jsi_ObjArraySizer(interpa, nobj, rhowmany);
      m = 0;
      j = 0;
      for ( i = istart; ; ++i )
      {
        v9 = 0;
        if ( m < rhowmany )
          v9 = m < curlen;
        if ( !v9 )
          break;
        if ( obj->arr[i] )
        {
          nobj->arr[m] = obj->arr[i];
          obj->arr[i] = 0LL;
        }
        ++m;
        ++j;
      }
      Jsi_ObjSetLength(interpa, nobj, m);
      while ( 1 )
      {
        v8 = 0;
        if ( rhowmany )
          v8 = i < curlen;
        if ( !v8 )
          break;
        obj->arr[i - rhowmany] = obj->arr[i];
        obj->arr[i++] = 0LL;
      }
      curlen -= j;
      v5 = argc + curlen;
      v6 = 1;
      if ( argc >= 2 )
        v6 = 2;
      newlen = v5 - v6;
      if ( Jsi_ObjArraySizer(interpa, obj, v5 - v6 + 3) <= 0 )
      {
        Jsi_LogMsg(interpa, 1u, "too long");
        Jsi_ValueMakeUndef(interpa, reta);
        return 1;
      }
      if ( ilen > 0 )
      {
        for ( ia = curlen - 1; ia >= istart; --ia )
        {
          *((_QWORD *)&obj->arr[ilen] + ia) = obj->arr[ia];
          obj->arr[ia] = 0LL;
        }
        ma = istart;
        for ( ib = 2; ib < argc; ++ib )
        {
          va = Jsi_ValueArrayIndex(interpa, argsa, ib);
          if ( va )
          {
            obj->arr[ma] = 0LL;
            Jsi_ValueDup2(interpa, &obj->arr[ma], va);
          }
          ++ma;
        }
      }
      Jsi_ObjSetLength(interpa, obj, newlen);
    }
    return 0;
  }
  return Jsi_LogMsg(interpa, 1u, "expected array object");
}