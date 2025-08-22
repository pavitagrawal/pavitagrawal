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
	LDR R4, =5
	LDR R0, =DST
	LDR R1, =DST+36
Up
	LDR R2, [R0]
    LDR R3, [R1]
    STR R2, [R1], #-4
    STR R3, [R0], #4
	SUBS R4, #1
	BNE Up
STOP B STOP

    AREA mydata, DATA, READWRITE
DST DCD 0x12345678, 0x23095340, 0x34567890, 0xABCDE123, 0x123ABCDE, 0xFEDCBA12, 0x89FEDCBA, 0x24ACDF67, 0xDCBF2345, 0x567783AC
    END