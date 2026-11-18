define GF_SG_VRML_SF_TYPE_4 4

void gf_dump_vrml_simple_field(GF_DumpContext *ctx, GF_FieldInfo *field, void *cbck) {
    GF_FieldInfo *info = field;
    int field_type = info->field_type;
    
    if (field_type == GF_SG_VRML_FIELD_SFNODE) {
        GF_Node **node_ptr = (GF_Node **)info->field_ptr;
        assert(node_ptr != NULL && *node_ptr != NULL);
        gf_dump_vrml_node(ctx, *node_ptr, 0, 0);
        
    } else if (field_type == GF_SG_VRML_FIELD_MFNODE_ALT) {
        GF_Node *node = *(GF_Node **)info->field_ptr;
        assert(node != NULL);
        
        ctx->indent_level++;
        while (node != NULL) {
            gf_dump_vrml_node(ctx, *(GF_Node **)((char *)node + 8), 1, 0);
            node = *(GF_Node **)node;
        }
        ctx->indent_level--;
        
    } else if (field_type != GF_SG_VRML_FIELD_MFNODE) {
        if (gf_sg_vrml_is_sf_field(info->field_type)) {
            if (ctx->is_xml_mode) {
                StartAttribute(ctx, "");
            }
            gf_dump_vrml_sffield(ctx, info->field_type, info->field_ptr, 0, cbck);
            if (ctx->is_xml_mode) {
                EndAttribute(ctx);
            }
        } else {
            void *field_ptr = info->field_ptr;
            int sf_type = gf_sg_vrml_get_sf_type(info->field_type);
            
            if (!ctx->is_xml_mode) {
                gf_fprintf(ctx->file, "[");
            } else if (sf_type == GF_SG_VRML_SF_TYPE_4) {
                gf_fprintf(ctx->file, "\"");
            } else {
                StartAttribute(ctx, "");
            }
            
            for (int i = 0; i < *(int *)field_ptr; i++) {
                if (i != 0) {
                    gf_fprintf(ctx->file, " ");
                }
                void *item;
                gf_sg_vrml_mf_get_item(info->field_ptr, info->field_type, &item, i);
                gf_dump_vrml_sffield(ctx, sf_type, item, 1, cbck);
            }
            
            if (!ctx->is_xml_mode) {
                gf_fprintf(ctx->file, "]");
            } else if (sf_type == GF_SG_VRML_SF_TYPE_4) {
                gf_fprintf(ctx->file, "\"");
            } else {
                EndAttribute(ctx);
            }
        }
    }
}