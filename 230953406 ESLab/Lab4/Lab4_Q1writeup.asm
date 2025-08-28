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
    LDR R0, =NUM1
    LDR R1, =NUM2
    LDR R2, =GCD
    LDR R3, [R0]
    LDR R4, [R1]
GCD_Loop
    CMP R3, R4
    BEQ GCD_Final
    CMP R3, R4
    BGT A_Greater
    BLT B_Greater
A_Greater
    SUBS R3, R3, R4
    B GCD_Loop
B_Greater
    SUBS R4, R4, R3
    B GCD_Loop
GCD_Final
    STR R3, [R2]
STOP B STOP

    AREA mydata, DATA, READWRITE
NUM1 DCD 0x64
NUM2 DCD 0x08
GCD DCD 0
    END