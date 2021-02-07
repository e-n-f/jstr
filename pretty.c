#include <stdio.h>

void indent(size_t level, int *wantnl, int c) {
	if (*wantnl) {
		putchar('\n');
		for (size_t i = 0; i < level; i++) {
			putchar('\t');
		}
		*wantnl = 0;
	}

	putchar(c);
}

int main(int argc, char **argv) {
	int c;
	size_t level = 0;
	int wantnl = 0;

	while ((c = getchar()) != EOF) {
		if (c == '{' || c == '[') {
			indent(level++, &wantnl, c);
			wantnl = 1;
		} else if (c == '}' || c == ']') {
			wantnl = 1;
			indent(--level, &wantnl, c);
			wantnl = 1;
		} else if (c == '"') {
			indent(level, &wantnl, c);
			while ((c = getchar()) != EOF) {
				if (c == '\\') {
					putchar(c);
					if ((c = getchar()) != EOF) {
						putchar(c);
					}
				} else {
					putchar(c);
					if (c == '"') {
						break;
					}
				}
			}
		} else if (c == ':') {
			printf(": ");
		} else if (c == ',') {
			printf(", ");
			wantnl = 1;
		} else if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
			indent(level, &wantnl, c);
		}
	}

	putchar('\n');
}
