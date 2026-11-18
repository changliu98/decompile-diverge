static PyObject *
conv_content_model(XML_Content *const model, PyObject *(*conv)(XML_Content *const))
{
 PyObject *ret = NULL;
 PyObject *children;
 int i;

 children = PyTuple_New(model->numchildren);
 if (children == NULL)
  goto done;

 do { if (!(model->numchildren < ((int)((unsigned long)-1 >> 1)))) ___assert_fail("model->numchildren < INT_MAX", "harness.c", 169, "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(content_model *))"); } while (0);;
 for (i = 0;; ++i) {
  PyObject *child;

  if (i >= model->numchildren)
   break;

  child = conv(&model->children[i]);
  if (child == NULL) {
   __ZN24QScopedPointerPodDeleter7cleanupEPv(children);
   ret = NULL;
   goto done;
  }

  PyTuple_SET_ITEM(children, i, child);
 }

 ret = Py_BuildValue("(iiO&N)", model->type, model->quant, conv_string, model->str, children);

done:
 return ret;
}