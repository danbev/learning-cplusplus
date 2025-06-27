#include <cstdio>
#include <cstdint>

int main() {
    {
        int packed = 7;
        printf("Packed: %d\n", packed);
        int trit0 = packed % 3;
        packed /= 3;
        int trit1 = packed % 3;

        printf("trits: [%d, %d]\n", trit1, trit0);
    }

    {
        int trits[5] = {2, 1, 0, 2, 1};
        printf("original trits [");
        for (int v: trits) {
            printf("%d, ", v);
        }
        printf("]\n");

        uint8_t q = 0;
        for (int n = 0; n < 5; n++) {
            q *= 3;
            q += trits[n];
        }
        printf("Base-3 value: %d\n", q);

        // The following is done to to enable the overflow-extration, that we will do
        // later, to work as it is designed to work for [0, 255] range, but currently
        // the range is [0, 242]. Without this the bit positions don't line up correctly.
        // So we have our base3 value, like 196, which is in the range of [0, 242], when we
        // rescale this are we like stretching this value (that represents our packed trits)
        // to map into the range [0,255] and this will allow the >> 8 work correctly. The
        // underlying trits are still representing the original values but we are "viewing"
        // them in a different way.
        uint8_t rescaled = ((uint16_t) q * 256 + 242) / 243;
        printf("Rescaled: %d\n", rescaled);

        const uint8_t pow3[6] = {1, 3, 9, 27, 81, 243};

        printf("\nExtracting trits:\n[");
        for (int n = 0; n < 5; n++) {
            uint8_t q_step = rescaled * pow3[n];
            int16_t xi = ((uint16_t)q_step * 3) >> 8;
            int recovered_trit = xi;

            printf("%d, ", recovered_trit);
        }
        printf("]\n");
    }
    return 0;
}
