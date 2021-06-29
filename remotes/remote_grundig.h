#include "esphome.h"

//
// on_panasonic:
//

#define BRIGHT_UP 0x01000405        // VOL-
#define BRIGHT_DOWN 0x01008485      // VOL+
#define POWER_OFF 0x0100BCBD        // power
#define POWER_ON 0x0100BCBD         // power

#define ACTION_FLASH 0x018030B1     // play
#define ACTION_STROBE 0x0180C041    // pause
#define ACTION_FADE 0x0180B839      // forward
#define ACTION_SMOOTH 0x018050D1    // reverse

#define COLOR_RED1 0x01000E0F       // red
#define COLOR_RED2 0x01000809       // 1
#define COLOR_RED3 0x0100C8C9       // 4
#define COLOR_RED4 0x01006869       // 7
#define COLOR_RED5 0x0100DCDD       // 1-

#define COLOR_GREEN1 0x01008E8F     // green
#define COLOR_GREEN2 0x01008889     // 2
#define COLOR_GREEN3 0x01002829     // 5
#define COLOR_GREEN4 0x0100E8E9     // 8
#define COLOR_GREEN5 0x01009899     // 0

#define COLOR_BLUE1 0x0100CECF      // blue
#define COLOR_BLUE2 0x01004849      // 3
#define COLOR_BLUE3 0x0100A8A9      // 6
#define COLOR_BLUE4 0x01001819      // 9
#define COLOR_BLUE5 0x01004A4B      // 2-

#define COLOR_WHITE 0x01004E4F      // yellow
