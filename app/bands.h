/*Frequencies are 10Hz: 100M is written 10000000
  Max bandname length is 11
  AVAILABLE STEPS ARE 
  S_STEP_0_01kHz,  S_STEP_0_1kHz,  S_STEP_0_5kHz,  S_STEP_1_0kHz,  S_STEP_2_5kHz,  S_STEP_5_0kHz,  S_STEP_6_25kHz,
  S_STEP_8_33kHz,  S_STEP_10_0kHz,  S_STEP_12_5kHz,  S_STEP_25_0kHz,  S_STEP_100kHz,  S_STEP_500kHz, */


#ifdef ENABLE_FULL_BAND
static const bandparameters BParams[MAX_BANDS] = {
    {"20M (14MHz)",    1400000,          1435000,       S_STEP_5_0kHz,    MODULATION_SSB},
    {"17M (18MHz)",    1806800,          1816800,       S_STEP_5_0kHz,    MODULATION_SSB},
    {"15M (21MHz)",    2100000,          2145000,       S_STEP_1_0kHz,    MODULATION_SSB},
    {"12M (24MHz)",    2489000,          2499000,       S_STEP_1_0kHz,    MODULATION_SSB},
    {"CB (27MHz)",     2651500,          2830500,       S_STEP_5_0kHz,    MODULATION_FM},
    {"10M (28MHz)",    2800000,          2970000,       S_STEP_1_0kHz,    MODULATION_AM},
    {"LB (43MHz)",     4330000,          4358750,       S_STEP_10_0kHz,   MODULATION_FM},
    {"5M(50MHz)",      5000000,          5400000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"5M+(57MHz)",     5700000,          5750000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"AIR",           11800000,         13790000,       S_STEP_25_0kHz,   MODULATION_AM},
    {"136-144MHz",    13600000,         14400000,       S_STEP_25_0kHz,   MODULATION_FM},
    {"2M (145MHz)",   14400000,         14650000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"2M (146MHz)",   14660000,         14790000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"SECURITY",      14800000,         14900000,       S_STEP_5_0kHz,    MODULATION_FM},
    {"RAIL",          15172500,         15600000,       S_STEP_25_0kHz,   MODULATION_FM},
    {"MARINE",        15600000,         16327500,       S_STEP_25_0kHz,   MODULATION_FM},
    {"VHF(162MHz)",   16200000,         17000000,       S_STEP_25_0kHz,   MODULATION_FM},
	{"VHF(170MHz)",   17000000,         17400000,       S_STEP_25_0kHz,   MODULATION_FM},
    {"SATCOM-L",      24000000,         25000000,       S_STEP_5_0kHz,    MODULATION_FM},
    {"SATCOM-H",      25050000,         27000000,       S_STEP_5_0kHz,    MODULATION_FM},
    {"RIVER",         30002500,         30051250,       S_STEP_5_0kHz,    MODULATION_FM},
    {"ARMY",          30051300,         33600000,       S_STEP_5_0kHz,    MODULATION_FM},
    {"RIVER",         33601250,         34000050,       S_STEP_5_0kHz,    MODULATION_FM},
    {"LTE",           36000000,         38000000,       S_STEP_5_0kHz,    MODULATION_FM},
    {"UHF400",        40000000,         43300000,       S_STEP_25_0kHz,   MODULATION_FM},
    {"LPD 433",       43307500,         43480000,       S_STEP_25_0kHz,   MODULATION_FM},
    {"PMR 446",       44600625,         44619375,       S_STEP_12_5kHz,   MODULATION_FM},
    {"450MHz",        44700625,         45900000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"GOV 460MHz",    46000000,         46200000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"LORA ",         86400000,         86900000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"GSM900",        89000000,         91500000,       S_STEP_12_5kHz,   MODULATION_FM},
    {"GSM900",        93500000,         96000000,       S_STEP_12_5kHz,   MODULATION_FM},
}; 
#endif


