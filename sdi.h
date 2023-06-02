

#define EAV_CYCLE   4
#define SAV_CYCLE   4


#define SRC_WIDTH_1080      1920
#define SRC_HEIGHT_1080     1080
#define BLANK_LEN_1080      272


int convert_yuv420_1080_to_SDI
(
        uint8_t *dst,
  const uint8_t *src
);