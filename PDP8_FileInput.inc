TITLE PDP8_FileInput					(PDP8_FileInput.inc)

INCLUDE macros.inc

.data
defaultFile BYTE "PDP8_Ram", 0
filenameMessage BYTE "Enter the file name.", 0
filename BYTE 80 DUP(0)
fileHandle HANDLE ?
fileOpenErrorMessage BYTE "Error opening file.", 0
counter WORD 0
fileError BYTE 0

.code
fileEntry PROC uses eax ebx edx
	call getFile
	xor ebx, ebx

load:
	mov bx, counter
	mov al, buffer[ebx * TYPE buffer]
	call writeToRam
	ret
fileEntry ENDP

getFile PROC uses ecx edx
	lea edx, defaultFile
	jmp open

filenameLoop:
	lea edx, filenameMessage
	call writeString
	call crlf
	call crlf
	lea edx, prompt
	call writeString
	lea edx, filename
	mov ecx, SIZEOF filename
	call readString
open:
	call openInputFile
	mov fileHandle, eax
	call errorCheck
	.IF fileError
		jmp filenameLoop
		.ENDIF
	ret
getFile ENDP

errorCheck PROC uses ecx edx
	.IF fileHandle == INVALID_HANDLE_VALUE
		call fileOpenError
		jmp done
		.ENDIF
	lea edx, buffer
	mov ecx, SIZEOF buffer
	call readFromFile
	jnc checkBufferSize
	call fileOpenError
	call closeFile

checkBufferSize:
	.IF fileHandle < SIZEOF buffer
		call fileOpenError
		.ENDIF

done:
	ret
errorCheck ENDP

fileOpenError PROC uses edx
	mov fileError, 1
	lea edx, fileOpenErrorMessage
	call writeString
	call crlf
	call crlf
	ret
fileOpenError ENDP