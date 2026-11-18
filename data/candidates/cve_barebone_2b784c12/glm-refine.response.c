PyObject *__cdecl conv_content_model(XML_Content *const model, PyObject *(*conv_string)(const XML_Char *))
{
  PyObject *children;
  int i;

  // Allocate a tuple to hold the child models
  children = PyTuple_New(model->numchildren);
  if (children == NULL)
    return NULL;

  // Assert that the number of children does not exceed INT_MAX
  if (model->numchildren >= 0x7FFFFFFF)
    __assert_fail(
        "model->numchildren < INT_MAX",
        "/work/harness.c",
        0xA9u,
        "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(const XML_Char *))");

  // Recursively convert each child model and append it to the tuple
  for (i = 0; i < (int)model->numchildren; ++i)
  {
    PyObject *child = conv_content_model(&model->children[i], conv_string);
    if (child == NULL)
    {
      // Clean up the partially constructed tuple on failure
      Py_XDECREF(children);
      return NULL;
    }
    PyTuple_SET_ITEM(children, i, child);
  }

  // Build and return the final Python tuple representing the content model
  // Format "(iiO&N)":
  //   i = model->type (integer)
  //   i = model->quant (integer)
  //   O& = model->name (converted via conv_string function pointer)
  //   N = children (steals reference to the tuple)
  return Py_BuildValue(
      "(iiO&N)",
      (unsigned int)model->type,
      (unsigned int)model->quant,
      conv_string,
      model->name,
      children);
}