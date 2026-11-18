PyObject *__cdecl conv_content_model(XML_Content *const model, PyObject *(*conv_string)(const XML_Char *))
{
  PyObject *child; // [rsp+8h] [rbp-38h]
  signed int i; // [rsp+14h] [rbp-2Ch]
  PyObject *children; // [rsp+18h] [rbp-28h]
  PyObject *result; // [rsp+20h] [rbp-20h]

  result = 0LL;
  children = PyTuple_New(model->numchildren);
  if ( children )
  {
    if ( model->numchildren >= 0x7FFFFFFF )
      __assert_fail(
        "model->numchildren < INT_MAX",
        "/work/harness.c",
        0xA9u,
        "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(const XML_Char *))");
    for ( i = 0; i < (signed int)model->numchildren; ++i )
    {
      child = conv_content_model(&model->children[i], conv_string);
      if ( !child )
      {
        QScopedPointerPodDeleter::cleanup(children);
        return 0LL;
      }
      PyTuple_SET_ITEM(children, i, child);
    }
    return Py_BuildValue(
             "(iiO&N)",
             (unsigned int)model->type,
             (unsigned int)model->quant,
             conv_string,
             model->name,
             children);
  }
  return result;
}