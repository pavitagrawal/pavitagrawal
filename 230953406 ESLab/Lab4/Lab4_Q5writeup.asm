	AREA RESET, DATA, READONLY ;ASCII to HEXA
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler

	LDR R1, =ASCII    ; Load address of ASCII input string
	LDR R4, =HEX      ; Load address of where to store the resulting hex byte
	MOV R10, #2       ; Initialize counter for processing two ASCII chars

UP
	LDRB R2, [R1], #1  ; Load an ASCII character from the string and increment address
	CMP R2, #'9'      ; Check if the character is a digit '0'-'9'
	BLS NUMERIC_CHAR  ; If it is a digit, branch to NUMERIC_CHAR
	SUB R2, R2, #7    ; If it is 'A'-'F', subtract 7 to adjust its value

NUMERIC_CHAR
	SUB R2, R2, #'0'  ; Subtract ASCII '0' to get the numeric value
	CMP R10, #2      ; Check if this is the first character
	BEQ FIRST_CHAR   ; If it is the first character, branch to FIRST_CHAR
	ORR R3, R3, R2   ; If it is the second character, combine with the first (already in R3)
	B STORE_HEX      ; Branch to store the combined hex byte

FIRST_CHAR
	MOV R3, R2, LSL #4 ; For the first character, shift its value left by 4 bits to prepare for combining
	SUBS R10, R10, #1  ; Decrement the counter
	BNE UP            ; If not finished with two characters, branch back to UP

STORE_HEX
	STRB R3, [R4]      ; Store the resulting hex byte

STOP B STOP

	AREA mydata, DATA, READWRITE
ASCII DCB "AF"    ; Input ASCII string (e.g., "AF" for 0xAF)
HEX   DCD 0        ;  Storage for the resulting hex byte
	END