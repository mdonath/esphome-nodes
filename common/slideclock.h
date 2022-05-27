#pragma once

#include "esphome/core/hal.h"
#include "esphome/components/max7219digit/max7219digit.h"
#include "esphome/components/time/real_time_clock.h"
#include "esphome/core/color.h"
#include "slidefonts.h"

namespace esphome
{
    namespace max7219digit
    {
        enum SlideDirection
        {
            UP = 0,
            DOWN,
        };

        struct slide_animation
        {
            int prev = 0;
            int frame = 0;
            int next = 0;
        };
        struct current_number
        {
            int value;
            int offset;
        };
        struct separator
        {
            char type;
            int offset;
        };

        uint8_t combine_column_data(uint8_t col_prev, uint8_t col_next, int step, SlideDirection direction, slidefont::SlideFontType font)
        {
            if (direction == SlideDirection::UP)
                return (col_prev >> step) | col_next << (font.height - step);
            else
                return (col_prev << step) | col_next >> (font.height - step);
        }

        void draw_number_step(MAX7219Component &it, slidefont::SlideFontType font, int x, int y, slide_animation anim, SlideDirection direction)
        {
            for (auto col = 0; col < font.width; col++)
            {
                auto col_prev = progmem_read_byte(&font.data[anim.prev % 10][col]);
                auto col_next = progmem_read_byte(&font.data[anim.next % 10][col]);
                auto column_data = combine_column_data(col_prev, col_next, anim.frame, direction, font);
                for (auto row = 0; row < font.height; row++)
                    if (column_data & (1 << row))
                        it.draw_absolute_pixel_internal(x + col, y + row, Color::WHITE);
            }
        }

        void printSlideFormatWithFont(MAX7219Component &it, int x, int y, const char *format, time::ESPTime time, int fontSize)
        {
            // create string based on format
            char buffer[64];
            size_t len = time.strftime(buffer, sizeof(buffer), format);
            if (len == 0)
                return;

            // get font data
            slidefont::SlideFontType font = slidefont::getFont(fontSize);

            // parse string
            std::vector<current_number> current_numbers;
            std::vector<separator> separators;
            for (auto i = 0, offset = 0; i < len; i++)
            {
                char c = buffer[i];
                if (c >= '0' && c <= '9')
                {
                    current_numbers.push_back({(c - '0'), x + offset});
                    offset += font.width + 1;
                }
                else if (c == ':' || c == ';')
                {
                    separators.push_back({c, x + offset});
                    offset += 2;
                }
                else if (c == ' ')
                {
                    offset += 3;
                }
                else if (c == '|')
                {
                    offset += 1;
                }
                else if (c == '-')
                {
                    separators.push_back({c, x + offset});
                    offset += 3;
                }
                else if (c == '.')
                {
                    separators.push_back({c, x + offset});
                    offset += 2;
                }
            }

            // animation is shown during multiple calls to function
            static std::vector<slide_animation> number_animations;
            auto current_size = current_numbers.size();
            if (number_animations.capacity() < current_size)
                number_animations.resize(current_size, slide_animation());

            // draw each number
            for (auto num = 0; num < current_size; num++)
            {
                auto current_number_value = current_numbers[num].value;
                if (current_number_value != number_animations[num].prev && number_animations[num].frame == 0)
                {
                    number_animations[num].frame++;
                    number_animations[num].next = current_number_value;
                }

                draw_number_step(it,
                                 font,
                                 current_numbers[num].offset,
                                 y,
                                 number_animations[num],
                                 SlideDirection::DOWN);

                if (number_animations[num].frame > 0)
                {
                    number_animations[num].frame++;

                    if (number_animations[num].frame > font.height)
                    {
                        number_animations[num].prev = number_animations[num].next;
                        number_animations[num].frame = 0;
                    }
                }
            }

            // draw separators
            for (auto s = 0; s < separators.size(); s++)
            {
                auto sep = separators[s];
                if (sep.type == ':')
                {
                    it.draw_absolute_pixel_internal(sep.offset, 2, Color::WHITE);
                    it.draw_absolute_pixel_internal(sep.offset, 4, Color::WHITE);
                }
                else if (sep.type == ';')
                {
                    auto d = time.second % 2;
                    it.draw_absolute_pixel_internal(sep.offset, 2 - d, Color::WHITE);
                    it.draw_absolute_pixel_internal(sep.offset, 4 + d, Color::WHITE);
                }
                else if (sep.type == '-')
                {
                    it.line(sep.offset, 3, sep.offset + 1, 3, Color::WHITE);
                }
                else if (sep.type == '.')
                {
                    it.draw_absolute_pixel_internal(sep.offset, 6, Color::WHITE);
                }
            }
        }

        void printSlideFormat(MAX7219Component &it, int x, int y, const char *format, time::ESPTime time)
        {
            printSlideFormatWithFont(it, x, y, format, time, 5);
        }

        void printSlideTimeWithFont(MAX7219Component &it, int x, int y, const char *format, time::ESPTime time, int fontSize)
        {
            printSlideFormatWithFont(it, x, y, format, time, fontSize);
        }

        /**
         * Prints HH:MM at (x,y) on a 4 chip 'platform:max7219digit' display.
         *
         * Example:
         *
         * ========
         * display:
         *   - platform: max7219digit
         *     id: display_clock
         *     cs_pin: D8
         *     num_chips: 4
         *     rotate_chip: 180
         *     reverse_enable: True
         *     intensity: 1
         *     update_interval: 67ms
         *     lambda: |-
         *         printSlideTime(it, 5, 0, id(hass_time).now());
         * ========
         * @param it    A max7219 matrix display
         * @param x     Horizontal position (left)
         * @param y     Vertical position (top)
         * @param time  Current time
         */
        void printSlideTime(MAX7219Component &it, int x, int y, time::ESPTime time)
        {
            printSlideTimeWithFont(it, x, y, "%H;%M", time, 5);
        }

    } // namespace max7219digit
} // namespace esphome
