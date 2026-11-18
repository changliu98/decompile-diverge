int XMLNode_remove_attribute(XMLNode* node, int i)
{
 int ret;
 struct _XMLNode* _node = (struct _XMLNode*)node;
 struct _XMLAttribute* attr;

 if (!_node || _node->init_value != 0x19770522 ||
  i < 0 || i >= _node->n_attributes) {
  ret = -1;
  goto end;
 }

 if (_node->n_attributes == 1) {
  attr = NULL;
 } else {
  attr = (struct _XMLAttribute*)malloc(sizeof(struct _XMLAttribute)*(_node->n_attributes-1));
  if (!attr) {
   ret = -1;
   goto end;
  }
 }

 if (_node->attributes[i].name) free(_node->attributes[i].name);
 if (_node->attributes[i].value) free(_node->attributes[i].value);

 if (attr) {
  memcpy(attr, _node->attributes, sizeof(struct _XMLAttribute)*i);
  memcpy(&attr[i], &_node->attributes[i+1],
   sizeof(struct _XMLAttribute)*(_node->n_attributes-i-1));
 }

 if (_node->attributes) free(_node->attributes);
 _node->attributes = attr;
 _node->n_attributes--;

 ret = _node->n_attributes;

end:
 return ret;
}