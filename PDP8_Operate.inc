TITLE PDP8_Operate						(PDP8_Operate.inc)

INCLUDE PDP8_Operate_Instructions.inc

.data
bit1 BYTE ?
bit2 BYTE ?
bit3 BYTE ?
bit4 BYTE ?
bit5 BYTE ?
bit6 BYTE ?
bit7 BYTE ?
bit8 BYTE ?
skip BYTE 0
groups DWORD groupOne, groupTwo

.code
startOperate PROC
	call extractOperateVariables
	call doOperate
	ret
startOperate ENDP

extractOperateVariables PROC uses eax
	mov ax, instruction
	shr ax, 7
	and ax, 1b
	mov bit1, al

	mov ax, instruction
	shr ax, 6
	and ax, 1b
	mov bit2, al

	mov ax, instruction
	shr ax, 5
	and ax, 1b
	mov bit3, al

	mov ax, instruction
	shr ax, 4
	and ax, 1b
	mov bit4, al

	mov ax, instruction
	shr ax, 3
	and ax, 1b
	mov bit5, al

	mov ax, instruction
	shr ax, 2
	and ax, 1b
	mov bit6, al

	mov ax, instruction
	shr ax, 1
	and ax, 1b
	mov bit7, al

	mov ax, instruction
	and ax, 1b
	mov bit8, al
	ret
extractOperateVariables ENDP

doOperate PROC uses eax ebx
	xor eax, eax
	mov ax, instruction
	shr ax, 8
	and ax, 1b
	mov ebx, groups[eax * TYPE groups]
	call ebx
	ret
doOperate ENDP

groupOne PROC
	.IF bit1
		call clearAccumulator
		.ENDIF
	.IF bit2
		call clearLink
		.ENDIF
	.IF bit3
		call onesComplementAccumulator
		.ENDIF
	.IF bit4
		call complementL
		.ENDIF
	.IF bit8
		call increment
		.ENDIF
	.IF bit7
		.IF (bit5 || bit6)
			.IF bit5
				call rotateRightTwice
				.ENDIF
			.IF bit6
				call rotateLeftTwice
				.ENDIF
			jmp done
		.ELSE
			call bitSwap
			.ENDIF
		.ENDIF
	.IF bit5
		call rotateRight
		.ENDIF
	.IF bit6
		call rotateLeft
		.ENDIF
done:
	ret
groupOne ENDP

groupTwo PROC
	.IF bit2
		call skipIfACLessThanZero
		.ENDIF
	.IF bit3
		call skipIfACZero
		.ENDIF
	.IF bit4
		call skipIfLNotZero
		.ENDIF
	.IF bit5
		not skip
		.ENDIF
	.IF skip
		inc programCounter
		.ENDIF
	.IF bit1
		call clearAccumulator
		.ENDIF
	.IF bit6
		call orACFrontPanel
		.ENDIF
	.IF bit7
		call halt
		.ENDIF
	ret
groupTwo ENDP