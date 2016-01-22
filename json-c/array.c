#include <json-c/json.h>

int json_array_len(json_object *input)
{
	json_object *root;
	enum json_type type;
	int len = -1;

	root = json_tokener_parse(input);
	if (root) {
		type = json_object_get_type(root);
		if (type == json_type_array)
			len = json_object_array_length(root);
		json_object_put(root);
	}

	return len;
}
