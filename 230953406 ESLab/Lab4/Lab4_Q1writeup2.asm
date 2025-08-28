    AREA RESET, DATA, READONLY ;GCD of 2 numbers
    EXPORT __Vectors
__Vectors
    DCD 0x10001000        
    DCD Reset_Handler    
    ALIGN
    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler
Reset_Handler
    LDR R0, =NUM1
    LDR R1, =NUM2
    LDR R2, [R0]
    LDR R3, [R1]
Up
    CMP R2, R3
	BEQ Down
	SUBPL R2, R3
	SUBMI R3, R2
	BNE Up
Down
    MOV R2, R3
STOP B STOP

    AREA mydata, DATA, READWRITE
NUM1 DCD 0x64
NUM2 DCD 0x08
GCD DCD 0
    END