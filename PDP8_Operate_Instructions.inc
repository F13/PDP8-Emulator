TITLE PDP8_Operate_Instructions			(PDP8_Operate_Instructions.inc)

.data
linkMask WORD 1111000000000000b
accumulatorMask WORD 0000111111111111b
tempStorage WORD 0

.code
clearAccumulator PROC
	mov accumulator, 0
	ret
clearAccumulator ENDP

clearLink PROC
	mov link, 0
	ret
clearLink ENDP

onesComplementAccumulator PROC
	not accumulator
	ret
onesComplementAccumulator ENDP

complementL PROC
	not link
	ret
complementL ENDP

increment PROC uses eax
	xor eax, eax
	mov ax, accumulator
	inc ax
	and ax, linkMask
	shr ax, 15
	mov link, al
	inc accumulator
	mov ax, accumulator
	and ax, accumulatorMask
	mov accumulator, ax
	ret
increment ENDP
	
rotateRight PROC uses eax
	mov ax, accumulator
	ror ax, 1
	and ax, linkMask
	shr ax, 15
	mov link, al
	mov ax, accumulator
	ror ax, 1
	and ax, accumulatorMask
	mov accumulator, ax
	ret
rotateRight ENDP

rotateLeft PROC uses eax
	mov ax, accumulator
	rol ax, 1
	shr ax, 12
	mov link, al
	mov ax, accumulator
	rol ax, 1
	.IF link
		inc ax
		.ENDIF
	and ax, accumulatorMask
	mov accumulator, ax
	ret
rotateLeft ENDP

rotateRightTwice PROC uses eax
	mov ax, accumulator
	and ax, 11b
	shl ax, 10
	mov tempStorage, ax
	mov ax, accumulator
	shr ax, 2
	or ax, tempStorage
	mov accumulator, ax
	mov ax, tempStorage
	shr ax, 1
	mov link, al
	ret
rotateRightTwice ENDP

rotateLeftTwice PROC uses eax
	mov ax, accumulator
	and ax, 110000000000b
	shr ax, 10
	mov tempStorage, ax
	mov ax, accumulator
	shl ax, 2
	and ax, accumulatorMask
	or ax, tempStorage
	mov accumulator, ax
	mov ax, tempStorage
	and ax, 1b
	mov al, link
	ret
rotateLeftTwice ENDP

bitSwap PROC uses eax ebx
	mov ax, accumulator
	mov bx, accumulator
	shr bx, 6
	shl ax, 6
	or ax, bx
	mov ax, accumulator
	ret
bitSwap ENDP

skipIfACLessThanZero PROC
	.IF accumulator < 0
		mov skip, 1
		.ENDIF
	ret
skipIfACLessThanZero ENDP

skipIfACZero PROC
	.IF accumulator == 0
		mov skip, 1
		.ENDIF
	ret
skipIfACZero ENDP

skipIfLNotZero PROC
	.IF link != 0
		mov skip, 1
		.ENDIF
	ret
skipIfLNotZero ENDP

orACFrontPanel PROC
	nop
	ret
orACFrontPanel ENDP

halt PROC
	mov halted, 1
	ret
halt ENDP