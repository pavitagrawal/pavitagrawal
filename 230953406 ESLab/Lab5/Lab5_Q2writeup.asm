;2.	Write an assembly program to find the factorial of a unsigned number using recursion.
	AREA    RESET, DATA, READONLY ;Factorial of a number using recursion
	EXPORT  __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
	ALIGN
	AREA MyCode, CODE, READONLY
	EXPORT Reset_Handler
	ENTRY

Reset_Handler
    LDR R0, =NUM
    LDR R1, [R0]
    BL  fact
    LDR R0, =RESULT
    STR R2, [R0]
STOP B STOP
fact
    CMP R1, #1
    BEQ exit_fact
    PUSH {lr}
    PUSH {R1}
    SUB R1, R1, #1
    BL fact
    POP {R1}
    POP {lr} 
    MUL R2, R1, R2
    BX lr 

exit_fact
    MOV R2, #1
    BX lr

	AREA MyData, DATA, READWRITE
NUM DCD 5
RESULT DCD 0
	END