/***************************************************************************

	cpuintrf.h

	Core CPU interface functions and definitions.

***************************************************************************/

#ifndef CPUINTRF_H
#define CPUINTRF_H

#include "osd_cpu.h"
#include "memory.h"
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************************************
 *
 *	Enum listing all the CPUs
 *
 *************************************/

/* the following list is automatically generated by makelist.pl - don't edit manually! */
enum
{
	CPU_DUMMY,
#if defined(PINMAME) && (HAS_PPS4)
	CPU_PPS4,
#endif
#if (HAS_Z80)
	CPU_Z80,
#endif
#if (HAS_Z180)
	CPU_Z180,
#endif
#if defined(PINMAME) && (HAS_4004)
	CPU_4004,
#endif
#if (HAS_8080)
	CPU_8080,
#endif
#if (HAS_8085A)
	CPU_8085A,
#endif
#if (HAS_M6502)
	CPU_M6502,
#endif
#if (HAS_M65C02)
	CPU_M65C02,
#endif
#if (HAS_M65SC02)
	CPU_M65SC02,
#endif
#if (HAS_M65CE02)
	CPU_M65CE02,
#endif
#if (HAS_M6509)
	CPU_M6509,
#endif
#if (HAS_M6510)
	CPU_M6510,
#endif
#if (HAS_M6510T)
	CPU_M6510T,
#endif
#if (HAS_M7501)
	CPU_M7501,
#endif
#if (HAS_M8502)
	CPU_M8502,
#endif
#if (HAS_N2A03)
	CPU_N2A03,
#endif
#if (HAS_DECO16)
	CPU_DECO16,
#endif
#if (HAS_M4510)
	CPU_M4510,
#endif
#if (HAS_H6280)
	CPU_H6280,
#endif
#if (HAS_I86)
	CPU_I86,
#endif
#if (HAS_I88)
	CPU_I88,
#endif
#if (HAS_I186)
	CPU_I186,
#endif
#if (HAS_I188)
	CPU_I188,
#endif
#if (HAS_I286)
	CPU_I286,
#endif
#if (HAS_V20)
	CPU_V20,
#endif
#if (HAS_V30)
	CPU_V30,
#endif
#if (HAS_V33)
	CPU_V33,
#endif
#if (HAS_V60)
	CPU_V60,
#endif
#if (HAS_V70)
	CPU_V70,
#endif
#if (HAS_I8035)
	CPU_I8035,
#endif
#if (HAS_I8039)
	CPU_I8039,
#endif
#if (HAS_I8048)
	CPU_I8048,
#endif
#if (HAS_N7751)
	CPU_N7751,
#endif
#if (HAS_I8X41)
	CPU_I8X41,
#endif
	
#if defined(PINMAME) && (HAS_I8051)
	CPU_I8051,
#endif
#if defined(PINMAME) && (HAS_I8752)
	CPU_I8752,
#endif

#if (HAS_M6800)
	CPU_M6800,
#endif
#if (HAS_M6801)
	CPU_M6801,
#endif
#if (HAS_M6802)
	CPU_M6802,
#endif
#if (HAS_M6803)
	CPU_M6803,
#endif
#if (HAS_M6808)
	CPU_M6808,
#endif
#if (HAS_HD63701)
	CPU_HD63701,
#endif
#if (HAS_NSC8105)
	CPU_NSC8105,
#endif
#if (HAS_M6805)
	CPU_M6805,
#endif
#if (HAS_M68705)
	CPU_M68705,
#endif
#if (HAS_HD63705)
	CPU_HD63705,
#endif
#if (HAS_HD6309)
	CPU_HD6309,
#endif
#if (HAS_M6809)
	CPU_M6809,
#endif
#if (HAS_KONAMI)
	CPU_KONAMI,
#endif
#if (HAS_M68000)
	CPU_M68000,
#endif
#if defined(PINMAME) && (HAS_M68306)
        CPU_M68306,
#endif
#if (HAS_M68010)
	CPU_M68010,
#endif
#if (HAS_M68EC020)
	CPU_M68EC020,
#endif
#if (HAS_M68020)
	CPU_M68020,
#endif
#if (HAS_T11)
	CPU_T11,
#endif
#if (HAS_S2650)
	CPU_S2650,
#endif
#if (HAS_TMS34010)
	CPU_TMS34010,
#endif
#if (HAS_TMS34020)
	CPU_TMS34020,
#endif
#if (HAS_TI990_10)
	CPU_TI990_10,
#endif
#if (HAS_TMS9900)
	CPU_TMS9900,
#endif
#if (HAS_TMS9940)
	CPU_TMS9940,
#endif
#if (HAS_TMS9980)
	CPU_TMS9980,
#endif
#if (HAS_TMS9985)
	CPU_TMS9985,
#endif
#if (HAS_TMS9989)
	CPU_TMS9989,
#endif
#if (HAS_TMS9995)
	CPU_TMS9995,
#endif
#if (HAS_TMS99105A)
	CPU_TMS99105A,
#endif
#if (HAS_TMS99110A)
	CPU_TMS99110A,
#endif
#if (HAS_Z8000)
	CPU_Z8000,
#endif
#if defined(PINMAME) && (HAS_TMS7000)
	CPU_TMS7000,
#endif
#if (HAS_TMS32010)
	CPU_TMS32010,
#endif
#if (HAS_TMS32025)
	CPU_TMS32025,
#endif
#if (HAS_TMS32031)
	CPU_TMS32031,
#endif
#if (HAS_CCPU)
	CPU_CCPU,
#endif
#if (HAS_ADSP2100)
	CPU_ADSP2100,
#endif
#if (HAS_ADSP2101)
 CPU_ADSP2101,
#endif
#if (HAS_ADSP2105)
	CPU_ADSP2105,
#endif
#if (HAS_ADSP2115)
	CPU_ADSP2115,
#endif
#if (HAS_PSXCPU)
	CPU_PSXCPU,
#endif
#if (HAS_ASAP)
	CPU_ASAP,
#endif
#if (HAS_UPD7810)
	CPU_UPD7810,
#endif
#if (HAS_UPD7807)
	CPU_UPD7807,
#endif
#if (HAS_JAGUAR)
	CPU_JAGUARGPU,
	CPU_JAGUARDSP,
#endif
#if (HAS_R3000)
	CPU_R3000BE,
	CPU_R3000LE,
#endif
#if (HAS_R4600)
	CPU_R4600BE,
	CPU_R4600LE,
#endif
#if (HAS_R5000)
	CPU_R5000BE,
	CPU_R5000LE,
#endif
#if (HAS_ARM)
	CPU_ARM,
#endif
#if (HAS_SH2)
	CPU_SH2,
#endif
#if (HAS_DSP32C)
	CPU_DSP32C,
#endif
#if (HAS_PIC16C54)
	CPU_PIC16C54,
#endif
#if (HAS_PIC16C55)
	CPU_PIC16C55,
#endif
#if (HAS_PIC16C56)
	CPU_PIC16C56,
#endif
#if (HAS_PIC16C57)
	CPU_PIC16C57,
#endif
#if (HAS_PIC16C58)
	CPU_PIC16C58,
#endif
#if (HAS_G65816)
	CPU_G65816,
#endif
#if (HAS_SPC700)
	CPU_SPC700,
#endif
#if (HAS_E132XS)
	CPU_E132XS,
#endif

#ifdef MESS
#if (HAS_APEXC)
	CPU_APEXC,
#endif
#if (HAS_CDP1802)
	CPU_CDP1802,
#endif
#if (HAS_CP1600)
	CPU_CP1600,
#endif
#if (HAS_F8)
	CPU_F8,
#endif
#if (HAS_LH5801)
	CPU_LH5801,
#endif
#if (HAS_PDP1)
	CPU_PDP1,
#endif
#if (HAS_SATURN)
	CPU_SATURN,
#endif
#if (HAS_SC61860)
	CPU_SC61860,
#endif
#if (HAS_Z80GB)
	CPU_Z80GB,
#endif
#if (HAS_Z80_MSX)
	CPU_Z80_MSX,
#endif
#endif
    CPU_COUNT
};



/*************************************
 *
 *	Interrupt line constants
 *
 *************************************/

enum
{
	/* line states */
	CLEAR_LINE = 0,				/* clear (a fired, held or pulsed) line */
	ASSERT_LINE,				/* assert an interrupt immediately */
	HOLD_LINE,					/* hold interrupt line until acknowledged */
	PULSE_LINE,					/* pulse interrupt line for one instruction */

	/* internal flags (not for use by drivers!) */
	INTERNAL_CLEAR_LINE = 100 + CLEAR_LINE,
	INTERNAL_ASSERT_LINE = 100 + ASSERT_LINE,

	/* interrupt parameters */
	MAX_IRQ_LINES =	16,			/* maximum number of IRQ lines per CPU */
	IRQ_LINE_NMI = 127			/* IRQ line for NMIs */
};



/*************************************
 *
 *	CPU information constants
 *
 *************************************/

/* get_reg/set_reg constants */
enum
{
	MAX_REGS = 128,				/* maximum number of register of any CPU */

	/* This value is passed to activecpu_get_reg to retrieve the previous
	 * program counter value, ie. before a CPU emulation started
	 * to fetch opcodes and arguments for the current instrution. */
	REG_PREVIOUSPC = -1,

	/* This value is passed to activecpu_get_reg to retrieve the current
	 * program counter value. */
	REG_PC = -2,

	/* This value is passed to activecpu_get_reg to retrieve the current
	 * stack pointer value. */
	REG_SP = -3,

	/* This value is passed to activecpu_get_reg/activecpu_set_reg, instead of one of
	 * the names from the enum a CPU core defines for it's registers,
	 * to get or set the contents of the memory pointed to by a stack pointer.
	 * You can specify the n'th element on the stack by (REG_SP_CONTENTS-n),
	 * ie. lower negative values. The actual element size (UINT16 or UINT32)
	 * depends on the CPU core. */
	REG_SP_CONTENTS = -4
};


/* endianness constants */
enum
{
	CPU_IS_LE = 0,				/* emulated CPU is little endian */
	CPU_IS_BE					/* emulated CPU is big endian */
};


/* Values passed to the cpu_info function of a core to retrieve information */
enum
{
	CPU_INFO_REG,
	CPU_INFO_FLAGS = MAX_REGS,
	CPU_INFO_NAME,
	CPU_INFO_FAMILY,
	CPU_INFO_VERSION,
	CPU_INFO_FILE,
	CPU_INFO_CREDITS,
	CPU_INFO_REG_LAYOUT,
	CPU_INFO_WIN_LAYOUT
};



/*************************************
 *
 *	Core CPU interface structure
 *
 *************************************/

struct cpu_interface
{
	/* index (used to make sure we mach the enum above */
	unsigned	cpu_num;

	/* table of core functions */
	void		(*init)(void);
	void		(*reset)(void *param);
	void		(*exit)(void);
	int			(*execute)(int cycles);
	void		(*burn)(int cycles);
	unsigned	(*get_context)(void *reg);
	void		(*set_context)(void *reg);
	const void *(*get_cycle_table)(int which);
	void		(*set_cycle_table)(int which, void *new_table);
	unsigned	(*get_reg)(int regnum);
	void		(*set_reg)(int regnum, unsigned val);
	void		(*set_irq_line)(int irqline, int linestate);
	void		(*set_irq_callback)(int(*callback)(int irqline));
	const char *(*cpu_info)(void *context,int regnum);
	unsigned	(*cpu_dasm)(char *buffer,unsigned pc);

	/* IRQ and clock information */
	unsigned	num_irqs;
	int			default_vector;
	int *		icount;
	double		overclock;

	/* memory information */
	int			databus_width;
	mem_read_handler memory_read;
	mem_write_handler memory_write;
	mem_read_handler internal_read;
	mem_write_handler internal_write;
	offs_t		pgm_memory_base;
	void		(*set_op_base)(offs_t pc);
	int			address_shift;
	unsigned	address_bits;
	unsigned	endianess;
	unsigned	align_unit;
	unsigned	max_inst_len;
};



/*************************************
 *
 *	 Core CPU interface functions
 *
 *************************************/

/* reset the internal CPU tracking */
int cpuintrf_init(void);

/* set up the interface for one CPU of a given type */
int	cpuintrf_init_cpu(int cpunum, int cputype);

/* clean up the interface for one CPU */
void cpuintrf_exit_cpu(int cpunum);

/* remember the previous context and set a new one */
void cpuintrf_push_context(int cpunum);

/* restore the previous context */
void cpuintrf_pop_context(void);



/*************************************
 *
 *	 Active CPU acccessors
 *
 *************************************/

/* apply a +/- to the current icount */
void activecpu_adjust_icount(int delta);

/* return the current icount */
int activecpu_get_icount(void);

/* ensure banking is reset properly */
void activecpu_reset_banking(void);

/* set the IRQ line on a CPU -- drivers use cpu_set_irq_line() */
void activecpu_set_irq_line(int irqline, int state);

/* return a pointer to the active cycle count table for the active CPU */
const void *activecpu_get_cycle_table(int which);

/* set a pointer to the active cycle count table for the active CPU */
void activecpu_set_cycle_tbl(int which, void *new_table);

/* return the value of a register on the active CPU */
unsigned activecpu_get_reg(int regnum);

/* set the value of a register on the active CPU */
void activecpu_set_reg(int regnum, unsigned val);

/* return the PC, corrected to a byte offset, on the active CPU */
offs_t activecpu_get_pc_byte(void);

/* update the banking on the active CPU */
void activecpu_set_op_base(unsigned val);

/* disassemble a line at a given PC on the active CPU */
unsigned activecpu_dasm(char *buffer, unsigned pc);

/* return a string containing the state of the flags on the active CPU */
const char *activecpu_flags(void);

/* return a string containing the value of a register on the active CPU */
const char *activecpu_dump_reg(int regnum);

/* return a string containing the state of the active CPU */
const char *activecpu_dump_state(void);

/* return the default IRQ vector for the active CPU */
int activecpu_default_irq_vector(void);

/* return the width of the address bus on the active CPU */
unsigned activecpu_address_bits(void);

/* return the active address mask on the active CPU */
unsigned activecpu_address_mask(void);

/* return the shift value to convert from address to bytes on the active CPU */
int activecpu_address_shift(void);

/* return the endianess of the active CPU */
unsigned activecpu_endianess(void);

/* return the width of the data bus on the active CPU */
unsigned activecpu_databus_width(void);

/* return the required alignment of data accesses on the active CPU */
unsigned activecpu_align_unit(void);

/* return the maximum length of one instruction on the active CPU */
unsigned activecpu_max_inst_len(void);

/* return a string containing the name of the active CPU */
const char *activecpu_name(void);

/* return a string containing the family of the active CPU */
const char *activecpu_core_family(void);

/* return a string containing the version of the active CPU */
const char *activecpu_core_version(void);

/* return a string containing the filename for the emulator of the active CPU */
const char *activecpu_core_file(void);

/* return a string containing the emulation credits for the active CPU */
const char *activecpu_core_credits(void);

/* return a string containing the registers of the active CPU */
const char *activecpu_reg_layout(void);

/* return a string containing the debugger layout of the active CPU */
const char *activecpu_win_layout(void);



/*************************************
 *
 *	 Specific CPU acccessors
 *
 *************************************/

/* execute the requested cycles on a given CPU */
int cpunum_execute(int cpunum, int cycles);

/* signal a reset and set the IRQ ack callback for a given CPU */
void cpunum_reset(int cpunum, void *param, int (*irqack)(int));

/* read a byte from another CPU's memory space */
data8_t cpunum_read_byte(int cpunum, offs_t address);

/* write a byte from another CPU's memory space */
void cpunum_write_byte(int cpunum, offs_t address, data8_t data);

/* return a pointer to the saved context of a given CPU, or NULL if the
   context is active (and contained within the CPU core */
void *cpunum_get_context_ptr(int cpunum);

/* return a pointer to the active cycle count table for a given CPU */
const void *cpunum_get_cycle_table(int cpunum, int which);

/* set a pointer to the active cycle count table for a given CPU */
void cpunum_set_cycle_tbl(int cpunum, int which, void *new_table);

/* return the value of a register on a given CPU */
unsigned cpunum_get_reg(int cpunum, int regnum);

/* set the value of a register on a given CPU */
void cpunum_set_reg(int cpunum, int regnum, unsigned val);

/* return the PC, corrected to a byte offset, on a given CPU */
offs_t cpunum_get_pc_byte(int cpunum);

/* update the banking on a given CPU */
void cpunum_set_op_base(int cpunum, unsigned val);

/* disassemble a line at a given PC on a given CPU */
unsigned cpunum_dasm(int cpunum, char *buffer, unsigned pc);

/* return a string containing the state of the flags on a given CPU */
const char *cpunum_flags(int cpunum);

/* return a string containing the value of a register on a given CPU */
const char *cpunum_dump_reg(int cpunum, int regnum);

/* return a string containing the state of a given CPU */
const char *cpunum_dump_state(int cpunum);

/* return the default IRQ vector for a given CPU */
int cpunum_default_irq_vector(int cpunum);

/* return the width of the address bus on a given CPU */
unsigned cpunum_address_bits(int cpunum);

/* return the active address mask on a given CPU */
unsigned cpunum_address_mask(int cpunum);

/* return the shift value to convert from address to bytes on a given CPU */
int cpunum_address_shift(int cpunum);

/* return the endianess of a given CPU */
unsigned cpunum_endianess(int cpunum);

/* return the width of the data bus on a given CPU */
unsigned cpunum_databus_width(int cpunum);

/* return the required alignment of data accesses on a given CPU */
unsigned cpunum_align_unit(int cpunum);

/* return the maximum length of one instruction on a given CPU */
unsigned cpunum_max_inst_len(int cpunum);

/* return a string containing the name of a given CPU */
const char *cpunum_name(int cpunum);

/* return a string containing the family of a given CPU */
const char *cpunum_core_family(int cpunum);

/* return a string containing the version of a given CPU */
const char *cpunum_core_version(int cpunum);

/* return a string containing the filename for the emulator of a given CPU */
const char *cpunum_core_file(int cpunum);

/* return a string containing the emulation credits for a given CPU */
const char *cpunum_core_credits(int cpunum);

/* return a string containing the registers of a given CPU */
const char *cpunum_reg_layout(int cpunum);

/* return a string containing the debugger layout of a given CPU */
const char *cpunum_win_layout(int cpunum);



/*************************************
 *
 *	 CPU type acccessors
 *
 *************************************/

/* return the default IRQ vector for a given CPU type */
int cputype_default_irq_vector(int cputype);

/* return the width of the address bus on a given CPU type */
unsigned cputype_address_bits(int cputype);

/* return the active address mask on a given CPU type */
unsigned cputype_address_mask(int cputype);

/* return the shift value to convert from address to bytes on a given CPU type */
int cputype_address_shift(int cputype);

/* return the endianess of a given CPU type */
unsigned cputype_endianess(int cputype);

/* return the width of the data bus on a given CPU type */
unsigned cputype_databus_width(int cputype);

/* return the required alignment of data accesses on a given CPU type */
unsigned cputype_align_unit(int cputype);

/* return the maximum length of one instruction on a given CPU type */
unsigned cputype_max_inst_len(int cputype);

/* return a string containing the name of a given CPU type */
const char *cputype_name(int cputype);

/* return a string containing the family of a given CPU type */
const char *cputype_core_family(int cputype);

/* return a string containing the version of a given CPU type */
const char *cputype_core_version(int cputype);

/* return a string containing the filename for the emulator of a given CPU type */
const char *cputype_core_file(int cputype);

/* return a string containing the emulation credits for a given CPU type */
const char *cputype_core_credits(int cputype);

/* return a string containing the registers of a given CPU type */
const char *cputype_reg_layout(int cputype);

/* return a string containing the debugger layout of a given CPU type */
const char *cputype_win_layout(int cputype);



/*************************************
 *
 *	 Miscellaneous functions
 *
 *************************************/

/* dump the states of all CPUs */
void cpu_dump_states(void);

/* set a callback function for reset on the 68k */
void cpu_set_m68k_reset(int cpunum, void (*resetfn)(void));



/*************************************
 *
 *	 Macros
 *
 *************************************/

#define		activecpu_get_previouspc()	activecpu_get_reg(REG_PREVIOUSPC)
#define		activecpu_get_pc()			activecpu_get_reg(REG_PC)
#define		activecpu_get_sp()			activecpu_get_reg(REG_SP)
#define		activecpu_set_pc(val)		activecpu_set_reg(REG_PC, val)
#define		activecpu_set_sp(val)		activecpu_set_reg(REG_SP, val)

#define		cpunum_get_previouspc(cpu)	cpunum_get_reg(cpu, REG_PREVIOUSPC)
#define		cpunum_get_pc(cpu)			cpunum_get_reg(cpu, REG_PC)
#define		cpunum_get_sp(cpu)			cpunum_get_reg(cpu, REG_SP)
#define		cpunum_set_pc(cpu, val)		cpunum_set_reg(cpu, REG_PC, val)
#define		cpunum_set_sp(cpu, val)		cpunum_set_reg(cpu, REG_SP, val)

/* this is kind of gross - is it necessary */
#define 	cpu_geturnpc() 				activecpu_get_reg(REG_SP_CONTENTS)



/*************************************
 *
 *	 CPU interface accessors
 *
 *************************************/

/* return a pointer to the interface struct for a given CPU type */
INLINE const struct cpu_interface *cputype_get_interface(int cputype)
{
	extern const struct cpu_interface cpuintrf[];
	return &cpuintrf[cputype];
}


/* return a the index of the active CPU */
INLINE int cpu_getactivecpu(void)
{
	extern int activecpu;
	return activecpu;
}


/* return a the index of the executing CPU */
INLINE int cpu_getexecutingcpu(void)
{
	extern int executingcpu;
	return executingcpu;
}


/* return a the total number of registered CPUs */
INLINE int cpu_gettotalcpu(void)
{
	extern int totalcpu;
	return totalcpu;
}



#ifdef __cplusplus
}
#endif

#endif	/* CPUINTRF_H */

