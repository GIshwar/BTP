
// Wrapper for testing the AVR version of GIFT-128 on Arduino devices.

extern "C" {
#include "gift128.h"
} // extern "C"

u8 const key[3][GIFT128_KEY_SIZE] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	//1st key
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,	//2nd key
	0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10},
	{0xd0, 0xf5, 0xc5, 0x9a, 0x77, 0x00, 0xd3, 0xe7,	//3rd key
	0x99, 0x02, 0x8f, 0xa9, 0xf9, 0x0a, 0xd8, 0x37}
};
u8 const ptext[3][GIFT128_BLOCK_SIZE] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	//1st plaintext
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,	//2nd plaintext
	0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10},
	{0xe3, 0x9c, 0x14, 0x1f, 0xa5, 0x7d, 0xba, 0x43,	//3rd plaintext
	0xf0, 0x8a, 0x85, 0xb6, 0xa9, 0x1f, 0x86, 0xc1}
};
u8 const ctext[3][GIFT128_BLOCK_SIZE] = {
	{0xcd, 0x0b, 0xd7, 0x38, 0x38, 0x8a, 0xd3, 0xf6,	//1st ciphertext
	0x68, 0xb1, 0x5a, 0x36, 0xce, 0xb6, 0xff, 0x92},
	{0x84, 0x22, 0x24, 0x1a, 0x6d, 0xbf, 0x5a, 0x93,	//2nd ciphertext
	0x46, 0xaf, 0x46, 0x84, 0x09, 0xee, 0x01, 0x52},
	{0x13, 0xed, 0xe6, 0x7c, 0xbd, 0xcc, 0x3d, 0xbf,	//3rd ciphertext
	0x40, 0x0a, 0x62, 0xd6, 0x97, 0x72, 0x65, 0xea}
};

void printHex(const char *tag, const unsigned char *data, int size)
{
    static char const hex[] = "0123456789abcdef";
    Serial.print(tag);
    while (size > 0) {
        int b = *data++;
        Serial.print(hex[(b >> 4) & 0x0F]);
        Serial.print(hex[b & 0x0F]);
        --size;
    }
    Serial.println();
}

void setup(void)
{
    Serial.begin(9600);
    Serial.println();

    Serial.println("GIFT-128[avr_fixsliced_medium]:");

    u32 rkey[GIFT128_KEY_SCHEDULE_WORDS];
    u8 state[GIFT128_BLOCK_SIZE];
    for (int vec = 0; vec < 3; ++vec) {
        gift128_keyschedule(key[vec], rkey);
        gift128_encrypt_block(state, rkey, ptext[vec]);
        Serial.print("   Vector ");
        Serial.print(vec + 1);
        Serial.print(" encryption ");
        if (!memcmp(state, ctext[vec], GIFT128_BLOCK_SIZE))
            Serial.println("ok");
        else
            Serial.println("FAILED");
        printHex("        actual   = ", state, GIFT128_BLOCK_SIZE);
        printHex("        expected = ", ctext[vec], GIFT128_BLOCK_SIZE);
        gift128_decrypt_block(state, rkey, ctext[vec]);
        Serial.print("   Vector ");
        Serial.print(vec + 1);
        Serial.print(" decryption ");
        if (!memcmp(state, ptext[vec], GIFT128_BLOCK_SIZE))
            Serial.println("ok");
        else
            Serial.println("FAILED");
        printHex("        actual   = ", state, GIFT128_BLOCK_SIZE);
        printHex("        expected = ", ptext[vec], GIFT128_BLOCK_SIZE);
    }

    Serial.println();
}

void loop()
{
}
