#include <stdio.h>
#include <string.h>
#include "encrypt.h"  // Ensure this is correctly included

void print_bytes(const char *label, const unsigned char *data, unsigned long long length) {
    printf("%s: ", label);
    for (unsigned long long i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    // Example 128-bit key
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

    // Example plaintext message
    unsigned char plaintext[16] = "Hello GIFT-COFB";  // 16-byte message
    unsigned long long plaintext_len = strlen((char*)plaintext);

    // Example nonce (96-bit)
    unsigned char nonce[12] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11,
                            0x22, 0x33, 0x44, 0x55};

    // Example associated data (for authentication)
    unsigned char ad[16] = "AUTHENTICATED";  // 16-byte
    unsigned long long ad_len = strlen((char*)ad);

    // Buffers for encryption
    unsigned char ciphertext[32];
    unsigned long long ciphertext_len;

    printf("\n🔐 **Encryption Process** 🔐\n");
    print_bytes("Key", key, 16);
    print_bytes("Nonce", nonce, 12);
    print_bytes("Plaintext", plaintext, plaintext_len);
    printf("Plaintext (String): %s\n", plaintext);
    print_bytes("Associated Data", ad, ad_len);

    // 🔒 Perform Encryption
    crypto_aead_encrypt(ciphertext, &ciphertext_len, plaintext, plaintext_len, 
                        ad, ad_len, NULL, nonce, key);

    // Print Ciphertext
    print_bytes("Ciphertext", ciphertext, ciphertext_len);

    // Buffers for decryption
    unsigned char decrypted[32];
    unsigned long long decrypted_len;

    printf("\n🔓 **Decryption Process** 🔓\n");

    // 🔓 Perform Decryption
    int status = crypto_aead_decrypt(decrypted, &decrypted_len, NULL, ciphertext, 
                                    ciphertext_len, ad, ad_len, nonce, key);

    // Print Decryption Results
    // Print Decryption Results
if (status == 0) {
    printf("✅ Decryption Successful!\n");

    // Print as HEX
    print_bytes("Decrypted Plaintext (Hex)", decrypted, decrypted_len);

    // Print as String
    printf("Decrypted Plaintext (String): %s\n", decrypted);
} else {
    printf("❌ Decryption Failed!\n");
}

    return 0;
}
