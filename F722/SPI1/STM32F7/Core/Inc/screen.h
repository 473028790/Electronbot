#ifndef ELECTRONBOT_FW_SCREEN_H
#define ELECTRONBOT_FW_SCREEN_H

#include "main.h"
#include "spi.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DEGREE_0,
    DEGREE_90,
    DEGREE_180,
    DEGREE_270
} Orientation_t;

typedef enum {
    BIT_12,
    BIT_16,
    BIT_18
} ColorMode_t;

typedef struct {
    SPI_HandleTypeDef* spi;
    Orientation_t orientation;
    ColorMode_t colorMode;
    volatile bool isBusy;
} Screen;

void Screen_Reset(bool enable);
void screen_init(Orientation_t _orientation);
void Screen_SetDataOrCommand(bool isData);
void WriteCommand(uint8_t _cmd);
void Write1Byte(uint8_t _data);
void Screen_SetWindow(uint16_t _startX, uint16_t _endX, uint16_t _startY, uint16_t _endY);
void WriteData(uint8_t* _data, uint32_t _len, bool _useDma);
void Screen_WriteFrameBuffer(uint8_t* _buffer, uint32_t _len, bool _isAppend);

#endif
