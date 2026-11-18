Jsi_RC
jsi_ArraySpliceCmd(Jsi_Interp *interp, Jsi_Value *args, Jsi_Value *_this, Jsi_Value **ret, Jsi_Func *funcPtr)
{
    Jsi_Obj *obj, *nobj;
    Jsi_Value *start, *howmany, *va;
    Jsi_Number nstart, nhow;
    int istart, rhowmany, ilen, curlen, newlen, n, i, j, m, argc;

    if (_this->vt != 4 || !Jsi_ObjIsArray(interp, _this->d.obj))
        return Jsi_LogMsg(interp, 1, "expected array object");
    obj = _this->d.obj;

    start = Jsi_ValueArrayIndex(interp, args, 0);
    howmany = Jsi_ValueArrayIndex(interp, args, 1);
    argc = Jsi_ValueGetLength(interp, args);
    ilen = argc > 1 ? argc - 2 : 0;
    curlen = Jsi_ObjGetLength(interp, obj);
    n = curlen;

    if (!start) {
        Jsi_ValueMakeNull(interp, ret);
        return JSI_OK;
    }

    nobj = Jsi_ObjNewType(interp, JSI_OT_ARRAY);
    Jsi_ValueMakeArrayObject(interp, ret, nobj);
    Jsi_ObjSetLength(interp, nobj, 0);

    if (Jsi_GetNumberFromValue(interp, start, &nstart) == JSI_OK) {
        istart = (int)nstart;
        if (istart > n)
            return JSI_OK;
        if (istart < 0)
            istart = n + istart;
        if (istart < 0)
            istart = 0;
    }

    rhowmany = n - istart;
    if (howmany && Jsi_GetNumberFromValue(interp, howmany, &nhow) == JSI_OK) {
        rhowmany = (int)nhow;
        if (rhowmany > n - istart)
            rhowmany = n - istart;
        if (rhowmany < 0)
            rhowmany = n - istart;
        if (rhowmany < 0)
            return JSI_OK;
    }

    if (curlen < 0)
        Jsi_ObjSetLength(interp, obj, 0);

    Jsi_ObjListifyArray(interp, obj);

    Jsi_ObjArraySizer(interp, nobj, rhowmany);
    for (i = istart, j = 0, m = 0; m < rhowmany && m < curlen; m++) {
        if (obj->arr[i]) {
            nobj->arr[m] = obj->arr[i];
            obj->arr[i] = 0;
        }
        i++;
        j++;
    }
    Jsi_ObjSetLength(interp, nobj, m);

    for (; rhowmany && i < curlen; i++) {
        obj->arr[i - rhowmany] = obj->arr[i];
        obj->arr[i] = 0;
    }
    curlen -= j;
    newlen = curlen + argc - (argc > 1 ? 2 : 1);

    if (Jsi_ObjArraySizer(interp, obj, newlen + 3) < 1) {
        Jsi_LogMsg(interp, 1, "too long");
        Jsi_ValueMakeUndef(interp, ret);
        return JSI_ERROR;
    }

    if (ilen > 0) {
        for (i = curlen - 1; i >= istart; i--) {
            obj->arr[i + ilen] = obj->arr[i];
            obj->arr[i] = 0;
        }
        for (i = 2, m = istart; i < argc; i++) {
            va = Jsi_ValueArrayIndex(interp, args, i);
            if (va) {
                obj->arr[m] = 0;
                Jsi_ValueDup2(interp, &obj->arr[m], va);
            }
            m++;
        }
    }

    Jsi_ObjSetLength(interp, obj, newlen);
    return JSI_OK;
}