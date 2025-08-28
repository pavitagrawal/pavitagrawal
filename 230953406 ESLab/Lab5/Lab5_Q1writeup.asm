	AREA RESET, DATA, READONLY ;Insertion Sort
    EXPORT __Vectors
__Vectors
    DCD 0x10001000
    DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
    LDR R0, =SRC          ; Load address of SRC array into R0
    MOV R1, #10           ; Array size (N) into R1
    MOV R2, #1            ; Outer loop counter 'i' (start from 1, second element)

OuterLoop
    CMP R2, R1            ; Compare i with N
    BGE Done              ; If i >= N, sorting is done
    ADD R5, R0, R2, LSL #2 ; R5 = address of arr[i]
    LDR R6, [R5]           ; R6 = key = arr[i]
    SUB R3, R2, #1        ; R3 = j = i - 1

InnerLoop
    CMP R3, #0            ; Compare j with 0
    BLT InsertKey          ; If j < 0, insert key at arr[0]
    ADD R8, R0, R3, LSL #2 ; R8 = address of arr[j]
    LDR R7, [R8]           ; R7 = arr[j]
    CMP R7, R6            ; Compare arr[j] with key
    BLE InsertKey          ; If arr[j] <= key, insert key at arr[j+1]
    ADD R9, R0, R3, LSL #2 ; R9 = address of arr[j]
    ADD R10, R0, R3, LSL #2 ; R10 = address of arr[j+1]
    STR R7, [R10, #4]      ; arr[j+1] = arr[j]
    SUB R3, R3, #1        ; j--
    B InnerLoop           ; Continue inner loop

InsertKey
    ADD R8, R0, R3, LSL #2 ; R8 = address of arr[j+1]
    STR R6, [R8, #4]       ; arr[j+1] = key
    ADD R2, R2, #1        ; i++
    B OuterLoop           ; Continue outer loop

Done
    B STOP
STOP B STOP

	AREA mydata, DATA, READWRITE
SRC DCD 0x00ABCDF, 0x0012345, 0x000DCEF, 0x0AB1234, 0x0001032, 0x21231223, 0x0023FE1A, 0x0AB564E, 0x0012345, 0xABCDE123
	END