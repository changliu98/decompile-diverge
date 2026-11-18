VALUE __cdecl rb_xml_reader_attribute_hash(VALUE rb_reader)
{
  xmlTextReaderPtr reader;
  xmlNodePtr node;
  xmlAttrPtr attr;
  xmlChar *c_value;
  VALUE rb_attributes;
  VALUE rb_name;
  VALUE rb_value;

  // Initialize a new Ruby hash to store the attributes
  rb_attributes = rb_hash_new();
  
  // Cast the Ruby value to the libxml2 reader pointer
  reader = (xmlTextReaderPtr)rb_reader;

  // If the current node has no attributes, return the empty hash early
  if ( !has_attributes(reader) )
    return rb_attributes;

  // Expand the reader to get the underlying xmlNode and iterate over its properties (attributes)
  node = xmlTextReaderExpand(reader);
  for ( attr = node->properties; attr; attr = attr->next )
  {
    // Create a Ruby string for the attribute name
    rb_name = nokogiri_str_new2_stub((const char *)attr->name);
    rb_value = Qnil; // Initialize value as Ruby nil (0LL)

    // Extract the string content of the attribute
    c_value = xmlNodeGetContent((xmlNodePtr)attr);
    if ( c_value )
    {
      // If content exists, convert it to a Ruby string and free the C string
      rb_value = nokogiri_str_new2_stub((const char *)c_value);
      free(c_value);
    }

    // Insert the key-value pair into the Ruby hash
    rb_hash_aset(rb_attributes, rb_name, rb_value);
  }

  return rb_attributes;
}