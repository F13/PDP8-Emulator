TITLE PDP8_Extract						(PDP8_Extract.inc)

.data
instruction WORD 0
opCode BYTE 0
page0Bit BYTE 0
indirectBit BYTE 0
givenAddress WORD 0
effectiveAddress WORD 0

.code
extractVariables PROC uses eax
	call getInstruction
	mov eax, 111000000000b			;OP Code mask - hardcoded because single use for each variable
	and ax, instruction
	shr ax, 9
	mov opCode, al					;extract OP Code from instruction

	mov eax, 000100000000b
	and ax, instruction
	shr ax, 8
	mov page0Bit, al				;extract page-0 bit from instruction

	mov eax, 000010000000b
	and ax, instruction
	shr ax, 7
	mov indirectBit, al				;extract indirect bit from instruction

	mov eax, 000001111111b
	and ax, instruction
	mov givenAddress, ax			;extract given address from instruction

	call calculateEffectiveAddress
	ret
extractVariables ENDP

getInstruction PROC uses eax ebx
	xor eax, eax
	xor ebx, ebx
	mov bx, programCounter
	mov ax, ram[ebx * TYPE ram]
	mov instruction, ax
	ret
getInstruction ENDP

calculateEffectiveAddress PROC
	call checkPage0Bit
	call checkIndirectBit
	ret
calculateEffectiveAddress ENDP

checkPage0Bit PROC uses eax
	.IF page0Bit == 1
		mov ax, givenAddress
		mov effectiveAddress, ax
		
	.ELSE
		mov ax, programCounter
		and ax, 111110000000b
		or ax, givenAddress
		mov effectiveAddress, ax
		.ENDIF
	ret
checkPage0Bit ENDP

checkIndirectBit PROC uses eax
	.IF indirectBit == 1
		mov ax, [effectiveAddress]
		mov effectiveAddress, ax
		.ENDIF
	ret
checkIndirectBit ENDP