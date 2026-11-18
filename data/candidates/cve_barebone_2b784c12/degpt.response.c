PyObject * convert_content_model(XML_Content *content_model, _func_PyObject_ptr_XML_Char_ptr *convert_string_func)
{
    // Check if the number of children exceeds the maximum integer value
    if (content_model->numchildren > INT_MAX) {
        __assert_fail("model->numchildren < INT_MAX", "/work/harness.c", 0xa9,
                      "PyObject *conv_content_model(XML_Content *const, PyObject *(*)(const XML_Char *))");
    }

    // Create a new tuple to hold the converted child content models
    PyObject *children_tuple = PyTuple_New((unsigned long)content_model->numchildren);
    if (!children_tuple) {
        return NULL;
    }

    // Iterate over each child content model and recursively convert it
    for (int child_index = 0; child_index < (int)content_model->numchildren; child_index++) {
        PyObject *converted_child = convert_content_model(content_model->children + child_index, convert_string_func);
        if (!converted_child) {
            // If conversion fails, decrement reference count and return NULL
            Py_XDECREF(children_tuple);
            return NULL;
        }
        // Set the item in the tuple without incrementing reference count
        PyTuple_SET_ITEM(children_tuple, child_index, converted_child);
    }

    // Build the result tuple containing type, quantifier, name, and the child tuple
    PyObject *final_result = Py_BuildValue("(iiO&N)", (unsigned long)content_model->type, (unsigned long)content_model->quant,
                                     convert_string_func, content_model->name, children_tuple);
    return final_result;
}