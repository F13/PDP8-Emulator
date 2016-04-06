TITLE PDP8_RawInput						(PDP8_RawInput.inc)

.data
rawEntryMessage BYTE "Enter instructions (in binary) by line. End with DONE.", 0
rawInput BYTE 12 DUP(0)

.code
manualEntry PROC
	call startManualEntryMessage
	call rawInputLoop
	ret
manualEntry ENDP

rawInputLoop PROC
	lea edx, prompt
	call writeString
	lea edx, rawInput
	mov ecx, SIZEOF rawInput
	call readString
	ret
rawInputLoop ENDP

startManualEntryMessage PROC
	lea edx, rawEntryMessage
	call writeString
	call crlf
	call crlf
	ret
startManualEntryMessage ENDP