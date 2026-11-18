/* WARNING: Enum "Jsi_vtype": Some values do not have unique names */
/* WARNING: Enum "Jsi_otype": Some values do not have unique names */

Jsi_RC jsi_ArraySpliceCmd(Jsi_Interp *interp,Jsi_Value *args,Jsi_Value *_this,Jsi_Value **ret,
                         Jsi_Func *funcPtr)

{
  _Bool _Var1;
  Jsi_RC JVar2;
  int iVar3;
  int local_a0;
  int m;
  int j;
  int i;
  Jsi_Number nhow;
  Jsi_Number nstart;
  Jsi_Obj *obj;
  Jsi_Obj *nobj;
  Jsi_Value *howmany;
  Jsi_Value *start;
  Jsi_Value *va;
  int curlen;
  int ilen;
  int rhowmany;
  int n;
  int istart;
  int argc;
  int newlen;
  Jsi_Func *funcPtr_local;
  Jsi_Value **ret_local;
  Jsi_Value *_this_local;
  Jsi_Value *args_local;
  Jsi_Interp *interp_local;
  
  funcPtr_local = funcPtr;
  ret_local = ret;
  _this_local = _this;
  args_local = args;
  interp_local = interp;
  if ((_this->vt != 4) || (_Var1 = Jsi_ObjIsArray(interp,(_this->d).obj), !_Var1)) {
    JVar2 = Jsi_LogMsg(interp_local,1,"expected array object");
    return JVar2;
  }
  obj = (_this_local->d).obj;
  start = Jsi_ValueArrayIndex(interp_local,args_local,0);
  howmany = Jsi_ValueArrayIndex(interp_local,args_local,1);
  argc = Jsi_ValueGetLength(interp_local,args_local);
  istart = 0;
  if (argc < 2) {
    local_a0 = 0;
  }
  else {
    local_a0 = argc + -2;
  }
  ilen = local_a0;
  curlen = Jsi_ObjGetLength(interp_local,obj);
  n = curlen;
  if (start == (Jsi_Value *)0x0) {
    Jsi_ValueMakeNull(interp_local,ret_local);
    return JSI_OK;
  }
  nobj = Jsi_ObjNewType(interp_local,JSI_OT_ARRAY);
  Jsi_ValueMakeArrayObject(interp_local,ret_local,nobj);
  Jsi_ObjSetLength(interp_local,nobj,0);
  JVar2 = Jsi_GetNumberFromValue(interp_local,start,&nstart);
  if (JVar2 == JSI_OK) {
    istart = (int)nstart;
    if (n < istart) {
      return JSI_OK;
    }
    if (istart < 0) {
      istart = n + istart;
    }
    if (istart < 0) {
      istart = 0;
    }
  }
  rhowmany = n - istart;
  if ((howmany != (Jsi_Value *)0x0) &&
     (JVar2 = Jsi_GetNumberFromValue(interp_local,howmany,&nhow), JVar2 == JSI_OK)) {
    rhowmany = (int)nhow;
    if (n - istart <= rhowmany) {
      rhowmany = n - istart;
    }
    if (rhowmany < 0) {
      rhowmany = n - istart;
    }
    if (rhowmany < 0) {
      return JSI_OK;
    }
  }
  if (curlen < 0) {
    Jsi_ObjSetLength(interp_local,obj,0);
  }
  Jsi_ObjListifyArray(interp_local,obj);
  Jsi_ObjArraySizer(interp_local,nobj,rhowmany);
  j = 0;
  i = istart;
  for (m = 0; m < rhowmany && m < curlen; m = m + 1) {
    if (obj->arr[i] != (Jsi_Value *)0x0) {
      nobj->arr[m] = obj->arr[i];
      obj->arr[i] = (Jsi_Value *)0x0;
    }
    i = i + 1;
    j = j + 1;
  }
  Jsi_ObjSetLength(interp_local,nobj,m);
  for (; rhowmany != 0 && i < curlen; i = i + 1) {
    obj->arr[i - rhowmany] = obj->arr[i];
    obj->arr[i] = (Jsi_Value *)0x0;
  }
  curlen = curlen - j;
  iVar3 = 1;
  if (1 < argc) {
    iVar3 = 2;
  }
  newlen = (curlen + argc) - iVar3;
  iVar3 = Jsi_ObjArraySizer(interp_local,obj,newlen + 3);
  if (0 < iVar3) {
    i = curlen;
    if (0 < ilen) {
      while (i = i + -1, istart <= i) {
        obj->arr[i + ilen] = obj->arr[i];
        obj->arr[i] = (Jsi_Value *)0x0;
      }
      m = istart;
      for (i = 2; i < argc; i = i + 1) {
        va = Jsi_ValueArrayIndex(interp_local,args_local,i);
        if (va != (Jsi_Value *)0x0) {
          obj->arr[m] = (Jsi_Value *)0x0;
          Jsi_ValueDup2(interp_local,obj->arr + m,va);
        }
        m = m + 1;
      }
    }
    Jsi_ObjSetLength(interp_local,obj,newlen);
    return JSI_OK;
  }
  Jsi_LogMsg(interp_local,1,"too long");
  Jsi_ValueMakeUndef(interp_local,ret_local);
  return JSI_ERROR;
}