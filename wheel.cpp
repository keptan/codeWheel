#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "fun/tree.h"
#include "fun/list.h"
#include "fun/range.h"


auto main (int argc, char** argv) -> int
{
	FILE *dict  = nullptr;
	FILE *input = nullptr;

	int opt;
	while ((opt = getopt(argc, argv, "d:i:")) != -1)
	{
		switch (opt)
		{
			case 'd':
				dict  = fopen(optarg, "r");
				break;
			case 'i':
				input = fopen(optarg, "r");
				break;
			case '?':
				fprintf (stderr, "Unkown option '-%c' .\n", optopt);
				return 1;
			default: 
				abort();
		}
	}

	const auto put = [](const auto c) -> void {putchar(c);};
	eval(fileStream(input) | Take(10) | Map(put));
}


