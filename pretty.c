#include <stdio.h>

void indent(ssize_t level, int *split, int *join, int c) {
	if (!*join) {
		if (*split) {
			putchar('\n');
			for (ssize_t i = 0; i < level; i++) {
				putchar('\t');
			}
		}
	}

	*split = *join = 0;
	putchar(c);
}

int main(int argc, char **argv) {
	int c;
	ssize_t level = 0;
	int split = 0, join = 1;

	while ((c = getchar()) != EOF) {
		if (c == '{' || c == '[') {
			indent(level++, &split, &join, c);
			split = 1;
		} else if (c == '}' || c == ']') {
			split = 1;
			indent(--level, &split, &join, c);
			split = 1;
		} else if (c == '"') {
			indent(level, &split, &join, c);
			while ((c = getchar()) != EOF) {
				putchar(c);
				if (c == '\\') {
					if ((c = getchar()) != EOF) {
						putchar(c);
					}
				} else if (c == '"') {
					break;
				}
			}
		} else if (c == ':') {
			printf(": ");
			join = 1;
		} else if (c == ',') {
			printf(", ");
			split = 1;
		} else if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
			split = 1;
		} else {
			indent(level, &split, &join, c);
		}
	}

	putchar('\n');
}
