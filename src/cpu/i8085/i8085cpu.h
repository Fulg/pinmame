/*******************************************************
 *
 *      Portable (hopefully ;-) 8085A emulator
 *
 *      Written by J. Buchmueller for use with MAME
 *
 *		Partially based on Z80Em by Marcel De Kogel
 *
 *      CPU related macros
 *
 *******************************************************/

#define SF              0x80
#define ZF              0x40
#define KF              0x20
#define HF              0x10
#define X3F             0x08
#define PF              0x04
#define VF              0x02
#define CF              0x01

#define IM_SID          0x80
#define IM_SOD          0x40
#define IM_INTR         0x20
#define IM_TRAP         0x10
#define IM_IE           0x08
#define IM_M75          0x04
#define IM_M65          0x02
#define IM_M55          0x01

#define ADDR_TRAP       0x0024
#define ADDR_RST55      0x002c
#define ADDR_RST65      0x0034
#define ADDR_RST75      0x003c
#define ADDR_INTR       0x0038

#define M_MVI(R) R=ARG()

/* rotate */
#define M_RLC {                                                                     \
	I.AF.b.h = (I.AF.b.h << 1) | (I.AF.b.h >> 7);           \
	I.AF.b.l = (I.AF.b.l & 0xfe) | (I.AF.b.h & CF);         \
}

#define M_RRC {                                                                     \
	I.AF.b.l = (I.AF.b.l & 0xfe) | (I.AF.b.h & CF);         \
	I.AF.b.h = (I.AF.b.h >> 1) | (I.AF.b.h << 7);           \
}

#define M_RAL {                                                                     \
	int c = I.AF.b.l&CF;                                                    \
	I.AF.b.l = (I.AF.b.l & 0xfe) | (I.AF.b.h >> 7);         \
	I.AF.b.h = (I.AF.b.h << 1) | c;                                 \
}

#define M_RAR {                                                                     \
	int c = (I.AF.b.l&CF) << 7;                                             \
	I.AF.b.l = (I.AF.b.l & 0xfe) | (I.AF.b.h & CF);         \
	I.AF.b.h = (I.AF.b.h >> 1) | c;                                 \
}

/* logical */
#define M_ORA(R) I.AF.b.h|=R; I.AF.b.l=ZSP[I.AF.b.h]
#define M_XRA(R) I.AF.b.h^=R; I.AF.b.l=ZSP[I.AF.b.h]
#define M_ANA(R) {UINT8 hc = ((I.AF.b.h | R)<<1) & HF; I.AF.b.h&=R; I.AF.b.l=ZSP[I.AF.b.h]; if(I.cputype) { I.AF.b.l |= HF; } else {I.AF.b.l |= hc; } }

/* increase / decrease */
#define M_INR(R) {UINT8 hc = ((R & 0x0f) == 0x0f) ? HF : 0; ++R; I.AF.b.l= (I.AF.b.l & CF ) | ZSP[R] | hc; }
#define M_DCR(R) {UINT8 hc = ((R & 0x0f) != 0x00) ? HF : 0; --R; I.AF.b.l= (I.AF.b.l & CF ) | ZSP[R] | hc | VF; }

/* arithmetic */
#define M_ADD(R) {                                                                  \
	int q = I.AF.b.h+R;                                                     \
	I.AF.b.l=ZSP[q&255]|((q>>8)&CF)|((I.AF.b.h^q^R)&HF);            \
	I.AF.b.h=q;                                                             \
}

#define M_ADC(R) {                                                                  \
	int q = I.AF.b.h+R+(I.AF.b.l&CF);                               \
	I.AF.b.l=ZSP[q&255]|((q>>8)&CF)|((I.AF.b.h^q^R)&HF);            \
	I.AF.b.h=q;                                                             \
}

#define M_SUB(R) {                                                                  \
	int q = I.AF.b.h-R;                                                     \
	I.AF.b.l=ZSP[q&255]|((q>>8)&CF)|(~(I.AF.b.h^q^R)&HF)|VF;        \
	I.AF.b.h=q;                                                             \
}

#define M_SBB(R) {                                                                  \
	int q = I.AF.b.h-R-(I.AF.b.l&CF);                               \
	I.AF.b.l=ZSP[q&255]|((q>>8)&CF)|(~(I.AF.b.h^q^R)&HF)|VF;        \
	I.AF.b.h=q;                                                             \
}

#define M_CMP(R) {                                                                  \
	int q = I.AF.b.h-R;                                                     \
	I.AF.b.l=ZSP[q&255]|((q>>8)&CF)|(~(I.AF.b.h^q^R)&HF)|VF;        \
}

#define M_IN													\
	I.XX.d=ARG();												\
	I.AF.b.h=cpu_readport16(I.XX.d);

#define M_OUT													\
	I.XX.d=ARG();												\
	cpu_writeport16(I.XX.d,I.AF.b.h)

#define M_DAD(R) {                                              \
	int q = I.HL.d + I.R.d; 									\
	I.AF.b.l = ( I.AF.b.l & ~CF ) | (q>>16 & CF );										\
	I.HL.w.l = q;												\
}

// DSUB is 8085-only, not sure if H flag handling is correct
#define M_DSUB() {                                                          \
	int q = I.HL.b.l-I.BC.b.l;                                      \
	I.AF.b.l=ZS[q&255]|((q>>8)&CF)|VF|                                      \
		((I.HL.b.l^q^I.BC.b.l)&HF)|                                 \
		(((I.BC.b.l^I.HL.b.l)&(I.HL.b.l^q)&SF)>>5);         \
	I.HL.b.l=q;                                                             \
	q = I.HL.b.h-I.BC.b.h-(I.AF.b.l&CF);                    \
	I.AF.b.l=ZS[q&255]|((q>>8)&CF)|VF|                                      \
		((I.HL.b.h^q^I.BC.b.h)&HF)|                                 \
		(((I.BC.b.h^I.HL.b.h)&(I.HL.b.h^q)&SF)>>5);         \
	if (I.HL.b.l!=0) I.AF.b.l&=~ZF;                                 \
	I.HL.b.h=q;                                                             \
}

#define M_PUSH(R) {                                             \
	WM(--I.SP.w.l, I.R.b.h);									\
	WM(--I.SP.w.l, I.R.b.l);									\
}

#define M_POP(R) {												\
	I.R.b.l = RM(I.SP.w.l++);									\
	I.R.b.h = RM(I.SP.w.l++);									\
}

#define M_RET(cc)												\
{																\
	if (cc) 													\
	{															\
		i8085_ICount -= 6;										\
		M_POP(PC);												\
		change_pc16(I.PC.d);									\
	}															\
}

// On 8085 jump if condition is not satisfied is shorter
#define M_JMP(cc) {                                                                 \
	if (cc) {                                                                       \
		I.PC.w.l = ARG16();                                         \
                change_pc16(I.PC.d);									\
	} else {                                                                        \
		I.PC.w.l += 2;                                                      \
		i8085_ICount += (I.cputype) ? 3 : 0;                            \
	}                                                                               \
}

// On 8085 call if condition is not satisfied is 9 ticks
#define M_CALL(cc)                                                                  \
{                                                                                   \
	if (cc)                                                                         \
	{                                                                               \
		UINT16 a = ARG16();                                                 \
		i8085_ICount -= (I.cputype) ? 7 : 6 ;                           \
		M_PUSH(PC);                                                                 \
		I.PC.d = a;                                                         \
                change_pc16(I.PC.d);									\
	} else {                                                                        \
		I.PC.w.l += 2;                                                      \
		i8085_ICount += (I.cputype) ? 2 : 0;                            \
	}                                                                               \
}

#define M_RST(nn) { 											\
	M_PUSH(PC); 												\
	I.PC.d = 8 * nn;											\
	change_pc16(I.PC.d);										\
}
