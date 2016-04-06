TITLE PDP8							(PDP8.asm)

INCLUDE Irvine32.inc
INCLUDE PDP8_Extract.inc
INCLUDE PDP8_Instructions.inc
INCLUDE PDP8_Operate.inc
INCLUDE PDP8_Interface.inc

.data
halted BYTE 0
accumulator WORD 0
link BYTE 0
programCounter WORD 0
ram WORD 111100000010b, 4094 DUP(0)
instructions DWORD accumulatorAnd, twosComplementAdd, incrementSkipIfZero, depositAccumulator,
				jumpToSubroutine, jump, ioTransfer, operate

.code
main PROC
	call interface
	exit
main ENDP

start PROC uses eax ebx
cycle:
	.IF halted == 1
		call haltMessage
	.ELSE
		call extractVariables
		xor ebx, ebx
		mov bl, opCode
		mov eax, instructions[ebx * TYPE instructions]
		call eax
		inc programCounter
		jmp cycle
		.ENDIF
	ret
start ENDP

END main