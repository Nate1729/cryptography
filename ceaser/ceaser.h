#ifndef CEASER_H
#define CEASER_H

/* Apply ceaser cipher to character
 * by key `k`.
 */
char encrypt(unsigned k, char plain_char);

/* Reverse ceaser cipher to character
 * by key `k`
 */
char decrypt(unsigned k, char cipher_char);


#endif /* CEASER_H */
