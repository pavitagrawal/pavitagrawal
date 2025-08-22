	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	LDR R2, [R0]
	STR R2, [R1]
	LDR R3, [R0, #4]!
	STR R3, [R1, #4]!
	LDR R4, [R0, #4]!
	STR R4, [R1, #4]!
	LDR R5, [R0, #4]!
	STR R5, [R1, #4]!
	LDR R6, [R0, #4]!
	STR R6, [R1, #4]!
	LDR R7, [R0, #4]!
	STR R7, [R1, #4]!
	LDR R8, [R0, #4]!
	STR R8, [R1, #4]!
	LDR R9, [R0, #4]!
	STR R9, [R1, #4]!
	LDR R10, [R0, #4]!
	STR R10, [R1, #4]!
	LDR R11, [R0, #4]!
	STR R11, [R1, #4]!
STOP B STOP
SRC DCD 0x12345678, 0x23095340, 0x34567890, 0xABCDE123, 0x123ABCDE, 0xFEDCBA12, 0x89FEDCBA, 0x24ACDF67, 0xDCBF2345, 0x567783AC
	AREA mydata, DATA, READWRITE
DST DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END