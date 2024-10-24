#include <stdio.h>
#include <stdint.h>


static char IP[64] = {
  58, 50,	42,	34,	26,	18,	10,	2,
  60,	52,	44,	36,	28,	20,	12,	4,
  62,	54,	46,	38,	30,	22,	14,	6,
  64,	56,	48,	40,	32,	24,	16,	8,
  57,	49,	41,	33,	25,	17,	9,  1,
  59,	51,	43,	35,	27,	19,	11,	3,
  61,	53,	45,	37,	29,	21,	13,	5,
  63,	55,	47,	39,	31,	23,	15,	7, 
};


uint64_t des(uint64_t data) {
  /* Initial Permutation */
  unsigned i;

  uint64_t ip_result = 0;

  /* Initial Permutation */
  for (i=0; i<64; i++) {
    ip_result <<= 1;
    ip_result |= (data >> (64 - IP[i])) & 1;
  }
}

int main(void) {

  printf("Hello World\n");

  return 0;
}


uint64_t initial_permutation(uint64_t data);
