static int Array_ReplaceCmd(Jsi_Interp *interp, Jsi_Value *args,
    Jsi_Value *_this, Jsi_Value **ret, Jsi_Func *funcPtr)
{
    int rc;
    double dlen, dstart, dhowmany;
    int start, howmany, curlen, newlen, ilen, nlen, i, j, k, m, n;
    int nstart, rhowmany, nhow;
    Jsi_Obj *arrPtr, *narrPtr, *val;
    Jsi_Value *vstart, *vhowmany, *vval;

    if (!((((_this)->type) == 4) && ((Jsi_ObjIsArray(interp, (_this)->obj))&1))) {
        rc = Jsi_LogMsg(interp, 1, "expected array object");
        goto return_rc;
    }
    arrPtr = _this->obj;
    vstart = Jsi_ValueArrayIndex(interp, args, 0);
    vhowmany = Jsi_ValueArrayIndex(interp, args, 1);
    nlen = Jsi_ValueGetLength(interp, args);
    if (nlen >= 3)
        ilen = nlen - 2;
    else
        ilen = 0;
    curlen = n = Jsi_ObjGetLength(interp, arrPtr);
    if (!vstart)
        goto bail2;
    narrPtr = Jsi_ObjNewType(interp, 5);
    Jsi_ValueMakeArrayObject(interp, ret, narrPtr);
    Jsi_ObjSetLength(interp, narrPtr, 0);
    if (Jsi_GetNumberFromValue(interp, vstart, &dstart) == 0) {
        start = (int)dstart;
        if (start > n)
            goto bail;
        if (start < 0)
            start += n;
        if (start < 0)
            start = 0;
    } else {
        rhowmany = n - start;
        if (vhowmany && Jsi_GetNumberFromValue(interp, vhowmany, &dhowmany) == 0) {
            howmany = (int)dhowmany;
            if (howmany >= n - start)
                howmany = n - start;
            if (howmany < 0)
                howmany = n - start;
            if (howmany < 0)
                goto bail;
        } else {
            if (curlen < 0)
                Jsi_ObjSetLength(interp, arrPtr, 0);
            Jsi_ObjListifyArray(interp, arrPtr);
            Jsi_ObjArraySizer(interp, narrPtr, howmany);
            for (m = 0, j = 0, i = start;; i++, j++) {
                if ((m < howmany) && (i < curlen)) {
                    if (arrPtr->value.arr[i]) {
                        narrPtr->value.arr[m] = arrPtr->value.arr[i];
                        arrPtr->value.arr[i] = NULL;
                    }
                    m++;
                } else {
                    Jsi_ObjSetLength(interp, narrPtr, m);
                    break;
                }
            }
            for (; (howmany) && (i < curlen); i++) {
                arrPtr->value.arr[i - howmany] = arrPtr->value.arr[i];
                arrPtr->value.arr[i] = NULL;
            }
            curlen -= j;
            newlen = curlen + nlen - (nlen < 2 ? 1 : 2);
            if (Jsi_ObjArraySizer(interp, arrPtr, newlen + 3) <= 0) {
                Jsi_LogMsg(interp, 1, "too long");
                Jsi_ValueMakeUndef(interp, ret);
                rc = 1;
                goto return_rc;
            }
            if (ilen > 0) {
                for (i = curlen - 1; i >= start; i--) {
                    arrPtr->value.arr[i + ilen] = arrPtr->value.arr[i];
                    arrPtr->value.arr[i] = NULL;
                }
                m = start;
                for (i = 2; i < nlen; i++) {
                    vval = Jsi_ValueArrayIndex(interp, args, i);
                    if (vval) {
                        arrPtr->value.arr[m] = NULL;
                        Jsi_ValueDup2(interp, &arrPtr->value.arr[m], vval);
                    }
                    m++;
                }
            } else {
                Jsi_ObjSetLength(interp, arrPtr, newlen);
            }
            rc = 0;
            goto return_rc;
        }
    }
    bail:
    rc = 0;
    goto return_rc;
    bail2:
    Jsi_ValueMakeNull(interp, ret);
    rc = 0;
    goto return_rc;
return_rc:
    return rc;
}