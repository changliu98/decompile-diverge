struct _PyObject *conv_content_model(struct _XML_Content *model, struct _PyObject *(*conv_string)(char *))
{
  struct _PyObject *result = ((void *)0);
  struct _PyObject *children = ((void *)0);
  struct _PyObject *child = ((void *)0);
  int i = 0;
  children = PyTuple_New(model->numchildren);
  if (children == ((void *)0))
    return result;
  ((void) sizeof ((model->numchildren < 2147483647) ? 1 : 0), __extension__ ({ if (model->numchildren < 2147483647) ; else __assert_fail ("model->numchildren < INT_MAX", "/work/harness.c", 169, __extension__ __PRETTY_FUNCTION__); }));
  for (i = 0; i < model->numchildren; i++)
  {
    child = conv_content_model(&model->children[i], conv_string);
    if (child == ((void *)0))
    {
      do { if (children != ((void *)0)) { QScopedPointerPodDeleter::call(children); children = ((void *)0); } } while (0);
      return ((void *)0);
    }
    PyTuple_SET_ITEM(children, i, child);
  }
  return Py_BuildValue("(?iiO&N)",
    model->type == eCONTENT_MODEL_IN_LIST ? "O" : "o",
    model->type,
    model->quant,
    conv_string,
    model->name,
    children);
}