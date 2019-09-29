#include <iostream>

typedef struct {
	char * buffer;
	int size;
	int len;
} StringBuilder;

void string_builder_write (TP, StringBuilder * sb, const char * s, int len)
{
	if(len < 0) len = strlen(s);
	if(sb->len + len + 1 >= sb->size) {
		sb->size = (sb->len + len + 1) + sb->len / 2;
		sb->buffer = (char*)tp_realloc(tp, sb->buffer, sb->size);
	}
	memcpy(sb->buffer + sb->len, s, len);
	sb->len += len;
	sb->buffer[sb->len] = 0;
}

/* Function: tp_str
 * String representation of an object.
 * Checks for recursive data structures
 *
 * Returns a string object representating self.
 */

tp_obj tp_str(TP, tp_obj self) {
	if (self.type.type_id == TP_STRING) {
		return self;
	}
	return tp_string_from_stdstring(tp, tp_as_string(tp, self));
}
tp_obj tp_repr(TP, tp_obj self) {
	if (self.type.type_id == TP_STRING) {
		return self;
	}
	return tp_string_from_stdstring(tp, tp_as_string(tp, self));
}


