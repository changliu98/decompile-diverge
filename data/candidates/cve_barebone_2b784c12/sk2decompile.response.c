static PyObject *conv_content_model(content_model_t *const model,
                                    PyObject *(*conv_type)(const type_t *)) {
  PyObject *sub_model = NULL;
  PyObject *sub_models = PyTuple_New(model->sub_model_count);
  if (sub_models == NULL) {
    return NULL;
  }
  assert(model->sub_model_count < PY_SSIZE_T_MAX);
  for (int i = 0; i < model->sub_model_count; ++i) {
    sub_model = conv_content_model(&model->sub_models[i], conv_type);
    if (sub_model == NULL) {
      Py_DECREF(sub_models);
      return NULL;
    }
    PyTuple_SET_ITEM(sub_models, i, sub_model);
  }
  return Py_BuildValue("(iiO&N)", model->min, model->max, conv_type,
                       model->type, sub_models);
}