/* Original work Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Modified work Copyright 2024 kamilsss655
 * https://github.com/kamilsss655
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>

#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "version.h"
#ifdef ENABLE_SCREENSHOT
    #include "screenshot.h"
#endif

void UI_DisplayReleaseKeys(void)
{
	memset(gStatusLine,  0, sizeof(gStatusLine));
	memset(gFrameBuffer, 0, sizeof(gFrameBuffer));

	UI_PrintString("RELEASE", 0, 127, 1, 10);
	UI_PrintString("ALL KEYS", 0, 127, 3, 10);

	ST7565_BlitStatusLine();  // blank status line
	ST7565_BlitFullScreen();
}

void UI_DisplayWelcome(void)
{
	char WelcomeString0[16];
	char WelcomeString1[16];
	
	memset(gStatusLine,  0, sizeof(gStatusLine));
	memset(gFrameBuffer, 0, sizeof(gFrameBuffer));

	if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE)
	{
		ST7565_BlitFullScreen();
	}
	else
	if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_FULL_SCREEN)
	{
		ST7565_FillScreen(0xFF);
	}
	else
	{
		memset(WelcomeString0, 0, sizeof(WelcomeString0));
		memset(WelcomeString1, 0, sizeof(WelcomeString1));

		if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_VOLTAGE)
		{
			strcpy(WelcomeString0, "CHECKMATE");
			sprintf(WelcomeString1, "%u.%02uV %u%%",
				gBatteryVoltageAverage / 100,
				gBatteryVoltageAverage % 100,
				BATTERY_VoltsToPercent(gBatteryVoltageAverage));
		}
		else
		{
			//EEPROM_ReadBuffer(0x0EB0, WelcomeString0, 16);
			//EEPROM_ReadBuffer(0x0EC0, WelcomeString1, 16);
			strcpy(WelcomeString0, "CHECKMATE");
#ifdef ENABLE_EEPROM_512K
			strcpy(WelcomeString1, "BIG EEPROM");
#else 
			strcpy(WelcomeString1, "STOCK EEPROM");
#endif
		}

		UI_PrintString(WelcomeString0, 0, 127, 0, 10);
		UI_PrintString(WelcomeString1, 0, 127, 2, 10);
		UI_PrintString(Version, 0, 120, 4,10);
		GUI_DisplaySmallestDark("V.7.4.6", 50, 49, false, false);

		//UI_PrintStringSmallBold("V.7.4.4", 1, LCD_WIDTH - 1, 6, 0);


		GUI_DisplaySmallest("OURO", 5, 49, false, true);
		GUI_DisplaySmallest("MODE", 108, 49, false, true);



		 //*******************ЛИНИИ-LINES***************** */
        for (uint8_t y = 47; y <= 57; y += 2) {
            UI_DrawLineBuffer(gFrameBuffer, 30, y, 30, y, 1); // Левая вертикальная пунктирная(X = 30)
        }
        for (uint8_t y = 47; y <= 57; y += 2) {
            UI_DrawLineBuffer(gFrameBuffer, 94, y, 94, y, 1);  // Правая вертикальная пунктирная (X = 90)
        }

        for (uint8_t i = 0; i <= 127; i += 2) {
            UI_DrawLineBuffer(gFrameBuffer, i, 15, i, 15, 1); // Hory X
        }
                for (uint8_t i = 0; i <= 127; i += 2) {
            UI_DrawLineBuffer(gFrameBuffer, i, 30, i, 30, 1); // Hory X
        }

		ST7565_BlitStatusLine();  // blank status line
		ST7565_BlitFullScreen();
		#ifdef ENABLE_SCREENSHOT
            getScreenShot(true);
        #endif
	}
}

