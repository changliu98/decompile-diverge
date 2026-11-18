PyObject * conv_content_model(XML_Content *model,_func_PyObject_ptr_XML_Char_ptr *conv_string)

{
  PyObject *tup;
  PyObject *v;
  PyObject *child;
  int i;
  PyObject *children;
  PyObject *result;
  _func_PyObject_ptr_XML_Char_ptr *conv_string_local;
  XML_Content *model_local;
  
  result = (PyObject *)0x0;
  tup = PyTuple_New((ulong)model->numchildren);
  if (tup != (PyObject *)0x0) {
    if (0x7ffffffe < model->numchildren) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("model->numchildren < INT_MAX","/work/harness.c",0xa9,
                    "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(const XML_Char *))"
                   );
    }
    for (i = 0; i < (int)model->numchildren; i = i + 1) {
      v = conv_content_model(model->children + i,conv_string);
      if (v == (PyObject *)0x0) {
        Py_XDECREF(tup);
        return (PyObject *)0x0;
      }
      PyTuple_SET_ITEM(tup,i,v);
    }
    result = Py_BuildValue("(iiO&N)",(ulong)model->type,(ulong)model->quant,conv_string,model->name,
                           tup);
  }
  return result;
}