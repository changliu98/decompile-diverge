void reset_request(struct Request *req) {
    if (req != NULL) {
        req->field_0 = 0;
        req->field_8 = 0;
        req->field_4 = 0;
        
        if (req->field_10 != NULL) {
            free(req->field_10);
        }
        req->field_10 = NULL;
        
        req->field_24 = 0;
        req->field_28 = 0;
        req->field_2c = 0;
    }
}