TITLE PDP8_Interface					(PDP8_Interface.inc)

INCLUDE PDP8_FileInput.inc
INCLUDE PDP8_RawInput.inc

.data
welcomeMessage1 BYTE "  MASM Assembly PDP-8 Simulator", 0
welcomeMessage2 BYTE "---------------------------------", 0
welcomeMessage3 BYTE "Entry Mode 1: Manual instructions by line (not yet functional).", 0
welcomeMessage4 BYTE "Entry Mode 2: Pull from file (default is PDP8_Ram.txt) (not functional).", 0
welcomeMessage5 BYTE "Entry Modes not functional! Pulling hard-coded instructions...", 0
entry1Selected BYTE "Entry mode [1] selected.", 0
entry2Selected BYTE "Entry mode [2] selected.", 0
prompt BYTE "--> ", 0
input BYTE 2 DUP(0)
buffer BYTE 5000 DUP(0)
inputErrorMessage BYTE "Input not recognized.", 0
haltFrontMessage BYTE "Program halted! PC at location ", 0
haltBackMessage BYTE ". Terminating on keypress...", 0

.code
interface PROC uses ecx edx
	call welcomeMessage

;promptLoop:
;	lea edx, prompt
;	call writeString
;	lea edx, input
;	mov ecx, SIZEOF input
;	call readString
;	.IF input == "1"
;		lea edx, entry1Selected
;		call writeString
;		call crlf
;		call manualEntry
;	.ELSEIF input == "2"
;		lea edx, entry2Selected
;		call writeString
;		call crlf
;		call fileEntry
;	.ELSE
;		call inputError
;		jmp promptLoop
;		.ENDIF
	call start
	ret
interface ENDP

welcomeMessage PROC uses edx
	lea edx, welcomeMessage1
	call writeString
	call crlf
	lea edx, welcomeMessage2
	call writeString
	call crlf
	call crlf
	lea edx, welcomeMessage3
	call writeString
	call crlf
	lea edx, welcomeMessage4
	call writeString
	call crlf
	call crlf
	lea edx, welcomeMessage5
	call writeString
	call crlf
	call crlf
	ret
welcomeMessage ENDP

inputError PROC
	lea edx, inputErrorMessage
	call writeString
	call crlf
	call crlf
	ret
inputError ENDP

haltMessage PROC uses eax edx
	xor eax, eax
	lea edx, haltFrontMessage
	call writeString
	mov ax, programCounter
	call writeDec
	call crlf
	call waitMsg
	ret
haltMessage ENDP