PyObject *
conv_content_model(XML_Content *model, PyObject *(*conv_string)(const XML_Char *))
{
    PyObject *result = NULL;
    PyObject *tup;
    int i;

    tup = PyTuple_New(model->numchildren);
    if (tup == NULL)
      return NULL;

    ((model->numchildren < INT_MAX) ? (void)0 : __assert_fail("model->numchildren < INT_MAX", "/work/harness.c", 169, "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(const XML_Char *))"));
    for (i = 0; i < (int)model->numchildren; i++) {
 PyObject *child;

 child = conv_content_model(&model->children[i], conv_string);
 if (child == NULL) {
     Py_XDECREF(tup);
     return NULL;
 }
 PyTuple_SET_ITEM(tup, i, child);
    }

    result = Py_BuildValue("(iiO&N)",
      model->type,
      model->quant,
      conv_string, model->name,
      tup);
    return result;
}