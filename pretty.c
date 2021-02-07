#include <stdio.h>

void indent(ssize_t level, int *want, int *inhibit, int c) {
	if (!*inhibit) {
		if (*want) {
			putchar('\n');
			for (ssize_t i = 0; i < level; i++) {
				putchar('\t');
			}
		}
	}

	*want = *inhibit = 0;
	putchar(c);
}

int main(int argc, char **argv) {
	int c;
	ssize_t level = 0;
	int want = 0, inhibit = 1;

	while ((c = getchar()) != EOF) {
		if (c == '{' || c == '[') {
			indent(level++, &want, &inhibit, c);
			want = 1;
		} else if (c == '}' || c == ']') {
			want = 1;
			indent(--level, &want, &inhibit, c);
			want = 1;
		} else if (c == '"') {
			indent(level, &want, &inhibit, c);
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
			inhibit = 1;
		} else if (c == ',') {
			printf(", ");
			want = 1;
		} else if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
			want = 1;
		} else {
			indent(level, &want, &inhibit, c);
		}
	}

	putchar('\n');
}
