VALUE rb_xml_reader_attribute_hash(VALUE self) {
  VALUE hash = rb_hash_new();

  if (!has_attributes((xmlTextReaderPtr)self)) {
    return hash;
  }

  xmlNodePtr node = xmlTextReaderExpand((xmlTextReaderPtr)self);
  xmlAttrPtr property;
  for (property = node->properties; property; property = property->next) {
    VALUE rb_name = nokogiri_str_new2_stub((char*)property->name);
    VALUE rb_value = 0;
    xmlChar* c_value = xmlNodeGetContent((xmlNodePtr)property);
    if (c_value) {
      rb_value = nokogiri_str_new2_stub((char*)c_value);
      free(c_value);
    }
    rb_hash_aset(hash, rb_name, rb_value);
  }

  return hash;
}