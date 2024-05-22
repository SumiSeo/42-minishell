#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void parseQuotedStrings(const char *input, char **output, int *count) {
	const char *ptr = input;
	bool inQuotes = false;
	bool escape = false;
	char buffer[BUFFER_SIZE];
	int bufIndex = 0;
	*count = 0;

	while (*ptr != '\0')
	{
		if (escape)
		{
			printf("[1]\n");
			buffer[bufIndex++] = *ptr;
			escape = false;
		}
		else if (*ptr == '\\')
		{
			printf("[2]\n");
			escape = true;
		}
		else if (*ptr == '"')
		{
			printf("[3]\n");
			if (inQuotes) {
				// End of quoted string
				buffer[bufIndex] = '\0';
				output[*count] = (char *)malloc(bufIndex + 1);
				strcpy(output[*count], buffer);
				(*count)++;
				bufIndex = 0;
			}
			inQuotes = !inQuotes;
		}
		else if (inQuotes)
		{
			printf("[4]\n");
			buffer[bufIndex++] = *ptr;
		}
		printf("5");
		ptr++;
	}
}

int main() {
    const char *input = "This is a \"quoted string\" and here is \"another one\".";
    char *output[10]; // Assuming there will be no more than 10 quoted strings
    int count = 0;

    parseQuotedStrings(input, output, &count);
	printf("\n");
    for (int i = 0; i < count; i++) {
        printf("Quoted string %d: %s\n", i + 1, output[i]);
        free(output[i]);
    }

    return 0;
}