static VALUE noko_xml_reader_get_attributes(VALUE self)
{
  VALUE attributes = rb_hash_new();
  xmlTextReaderPtr reader;
  xmlNodePtr node;
  xmlNsPtr ns;
  VALUE rb_ns;

  reader = (xmlTextReaderPtr)DATA_PTR(self);

  if (!has_attributes(reader)) {
    return attributes;
  }

  node = xmlTextReaderExpand(reader);
  ns = node->properties;

  while (ns != NULL) {
    VALUE name = nokogiri_str_new2_stub((char*)ns->name);
    VALUE value = ((void*)0);
    char *val = (char*)xmlNodeGetContent((xmlNodePtr)ns);
    if (val != NULL) {
      value = nokogiri_str_new2_stub(val);
      free(val);
    }
    rb_hash_aset(attributes, name, value);
    ns = ns->next;
  }

  return attributes;
}