define JSI_OBJECT_ARRAY 4

int jsi_ArraySpliceCmd(Jsi_Interp *interp, Jsi_Value *args, Jsi_Value *ret_value, void *cmd, void *data) {
    Jsi_Obj *obj;
    Jsi_Value *start_val;
    Jsi_Value *deleteCount_val;
    int argc;
    int insert_count;
    int start = 0;
    int delete_count;
    int arr_len;
    int orig_arr_len;
    int new_len;
    int i, j, k;
    double dval;
    Jsi_Obj *new_obj;
    int actual_deleted = 0;

    if (args->type != JSI_OBJECT_ARRAY || !Jsi_ObjIsArray(interp, args->d.obj)) {
        Jsi_LogMsg(interp, 1, "expected array");
        return interp->error;
    }

    obj = args->d.obj;
    start_val = Jsi_ValueArrayIndex(interp, args, 0);
    deleteCount_val = Jsi_ValueArrayIndex(interp, args, 1);
    argc = Jsi_ValueGetLength(interp, args);
    
    insert_count = (argc >= 2) ? (argc - 2) : 0;
    arr_len = Jsi_ObjGetLength(interp, obj);
    orig_arr_len = arr_len;

    if (start_val == NULL) {
        Jsi_ValueMakeNull(interp, ret_value);
        return 0;
    }

    new_obj = Jsi_ObjNewType(interp, 5);
    Jsi_ValueMakeArrayObject(interp, ret_value, new_obj);
    Jsi_ObjSetLength(interp, new_obj, 0);

    if (Jsi_GetNumberFromValue(interp, start_val, &dval) == 0) {
        start = (int)dval;
        if (start > arr_len) {
            goto cleanup;
        }
        if (start < 0) {
            start += arr_len;
        }
        if (start < 0) {
            start = 0;
        }
    }

    delete_count = arr_len - start;
    if (deleteCount_val != NULL && Jsi_GetNumberFromValue(interp, deleteCount_val, &dval) == 0) {
        delete_count = (int)dval;
        if (delete_count > arr_len - start) {
            delete_count = arr_len - start;
        }
        if (delete_count < 0) {
            delete_count = arr_len - start;
        }
        if (delete_count < 0) {
            goto cleanup;
        }
    }

    if (orig_arr_len < 0) {
        Jsi_ObjSetLength(interp, obj, 0);
    }
    Jsi_ObjListifyArray(interp, obj);
    Jsi_ObjArraySizer(interp, new_obj, delete_count);

    i = 0;
    j = 0;
    k = start;
    while (i < delete_count && k < orig_arr_len) {
        if (obj->arr[k] != NULL) {
            new_obj->arr[i] = obj->arr[k];
            obj->arr[k] = NULL;
        }
        i++;
        k++;
        j++;
    }
    Jsi_ObjSetLength(interp, new_obj, i);

    k = start;
    while (delete_count != 0 && k < orig_arr_len) {
        obj->arr[k - delete_count] = obj->arr[k];
        obj->arr[k] = NULL;
        k++;
    }

    arr_len = orig_arr_len - j;
    new_len = arr_len + argc;
    if (argc >= 2) {
        new_len -= 2;
    } else {
        new_len -= 1;
    }

    if (Jsi_ObjArraySizer(interp, obj, new_len + 3) <= 0) {
        Jsi_LogMsg(interp, 1, "out of memory");
        Jsi_ValueMakeUndef(interp, ret_value);
        return 1;
    }

    if (insert_count > 0) {
        for (k = arr_len - 1; k >= start; k--) {
            obj->arr[k + insert_count] = obj->arr[k];
            obj->arr[k] = NULL;
        }

        k = start;
        for (i = 2; i < argc; i++) {
            Jsi_Value *val = Jsi_ValueArrayIndex(interp, args, i);
            if (val != NULL) {
                obj->arr[k] = NULL;
                Jsi_ValueDup2(interp, &obj->arr[k], val);
            }
            k++;
        }
    }

    Jsi_ObjSetLength(interp, obj, new_len);

cleanup:
    return 0;
}