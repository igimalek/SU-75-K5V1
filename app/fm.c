/* Original work Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Modified work Copyright 2024 kamilsss655
 * https://github.com/kamilsss655
 *
 * Copyright 2024 kamilsss655
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


#include "app/action.h"
#include "app/fm.h"
#include "app/generic.h"

#include "driver/bk1080.h"
#include "driver/bk4819.h"
#include "misc.h"
#include "settings.h"
#include "ui/ui.h"
#include "driver/gpio.h"

const uint16_t FM_RADIO_MAX_FREQ = 1080; // 108  Mhz
const uint16_t FM_RADIO_MIN_FREQ = 875;  // was 87.5 Mhz

bool              gFmRadioMode;
uint8_t           gFmRadioCountdown_500ms;
volatile uint16_t gFmPlayCountdown_10ms;
volatile int8_t   gFM_ScanState;
uint16_t          gFM_RestoreCountdown_10ms;
bool              gFM_ManualMode = false;
bool              gFM_Mute       = false;

void FM_TurnOff(void)
{
	gFmRadioMode              = false;
	gFM_ScanState             = FM_SCAN_OFF;
	gFM_RestoreCountdown_10ms = 0;
	gFM_ManualMode            = false;

	// если бекен рации был заглушён — восстанавливаем
	if (gFM_Mute) {
		gFM_Mute = false;
		BK4819_RX_TurnOn();
	}

	AUDIO_AudioPathOff();
	gEnableSpeaker = false;
	BK1080_Init(0, false);

	// восстанавливаем BK4819 для приёма рации
	gFlagReconfigureVfos = true;
}

static void Key_EXIT()
{
	ACTION_FM();
	return;
}

static void Key_UP_DOWN(bool direction)
{
	if (gFM_ManualMode) {
		// MANUAL: шаг 0.1 МГц (1 в единицах ×0.1 МГц)
		uint16_t freq = gEeprom.FM_FrequencyPlaying;
		if (direction) {
			if (freq < FM_RADIO_MAX_FREQ)
				freq++;
			else
				freq = FM_RADIO_MIN_FREQ;
		} else {
			if (freq > FM_RADIO_MIN_FREQ)
				freq--;
			else
				freq = FM_RADIO_MAX_FREQ;
		}
		gEeprom.FM_FrequencyPlaying = freq;
		BK1080_SetFrequency(freq);
	} else {
		// AUTO: ищем ближайшую станцию
		BK1080_TuneNext(direction);
		gEeprom.FM_FrequencyPlaying = BK1080_GetFrequency();
	}
	gRequestSaveSettings = true;
}

static void Key_STAR(bool bKeyHeld)
{
	if (bKeyHeld) {
		// Длинное нажатие — переключить MUTE
		gFM_Mute = !gFM_Mute;
		if (gFM_Mute) {
			// Выключаем бекен рации — BK4819 не принимает
			BK4819_WriteRegister(BK4819_REG_30, 0x0000);
		} else {
			// Включаем бекен рации обратно
			BK4819_RX_TurnOn();
		}
	} else {
		// Короткое нажатие — переключить AUTO / MANUAL
		gFM_ManualMode = !gFM_ManualMode;
	}
}

void FM_ProcessKeys(KEY_Code_t Key, bool bKeyPressed, bool bKeyHeld)
{	
	uint8_t state = bKeyPressed + 2 * bKeyHeld;

	// Длинное нажатие STAR — MUTE (срабатывает при первом тике удержания)
	if (bKeyHeld && bKeyPressed && Key == KEY_STAR) {
		Key_STAR(true);
		return;
	}

	if (state == 0) {
		switch (Key)
		{	
			case KEY_UP:
				Key_UP_DOWN(true);
				break;
			case KEY_DOWN:
				Key_UP_DOWN(false);
				break;
			case KEY_EXIT:
				Key_EXIT();
				break;
			case KEY_STAR:
				// Короткое нажатие — AUTO/MANUAL
				Key_STAR(false);
				break;
			default:
				
				break;
		}
	}
}

void FM_Start(void)
{
	gFmRadioMode              = true;
	gFM_ScanState             = FM_SCAN_OFF;
	gFM_RestoreCountdown_10ms = 0;

	gFmPlayCountdown_10ms = 0;
	gScheduleFM           = false;

	BK1080_Init(gEeprom.FM_FrequencyPlaying, true);

	AUDIO_AudioPathOn();

	GUI_SelectNextDisplay(DISPLAY_FM);

	// let the user see DW is not active
	gDualWatchActive     = false;

	gEnableSpeaker       = true;
	        
}

