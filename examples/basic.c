#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>  // for all the PRI stuff

#include "pcg.h"

int main ()
{
	pcg32_entropy_seed ();

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("32bit global random: %" PRIu32 "\n", pcg32_random ());
	}

	printf ("\n");

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("32bit global bounded to 100: %" PRIu32 "\n", pcg32_boundedrand (100));
	}

	printf ("\n");

	pcg32_random_t local32;
	pcg32_entropy_seed_r (&local32);

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("32bit local random: %" PRIu32 "\n", pcg32_random_r (&local32));
	}

	printf ("\n");

#ifndef PCG_NO_128BIT
	pcg64_entropy_seed ();

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("64bit global random: %" PRIu64 "\n", pcg64_random ());
	}

	printf ("\n");

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("64bit global bounded to 100: %" PRIu64 "\n", pcg64_boundedrand (100));
	}

	printf ("\n");

	pcg64_random_t local64;
	pcg64_entropy_seed_r (&local64);

	for (int iter = 0; iter < 5; iter++)
	{
		printf ("64bit local random: %" PRIu64 "\n", pcg64_random_r (&local64));
	}
#endif

	return 0;
}
