#pragma once
 
#include "esphome/core/component.h"
#include "esphome/core/defines.h"
 
#ifdef USE_TIME
#include "esphome/components/time/real_time_clock.h"
#endif
 
#include "esphome/components/spi/spi.h"
 
namespace esphome {
namespace max7219 {
 
class MAX7219MappedComponent;
 
using max7219mapped_writer_t = std::function<void(MAX7219MappedComponent &)>;
 
 class MAX7219MappedComponent : public PollingComponent,
                                public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                                      spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1MHZ> {
  public:
   void set_mapping(std::initializer_list<uint8_t> mapping);

   void set_writer(max7219mapped_writer_t &&writer);
 
   void setup() override;
 
   void dump_config() override;
 
   void update() override;
 
   float get_setup_priority() const override;
 
   void display();
 
   void set_intensity(uint8_t intensity);
   void set_num_chips(uint8_t num_chips);
   void set_reverse(bool reverse) { this->reverse_ = reverse; };
 
   uint8_t printf(uint8_t pos, const char *format, ...) __attribute__((format(printf, 3, 4)));
   uint8_t printf(const char *format, ...) __attribute__((format(printf, 2, 3)));
 
   uint8_t print(uint8_t pos, const char *str);
   uint8_t print(const char *str);
 
 #ifdef USE_TIME
   uint8_t strftime(uint8_t pos, const char *format, time::ESPTime time) __attribute__((format(strftime, 3, 0)));
 
   uint8_t strftime(const char *format, time::ESPTime time) __attribute__((format(strftime, 2, 0)));
 #endif
 
  protected:
   void send_byte_(uint8_t a_register, uint8_t data);
   void send_to_all_(uint8_t a_register, uint8_t data);
 
   uint8_t intensity_{15};  
   uint8_t num_chips_{1};
   uint8_t *buffer_;
   bool reverse_{false};
   optional<max7219mapped_writer_t> writer_{};
   bool has_map_{false};
   uint8_t map_[16];
 };
 
 }  // namespace max7219
 }  // namespace esphome