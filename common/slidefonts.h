#pragma once

#include "esphome/core/hal.h"

namespace esphome
{
    namespace max7219digit
    {
        namespace slidefont
        {
            struct SlideFontType
            {
                uint8_t width;
                uint8_t height;
                uint8_t data[10][7];
            };
            const SlideFontType pacman PROGMEM = {
                7,
                8,
                {
                    {0xFE, 0x73, 0xF3, 0x7F, 0xF3, 0x73, 0xFE}, // 0 no eyes
                    {0xFE, 0x7B, 0xF3, 0x7F, 0xFB, 0x73, 0xFE}, // 1 eyes left-down
                    {0xFE, 0x77, 0xF3, 0x7F, 0xF7, 0x73, 0xFE}, // 2 eyes left-up
                    {0xFE, 0x73, 0xFB, 0x7F, 0xF3, 0x7B, 0xFE}, // 3 eyes right-down
                    {0xFE, 0x73, 0xF7, 0x7F, 0xF3, 0x77, 0xFE}, // 4 eyes right-up

                }};

            const SlideFontType font3 PROGMEM = {
                3,
                8,
                {
                    {0x7F, 0x41, 0x7F}, // 0
                    {0x04, 0x02, 0x7F}, // 1
                    {0x79, 0x49, 0x4F}, // 2
                    {0x49, 0x49, 0x7F}, // 3
                    {0x0F, 0x08, 0x7F}, // 4
                    {0x4F, 0x49, 0x79}, // 5
                    {0x7F, 0x49, 0x79}, // 6
                    {0x71, 0x09, 0x07}, // 7
                    {0x7F, 0x49, 0x7F}, // 8
                    {0x4F, 0x49, 0x7F}, // 9
                }};

            const SlideFontType font4 PROGMEM = {
                4,
                8,
                {
                    {0x3E, 0x41, 0x41, 0x3E}, // 0
                    {0x00, 0x04, 0x02, 0x7F}, // 1
                    {0x62, 0x51, 0x49, 0x46}, // 2
                    {0x22, 0x49, 0x49, 0x36}, // 3
                    {0x18, 0x14, 0x12, 0x7F}, // 4
                    {0x4F, 0x49, 0x49, 0x31}, // 5
                    {0x3E, 0x49, 0x49, 0x32}, // 6
                    {0x61, 0x11, 0x09, 0x07}, // 7
                    {0x36, 0x49, 0x49, 0x36}, // 8
                    {0x26, 0x49, 0x49, 0x3E}, // 9
                }};

            const SlideFontType font5 PROGMEM = {
                5,
                8,
                {
                    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
                    {0x40, 0x42, 0x7F, 0x40, 0x40}, // 1
                    {0x62, 0x51, 0x49, 0x49, 0x46}, // 2
                    {0x22, 0x41, 0x49, 0x49, 0x36}, // 3
                    {0x18, 0x14, 0x12, 0x11, 0x7F}, // 4
                    {0x47, 0x45, 0x45, 0x45, 0x39}, // 5
                    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
                    {0x03, 0x01, 0x71, 0x09, 0x07}, // 7
                    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
                    {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
                }};

            /**
             * @brief Get the font with given width
             *
             * @param fontSize Possible fontSizes: 3, 4, 5
             * @return SlideFontType
             */
            SlideFontType getFont(int fontSize)
            {
                if (fontSize == 0)
                    return pacman;
                if (fontSize == 3)
                    return font3;
                if (fontSize == 4)
                    return font4;
                if (fontSize == 5)
                    return font5;
                return font5;
            }

        } // namespace slidefont

    } // namespace max7219digit

} // namespace esphome
