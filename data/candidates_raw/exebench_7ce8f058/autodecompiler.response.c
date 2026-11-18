void Vector_Round( void * const vector, const void * const input ) {
 ( ( vec4_t * )vector )->x = ( ( ( vec4_t * )input )->x - ( ( int )( ( vec4_t * )input )->x ) < 0.5 ? ( ( int )( ( vec4_t * )input )->x ) : ( ( int )( ( vec4_t * )input )->x + 1 ) );
 ( ( vec4_t * )vector )->y = ( ( ( vec4_t * )input )->y - ( ( int )( ( vec4_t * )input )->y ) < 0.5 ? ( ( int )( ( vec4_t * )input )->y ) : ( ( int )( ( vec4_t * )input )->y + 1 ) );
 ( ( vec4_t * )vector )->z = ( ( ( vec4_t * )input )->z - ( ( int )( ( vec4_t * )input )->z ) < 0.5 ? ( ( int )( ( vec4_t * )input )->z ) : ( ( int )( ( vec4_t * )input )->z + 1 ) );
}