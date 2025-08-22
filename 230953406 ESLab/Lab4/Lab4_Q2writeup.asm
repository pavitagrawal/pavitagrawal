    AREA RESET, DATA, READONLY ;Hex to ASCII
    EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
    ALIGN
    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler
Reset_Handler
    LDR R1, =HEX
    LDRB R2, [R1]
    LDR R4, =ASCII
    MOV R10, #2
UP
    AND R3, R2, #0x0F
    CMP R3, #9
    BCS NUMERIC
    ADD R3, R3, #0x07
NUMERIC
    ADD R3, R3, #0x37
    STRB R3, [R4], #1
    LSR R2, R2, #4
    SUBS R10, R10, #1
    BNE UP
STOP B STOP

    AREA mydata, DATA, READWRITE
HEX DCD 0xAF
ASCII DCD 0
    END