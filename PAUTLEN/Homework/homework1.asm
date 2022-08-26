segment .data
    _err_msg db "ERROR. The divisor can't be 0", 0

segment .bss
    _num1 resd 1
    _num2 resd 1

segment .text

global main
extern scan_int, print_string, print_int

main:
    ; Scans the first integer number
    push dword _num1
    call scan_int
    add esp, 4

    ; Scans the second integer number
    push dword _num2
    call scan_int
    add esp, 4
    
    ; If num2 = 0 jump to show the error message
    mov eax, [_num2]
    cmp eax, 0
    je _err

    ; If not, perform the integer division num1/num2
    mov edx, 0
    mov eax, [_num1]
    mov ecx, [_num2]
    idiv ecx

    ; Prints the result of the division
    push eax
    call print_int
    add esp, 4
    ret

_err:
    mov eax, _err_msg
    push eax
    call print_string
    add esp, 4
    ret
