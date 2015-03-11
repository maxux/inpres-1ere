#ifndef __INPUT_HEADER
	#define __INPUT_HEADER
	
	/* Prototypes */
	char HandleFieldInput_Text(field_node_t  *field, char accept);
	char HandleFieldInput_Date(field_node_t *field);
	char HandleFieldInput_Numeric(field_node_t  *field, int min, int max);
	char HandleFieldInput_Float(field_node_t *field, float min, float max);
	char HandleFieldInput_Hours(field_node_t *field);

	/* See: http://en.wikipedia.org/wiki/Itoa */
	void reverse(char s[]);
	void __itoa(int n, char s[]);
#endif