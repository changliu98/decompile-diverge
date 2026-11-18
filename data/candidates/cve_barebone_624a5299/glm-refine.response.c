Jsi_RC __cdecl jsi_ArraySpliceCmd(
        Jsi_Interp *interp,
        Jsi_Value *args,
        Jsi_Value *_this,
        Jsi_Value **ret,
        Jsi_Func *funcPtr)
{
    Jsi_Obj *obj;
    Jsi_Obj *nobj;
    Jsi_Value *start;
    Jsi_Value *howmany;
    Jsi_Value *va;
    Jsi_Number nstart;
    Jsi_Number nhow;
    int argc, curlen, ilen, istart, rhowmany, newlen, n, m, j, i, ma, ib;

    // Check if _this is an array object
    if ( *((_BYTE *)_this + 4) != 4 || !Jsi_ObjIsArray(interp, _this->d.obj) )
        return Jsi_LogMsg(interp, 1u, "expected array object");

    obj = _this->d.obj;
    start = Jsi_ValueArrayIndex(interp, args, 0);
    howmany = Jsi_ValueArrayIndex(interp, args, 1);
    argc = Jsi_ValueGetLength(interp, args);
    istart = 0;

    // Calculate the number of elements to insert
    ilen = (argc < 2) ? 0 : (argc - 2);

    n = Jsi_ObjGetLength(interp, obj);
    curlen = n;

    if ( !start )
    {
        Jsi_ValueMakeNull(interp, ret);
        return 0;
    }

    nobj = Jsi_ObjNewType(interp, JSI_OT_ARRAY);
    Jsi_ValueMakeArrayObject(interp, ret, nobj);
    Jsi_ObjSetLength(interp, nobj, 0);

    // Parse the start index
    if ( Jsi_GetNumberFromValue(interp, start, &nstart) == JSI_OK )
    {
        istart = (int)nstart;
        if ( (int)nstart > n )
            return 0;
        if ( istart < 0 )
            istart += n;
        if ( istart < 0 )
            istart = 0;
    }

    // Default to removing all elements from start to end
    rhowmany = n - istart;

    // Parse the delete count
    if ( howmany && Jsi_GetNumberFromValue(interp, howmany, &nhow) != JSI_OK )
    {
        rhowmany = (int)nhow;
        if ( (int)nhow >= n - istart )
            rhowmany = n - istart;
        if ( rhowmany < 0 )
            rhowmany = n - istart;
    }

    // Only process if we are removing 0 or more elements
    if ( rhowmany >= 0 )
    {
        if ( curlen < 0 )
            Jsi_ObjSetLength(interp, obj, 0);
        Jsi_ObjListifyArray(interp, obj);
        Jsi_ObjArraySizer(interp, nobj, rhowmany);

        // Phase 1: Extract elements to be removed into the new array
        m = 0;
        j = 0;
        for ( i = istart; m < rhowmany && m < curlen; ++i )
        {
            if ( obj->arr[i] )
            {
                nobj->arr[m] = obj->arr[i];
                obj->arr[i] = 0LL;
            }
            ++m;
            ++j;
        }
        Jsi_ObjSetLength(interp, nobj, m);

        // Phase 2: Shift remaining elements down
        while ( rhowmany && i < curlen )
        {
            obj->arr[i - rhowmany] = obj->arr[i];
            obj->arr[i++] = 0LL;
        }
        curlen -= j;

        // Calculate new length: (argc + curlen) - (argc >= 2 ? 2 : 1)
        newlen = (argc + curlen) - (argc >= 2 ? 2 : 1);

        if ( Jsi_ObjArraySizer(interp, obj, newlen + 3) <= 0 )
        {
            Jsi_LogMsg(interp, 1u, "too long");
            Jsi_ValueMakeUndef(interp, ret);
            return 1;
        }

        // Phase 3: Insert new elements if any
        if ( ilen > 0 )
        {
            // Shift elements right to make room for new items
            for ( int ia = curlen - 1; ia >= istart; --ia )
            {
                *((_QWORD *)&obj->arr[ilen] + ia) = obj->arr[ia];
                obj->arr[ia] = 0LL;
            }

            // Copy new items into the vacated positions
            ma = istart;
            for ( ib = 2; ib < argc; ++ib )
            {
                va = Jsi_ValueArrayIndex(interp, args, ib);
                if ( va )
                {
                    obj->arr[ma] = 0LL;
                    Jsi_ValueDup2(interp, &obj->arr[ma], va);
                }
                ++ma;
            }
        }
        Jsi_ObjSetLength(interp, obj, newlen);
    }

    return 0;
}