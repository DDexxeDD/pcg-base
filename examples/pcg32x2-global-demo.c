/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014-2017 Melissa O'Neill <oneill@pcg-random.org>,
 *					 and the PCG Project contributors.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 *
 * Licensed under the Apache License, Version 2.0 (provided in
 * LICENSE-APACHE.txt and at http://www.apache.org/licenses/LICENSE-2.0)
 * or under the MIT license (provided in LICENSE-MIT.txt and at
 * http://opensource.org/licenses/MIT), at your option. This file may not
 * be copied, modified, or distributed except according to those terms.
 *
 * Distributed on an "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied.  See your chosen license for details.
 *
 * For additional information about the PCG random number generation scheme,
 * visit http://www.pcg-random.org/.
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "pcg.h"

int main(int argc, char** argv)
{
	/* Read command-line options */

	int rounds = 5;
	bool nondeterministic_seed = false;

	++argv;
	--argc;
	if (argc > 0 && strcmp(argv[0], "-r") == 0) {
		nondeterministic_seed = true;
		++argv;
		--argc;
	}
	if (argc > 0) {
		rounds = atoi(argv[0]);
	}

	/* You should *always* seed the RNG.  The usual time to do it is the
	   point in time when you create RNG (typically at the beginning of the
	   program). */

	if (nondeterministic_seed) {
		/* Seed with external entropy */
		pcg32x2_entropy_seed ();
	} else {
		/* Seed with a fixed constant */
		pcg32x2_srandom (42u, 42u, 54u, 54u);
	}

	printf("pcg32x2_random_r:\n"
		   "	  -  result:	  64-bit unsigned int (uint64_t)\n"
		   "	  -  period:	  2^64   (* ~2^126 streams)\n"
		   "	  -  state space: 2^128  (* ~2^126 streams)\n"
		   "	  -  state type:  pcg32x2_random_t (%zu bytes)\n"
		   "	  -  output func: XSH-RR (x 2)\n"
		   "\n",
		   sizeof(pcg32x2_random_t));

	for (int round = 1; round <= rounds; ++round) {
		printf("Round %d:\n", round);

		/* Make some RngTypebit numbers */
		printf("  64bit:");
		for (int i = 0; i < 6; ++i) {
			if (i > 0 && i % 3 == 0)
				printf("\n\t");
			printf(" 0x%016" PRIx64 "", pcg32x2_random());
		}
		printf("\n");

		printf("  Again:");
		pcg32x2_advance(-6);
		for (int i = 0; i < 6; ++i) {
			if (i > 0 && i % 3 == 0)
				printf("\n\t");
			printf(" 0x%016" PRIx64 "", pcg32x2_random());
		}
		printf("\n");

		/* Toss some coins */
		printf("  Coins: ");
		for (int i = 0; i < 65; ++i)
			printf("%c", pcg32x2_boundedrand(2) ? 'H' : 'T');
		printf("\n");

		/* Roll some dice */
		printf("  Rolls:");
		for (int i = 0; i < 33; ++i)
			printf(" %d", (int)pcg32x2_boundedrand(6) + 1);
		printf("\n");

		/* Deal some cards */
		enum { SUITS = 4, NUMBERS = 13, CARDS = 52 };
		char cards[CARDS];

		for (int i = 0; i < CARDS; ++i)
			cards[i] = i;

		for (int i = CARDS; i > 1; --i) {
			int chosen = pcg32x2_boundedrand(i);
			char card = cards[chosen];
			cards[chosen] = cards[i - 1];
			cards[i - 1] = card;
		}

		printf("  Cards:");
		static const char number[] = {'A', '2', '3', '4', '5', '6', '7',
									  '8', '9', 'T', 'J', 'Q', 'K'};
		static const char suit[] = {'h', 'c', 'd', 's'};
		for (int i = 0; i < CARDS; ++i) {
			printf(" %c%c", number[cards[i] / SUITS], suit[cards[i] % SUITS]);
			if ((i + 1) % 22 == 0)
				printf("\n\t");
		}
		printf("\n");

		printf("\n");
	}

	return 0;
}
