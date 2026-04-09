
#include "functions.h"
#include "misc.h"
#include "settings.h"
#include "ui/ui.h"
#include "driver/eeprom.h"
#include "radio.h"

// Записываем SCRAMBLING_TYPE в байт 15 нужного блока EEPROM (base + 8 + 7)
static void PropagateScrambler(uint16_t Channel)
{
	uint16_t base = IS_MR_CHANNEL(Channel)
		? (ADRESS_FREQ_PARAMS + Channel * 16)
		: (0x0C80 + (Channel - FREQ_CHANNEL_FIRST) * 32);

	uint8_t data[8];
	EEPROM_ReadBuffer(base + 8, data, sizeof(data));
	data[7] = gTxVfo->SCRAMBLING_TYPE;
	EEPROM_WriteBuffer(base + 8, data);
}

void COMMON_KeypadLockToggle() 
{

    if (gScreenToDisplay != DISPLAY_MENU &&
        gCurrentFunction != FUNCTION_TRANSMIT)
    {	// toggle the keyboad lock

        gEeprom.KEY_LOCK = !gEeprom.KEY_LOCK;

        gRequestSaveSettings = true;
    }
}

void COMMON_SwitchToVFOMode()
{
    PropagateScrambler(gEeprom.FreqChannel);   // скремблер → VFO EEPROM
    gEeprom.ScreenChannel = gEeprom.FreqChannel;
    gRequestSaveVFO     = true;
    gVfoConfigureMode   = VFO_CONFIGURE_RELOAD;
    return;
}
void COMMON_SwitchToChannelMode()
{
    uint16_t Channel = RADIO_FindNextChannel(gEeprom.MrChannel, 1, false,0);
    if (Channel != 0xFFFF)
    {	// swap to Channel mode
        PropagateScrambler(Channel);           // скремблер → MR канал EEPROM
        gEeprom.ScreenChannel = Channel;
        gRequestSaveVFO     = true;
        gVfoConfigureMode   = VFO_CONFIGURE_RELOAD;
        return;
    }
}

void COMMON_SwitchVFOMode()
{
    if (gEeprom.VFO_OPEN)
    {
        if (IS_MR_CHANNEL(gTxVfo->CHANNEL_SAVE))
        {	// swap to frequency mode
            COMMON_SwitchToVFOMode();
        }
        else
        {
            //swap to Channel mode
            COMMON_SwitchToChannelMode();
        }
    }
}