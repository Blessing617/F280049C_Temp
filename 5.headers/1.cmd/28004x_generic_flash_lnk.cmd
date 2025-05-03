
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to Flash" bootloader mode   */

   BEGIN           	: origin = 0x080000, length = 0x000002
   RAMM0           	: origin = 0x0000F6, length = 0x00030A

   RAMLS0          	: origin = 0x008000, length = 0x000800
   RAMLS1          	: origin = 0x008800, length = 0x000800
   RAMLS2      		: origin = 0x009000, length = 0x000800
   RAMLS3      		: origin = 0x009800, length = 0x000800
   RAMLS4      		: origin = 0x00A000, length = 0x000800
   RAMLS            : origin = 0x00A800, length = 0x003FF8
   RESET           	: origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   /* BANK 0 */
   FLASH_BANK0_SEC0  : origin = 0x080002, length = 0x000FFE	/* on-chip Flash */
   FLASH_BANK0_SEC1  : origin = 0x081000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC2  : origin = 0x082000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC3  : origin = 0x083000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC4  : origin = 0x084000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC5  : origin = 0x085000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC6  : origin = 0x086000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC7  : origin = 0x087000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC8  : origin = 0x088000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC9  : origin = 0x089000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC10 : origin = 0x08A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC11 : origin = 0x08B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC12 : origin = 0x08C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC13 : origin = 0x08D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC14 : origin = 0x08E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK0_SEC15 : origin = 0x08F000, length = 0x001000	/* on-chip Flash */

   /* BANK 1 */
   FLASH_BANK1_SEC0  : origin = 0x090000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC1  : origin = 0x091000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC2  : origin = 0x092000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC3  : origin = 0x093000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC4  : origin = 0x094000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC5  : origin = 0x095000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC6  : origin = 0x096000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC7  : origin = 0x097000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC8  : origin = 0x098000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC9  : origin = 0x099000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC10 : origin = 0x09A000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC11 : origin = 0x09B000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC12 : origin = 0x09C000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC13 : origin = 0x09D000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC14 : origin = 0x09E000, length = 0x001000	/* on-chip Flash */
   FLASH_BANK1_SEC15 : origin = 0x09F000, length = 0x000FF0	/* on-chip Flash */

   CSM_RSVD   		 : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL    		 : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA            */
   OTP        		 : origin = 0x380400, length = 0x000400     /* on-chip OTP */
   ADC_CAL    		 : origin = 0x380080, length = 0x000009

   IQTABLES    		 : origin = 0x3FE000, length = 0x000b50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   		 : origin = 0x3FEB50, length = 0x00008c     /* IQ Math Tables in Boot ROM */
   FPUTABLES   		 : origin = 0x3FEBDC, length = 0x0006A0     /* FPU Tables in Boot ROM */

//   FLASH_BANK1_SEC15_RSVD : origin = 0x09FFF0, length = 0x000010  /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

PAGE 1 :

   BOOT_RSVD       : origin = 0x000002, length = 0x0000F1     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD      : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS5      : origin = 0x00A800, length = 0x002000
   RAMLS6      : origin = 0x00C800, length = 0x002000
   RAMLS7      : origin = 0x00E800, length = 0x002000

   RAMGS0      : origin = 0x010800, length = 0x002000
   RAMGS1      : origin = 0x012800, length = 0x002000
   RAMGS2      : origin = 0x014800, length = 0x002000
   RAMGS3      : origin = 0x016800, length = 0x001FF8
//   RAMGS3_RSVD : origin = 0x013FF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{

    FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD

	FFT_buffer1		: > RAMLS6,     PAGE = 1,    ALIGN = 4096
	FFT_buffer2		: > RAMLS7,     PAGE = 1,	 ALIGN = 4096

   codestart        : > BEGIN,     PAGE = 0, ALIGN(4)
   .text            : >> FLASH_BANK0_SEC2 | FLASH_BANK0_SEC3 | FLASH_BANK0_SEC5 | FLASH_BANK0_SEC6,   PAGE = 0, ALIGN(4)
   .cinit           : > FLASH_BANK0_SEC1,     PAGE = 0, ALIGN(4)
   .switch          : > FLASH_BANK0_SEC1,     PAGE = 0, ALIGN(4)
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM1,     PAGE = 1

#if defined(__TI_EABI__)
   .init_array      : > FLASH_BANK0_SEC1,       PAGE = 0,       ALIGN(4)
   .bss             : > RAMLS5,       			PAGE = 1
   .bss:output      : > RAMLS3,      			PAGE = 0
   .bss:cio         : > RAMLS0,       			PAGE = 0
   .data            : >> RAMLS5|RAMLS6   		PAGE = 1,		ALIGN(4)
   .sysmem          : > RAMLS5,       			PAGE = 1
   /* Initalized sections go in Flash */
   .const           : >> FLASH_BANK0_SEC4|FLASH_BANK0_SEC7,       PAGE = 0,       ALIGN(4)
#else
   .pinit           : > FLASH_BANK0_SEC1,       PAGE = 0,       ALIGN(4)
   .ebss            : > RAMLS5,       PAGE = 1
   .esysmem         : > RAMLS5,       PAGE = 1
   .cio             : > RAMLS0,       PAGE = 0
   .econst          : > FLASH_BANK0_SEC4,    PAGE = 0, ALIGN(4)
#endif

   ramgs0           : > RAMGS0,    PAGE = 1
   ramgs1           : > RAMGS1,    PAGE = 1
   ramgs2			: > RAMGS2,	   PAGE = 1

#if defined(__TI_EABI__)
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS0,
                      LOAD_START(RamfuncsLoadStart),
                      LOAD_SIZE(RamfuncsLoadSize),
                      LOAD_END(RamfuncsLoadEnd),
                      RUN_START(RamfuncsRunStart),
                      RUN_SIZE(RamfuncsRunSize),
                      RUN_END(RamfuncsRunEnd),
                      PAGE = 0, ALIGN(4)
#else
   .TI.ramfunc      : LOAD = FLASH_BANK0_SEC1,
                      RUN = RAMLS0,
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                      PAGE = 0, ALIGN(4)
#endif
	SINTBL 				: > RAMGS1,       			PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
