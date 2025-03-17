#ifndef GIFT128_H_
#define GIFT128_H_

typedef unsigned char u8;
typedef unsigned int u32;

extern void precompute_rkeys(u32* rkeys, const u8* key);
extern void giftb128(u8* out, const u8* in, const u32* rkeys);

#define ROR(x,y) (((x) >> (y)) | ((x) << (32 - (y))))

// Define SWAPMOVE to fix implicit declaration error
#define SWAPMOVE(x, y, mask, n) ((x = ((x & mask) << n) | ((y >> n) & mask)))

// S-Box
static const u8 GIFT_SBOX[16] = {
    0x1, 0xA, 0x4, 0xC, 0x6, 0xF, 0x3, 0x9,
    0x2, 0xD, 0xB, 0x7, 0x5, 0x0, 0x8, 0xE
};

// Function to apply the new S-Box substitution
static inline u32 apply_sbox(u32 state) {
    u32 new_state = 0;
    for (int i = 0; i < 8; i++) {
        new_state |= GIFT_SBOX[(state >> (4 * i)) & 0xF] << (4 * i);
    }
    return new_state;
}

// Apply S-Box substitution in the encryption rounds
#define QUINTUPLE_ROUND(state, rkey, rconst) ({ \
    state[0] = apply_sbox(state[0]);           \
    state[1] = apply_sbox(state[1]);           \
    state[2] = apply_sbox(state[2]);           \
    state[3] = apply_sbox(state[3]);           \
    state[1] ^= (rkey)[0];                     \
    state[2] ^= (rkey)[1];                     \
    state[0] ^= (rconst)[0];                   \
    state[3] = ROR(state[3], 16);              \
    state[2] = ROR(state[2], 16);              \
    state[1] ^= (rkey)[2];                     \
    state[2] ^= (rkey)[3];                     \
    state[3] ^= (rconst)[1];                   \
    state[0] ^= state[3];                      \
    state[3] ^= state[0];                      \
    state[0] ^= state[3];                      \
})

#endif  // GIFT128_H_
