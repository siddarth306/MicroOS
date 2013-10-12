

; Printing a string in Protected Mode

[ bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm :
                pusha
                mov edi , VIDEO_MEMORY                      ; Set edx to the start of vid mem.
print_string_pm_loop :
                mov al , [ ebx ]                            ; Store the char at EBX in AL
                mov ah , WHITE_ON_BLACK                     ; Store the attributes in AH
                cmp al , 0                                  ; Check if ( al == 0) (0 denotes end of string)
                je print_string_pm_done                     ; If al=0 jump to done (0 denotes end of string)
                mov word [ edi ] , ax            
                inc ebx
                inc edi
                inc edi
                jmp print_string_pm_loop                    ; loop around to print the next char.
    
print_string_pm_done :
                popa
                ret
        


