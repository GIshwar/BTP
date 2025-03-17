#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#define BLOCK_SIZE	16
#define KEY_SIZE	16

typedef unsigned char u8;
typedef unsigned int u32;

int gift128_encrypt_ecb(u8* ctext, const u8* ptext, u32 ptext_len, const u8* key);
int gift128_decrypt_ecb(u8* ptext, const u8* ctext, u32 ctext_len, const u8* key);

#endif  // ENCRYPT_H_

void encrypt(const unsigned char *plaintext, unsigned char *ciphertext, 
    const unsigned char *key, const unsigned char *nonce);

    int crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
        const unsigned char* m, unsigned long long mlen,
        const unsigned char* ad, unsigned long long adlen,
        const unsigned char* nsec, const unsigned char* npub,
        const unsigned char* k);

        int crypto_aead_decrypt(unsigned char* m, unsigned long long* mlen,
            unsigned char* nsec, const unsigned char* c,
            unsigned long long clen, const unsigned char* ad,
            unsigned long long adlen, const unsigned char* npub,
            const unsigned char *k);
////////////
