#ifndef __INPUT_HEADER
	#define __INPUT_HEADER
	
	/* Prototypes */
	void HandleFieldInput_Text(field_node_t  *field, char accept);
	void HandleFieldInput_Date(field_node_t *field);
	void HandleFieldInput_Numeric(field_node_t  *field, int min, int max);
	void HandleFieldInput_Float(field_node_t *field, float min, float max);
	void HandleFieldInput_Hours(field_node_t *field);

	/* See: http://en.wikipedia.org/wiki/Itoa */
	void reverse(char s[]);
	void __itoa(int n, char s[]);
#endif