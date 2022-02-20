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
	bool unencrypt = false;

	int opt;
	while ((opt = getopt(argc, argv, "d:i:u")) != -1)
	{
		switch (opt)
		{
			case 'd':
				dict  = fopen(optarg, "r");
				break;
			case 'i':
				input = fopen(optarg, "r");
				break;
			case 'u':
				unencrypt = true;
				break;
			case '?':
				fprintf (stderr, "Unkown option '-%c' .\n", optopt);
				return 1;
			default: 
				abort();
		}
	}

	const auto toUpper = [](const auto c) -> char {return toupper(c);}; 
	const auto put 	   = [](const auto c) -> void {putchar(c);};
	const auto cipher  = [](const auto t) -> char 
	{
		const auto inChar = std::get<0>(t);
		const auto dChar  = std::get<1>(t);

		if(!isalpha(inChar)) return inChar;
		const auto normalI = inChar - 'A';
		const auto normald = dChar  - 'A';
		const auto output  = ((inChar + dChar) % 26) + 'A';
		return output;
	};
			
	const auto inputStripped  = fileStream(input) | Map(toUpper);
	const auto streamStripped = fileStream(dict)  | Map(toUpper) | Filter(isalpha) | Loop();

	eval (inputStripped | Zip(streamStripped) | Map(cipher) | Map(put));
}


