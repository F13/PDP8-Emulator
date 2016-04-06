TITLE PDP8_Instructions					(PDP8_Instructions.asm)

.code
accumulatorAnd PROC uses eax ebx
	xor ebx, ebx
	mov bx, effectiveAddress
	mov ax, ram[ebx * TYPE ram]
	and accumulator, ax
	ret
accumulatorAnd ENDP

twosComplementAdd PROC uses eax ebx
	xor ebx, ebx
	mov bx, effectiveAddress
	mov ax, ram[ebx * TYPE ram]
	add accumulator, ax
	ret
twosComplementAdd ENDP

incrementSkipIfZero PROC uses eax
	xor eax, eax
	mov ax, effectiveAddress
	inc ram[eax * TYPE ram]
	.IF ram[eax * TYPE ram] == 0
		inc programCounter
		.ENDIF
	ret
incrementSkipIfZero ENDP

depositAccumulator PROC uses ebx edx
	xor edx, edx
	mov dx, effectiveAddress
	mov bx, accumulator
	call writeToRam
	mov accumulator, 0
	ret
depositAccumulator ENDP

jumpToSubroutine PROC uses eax ebx edx
	xor ebx, ebx
	xor edx, edx
	mov bx, programCounter
	inc bx
	mov dx, effectiveAddress
	call writeToRam
	dec bx
	mov ax, ram[ebx * TYPE ram]
	dec ax
	mov programCounter, ax
	ret
jumpToSubroutine ENDP

jump PROC uses eax
	xor eax, eax
	mov ax, ram[ebx * TYPE ram]
	mov programCounter, ax
	ret
jump ENDP

ioTransfer PROC
	nop
	ret
ioTransfer ENDP

operate PROC
	call startOperate
	ret
operate ENDP

writeToRam PROC uses edi
	;writes WORD in bx to ram location edx
	xor edi, edi
	lea edi, ram							;put address of ram into DI
	shl edx, 1							;double edx because ram is in WORDs
	add edi, edx							;move to position			
	mov [edi], bx			
	ret
writeToRam ENDP