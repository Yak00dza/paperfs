#include "fprint.h"
#include "encode.h"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		help_message();
		return 0;
	}	

	char *input_file_name = argv[1];	
	char *output_file_name = argv[2];	

	FILE *input_file = fopen(input_file_name, "rb");

	if (input_file == NULL)
	{
		err_file_not_exists(input_file_name);	
		return -1;
	} 

	FILE* output = file_to_image(input_file, output_file_name);
	
	if (!output) {
		printf("Could not save convert %s to images: file too big.\nSpliting files into pages is not yet supported.\n", input_file_name);
		return -1;
	}

	fclose(output);

	return 0;
}

void help_message()
{
	printf("Usage: fprint [file] [output]\n");	
}

void err_file_not_exists(char* name)
{
	printf("Error: file %s does not exist!\n", name);
}

