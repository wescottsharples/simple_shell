#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int i, j, k, n, m = 0;
	char *buf, *path, *token, *pathcpy;
	struct stat *bufstat = NULL;

	if (argc < 2)
		exit(98);
	path = getenv("PATH");
	bufstat = malloc(sizeof(struct stat));
	if (bufstat == NULL)
		return (1);
	for (k = 1; k < argc; k++)
	{
		for (i = 0; path[i]; i++)
			;
		pathcpy = malloc(sizeof(char) * (i + 1));
		if (pathcpy == NULL)
			return (1);
		for (i = 0; path[i]; i++)
			pathcpy[i] = path[i];
		pathcpy[i] = '\0';
		token = strtok(pathcpy, ":");
		while (token)
		{
			m = 0;
			for (i = 0; argv[k][i]; i++)
				;
			for (j = 0; token[j]; j++)
				;
			buf = malloc(sizeof(char) * (i + j + 4));
			if (buf == NULL)
				return (1);
			for (n = 0; n < j; n++)
				buf[n] = token[n];
			buf[n++] = '/';
			for (; n < (i + j + 2); n++)
				buf[n] = argv[k][m++];
			buf[n] = '\n';
			n++;
			buf[n] = '\0';
			if (stat(buf, bufstat) == 0)
			{
				write(1, buf, (i + j + 3));
				break;
			}
			token = strtok(NULL, ":");
			free(buf);
		}
		free(pathcpy);
		free(buf);
	}
	free(bufstat);
	return (0);
}
