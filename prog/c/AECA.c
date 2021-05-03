// AECA.c - Audible Elementary Cellular Automata

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "AECA.schar"

int main(void) {
	unsigned seed, rule, gen_len, gen_cnt;

	printf("Seed: ");
	scanf("%u", &seed);

	printf("Rule: ");
	scanf("%u", &rule);

	printf("Generation length: ");
	scanf("%u", &gen_len);

	printf("Generation count: ");
	scanf("%u", &gen_cnt);

	unsigned samples = gen_cnt * gen_len;

	_Bool cells[gen_len];
	_Bool clone[gen_len];

	if (seed) {
		srand(seed);

		for (unsigned c = 0; c < gen_len; ++c)
			cells[c] = rand() & 1;
	} else {
		memset(cells, 0, sizeof cells);
		cells[gen_len / 2] = 1;
	}

	signed char* audio = malloc(samples);

	for (unsigned g = 0; g < gen_cnt; ++g) {
		for (unsigned c = 0; c < gen_len; ++c) {
			audio[g * gen_len + c] = cells[c] ? SCHAR_MAX : SCHAR_MIN;

			_Bool p = cells[c ? c - 1 : gen_len - 1];
			_Bool q = cells[c];
			_Bool r = cells[(c + 1) % gen_len];

			clone[c] = rule >> (p << 2 | q << 1 | r) & 1;
		}

		memcpy(cells, clone, sizeof clone);
	}

	FILE* stream = fopen(FILENAME, "wb");

	fwrite(audio, 1, samples, stream);

	fclose(stream);

	free(audio);

	system("aplay -q -t raw -f S8 -r 44100 " FILENAME);
}
