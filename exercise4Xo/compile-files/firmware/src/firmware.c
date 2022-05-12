#include "print.h"
#include "Xoodyak.h"
#include <stddef.h>

#define MESSAGE_LENGTH 3
#define XOODYAK_DIGEST_SIZE 32

void main(void){

    struct cyclist cy;
    //unsigned char message[MESSAGE_LENGTH] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21\x22\x23\x24\x25\x26\x27";
    unsigned char message[MESSAGE_LENGTH] = "\x00\x01\x02";
    unsigned char digest[XOODYAK_DIGEST_SIZE];

    // HASHING
    /* create a cyclist */
    cyclist_initialise_hash(&cy);

    /* absorb the message*/
    cyclist_absorb(&cy, message, MESSAGE_LENGTH);

    /* squeeze out the digest */
    cyclist_squeeze(&cy, digest, XOODYAK_DIGEST_SIZE, 0x40);

    // print_str("MSG =");
    // for (int i = 0; i < MESSAGE_LENGTH; i++){
    //     print_hex(message[i], 2);
    // }

    // print_str(" MD =");
    // for (int i = 0; i < XOODYAK_DIGEST_SIZE; i++){
    //     print_hex(digest[i], 2);
    // }

}

/**
 * @brief added own memcpy because of compiler warning
 * 
 */
void *memcpy(void *dest, const void *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}