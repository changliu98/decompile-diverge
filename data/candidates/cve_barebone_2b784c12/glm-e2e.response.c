PyObject* conv_content_model(struct ContentModel* model, void* arg2) {
    PyObject* result = NULL;
    PyObject* tuple = NULL;
    PyObject* child_obj = NULL;
    int i;

    if (model == NULL) {
        return NULL;
    }

    tuple = PyTuple_New(model->count);
    if (tuple == NULL) {
        return NULL;
    }

    // Assert that count is less than or equal to PY_SSIZE_T_MAX
    assert(model->count <= 0x7fffffff);

    for (i = 0; i < model->count; i++) {
        child_obj = conv_content_model(&model->children[i], arg2);
        if (child_obj == NULL) {
            Py_XDECREF(tuple);
            return NULL;
        }
        PyTuple_SET_ITEM(tuple, i, child_obj);
    }

    result = Py_BuildValue("(iiNN)", model->field0, model->field4, arg2, model->field8, tuple);
    
    return result;
}