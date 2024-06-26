#include "PR/rcp.h"
#include "../os/osint.h"

s32 osAiSetFrequency(u32 frequency) {
    register u32 dacRate;
#if LIBULTRA_VERSION >= OS_VER_J
    register u32 bitRate;
#else
    register s32 bitRate;
#endif
    register float f;

    f = osViClock / (float) frequency + .5f;
    dacRate = f;

    if (dacRate < AI_MIN_DAC_RATE) {
        return -1;
    }

    bitRate = (dacRate / 66) & 0xff;

    if (bitRate > AI_MAX_BIT_RATE) {
        bitRate = AI_MAX_BIT_RATE;
    }

    IO_WRITE(AI_DACRATE_REG, dacRate - 1);
    IO_WRITE(AI_BITRATE_REG, bitRate - 1);
#if LIBULTRA_VERSION < OS_VER_J
    IO_WRITE(AI_CONTROL_REG, AI_CONTROL_DMA_ON);
#endif
    return osViClock / (s32) dacRate;
}
