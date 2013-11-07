[ org 0 x7c00 ]
mov [ BOOT_DRIVE ] , dl ; BIOS stores our boot drive in DL , so it ’s
mov bp , 0x8000
mov sp , bp
mov bx , 0x9000
mov dh , 5
mov dl , [ BOOT_DRIVE ]
call disk_load
mov dx , [0x9000 ]
call print_hex
mov dx , [0x9000 + 512] ; Also , print the first word from the
call print_hex
jmp $
%include "print/print_string.asm"
%include "hex/print_hex.asm"
%include "disk_load.asm"
BOOT_DRIVE : db 0
times 510 -($-$$) db 0
dw 0xaa55
times 256 dw 0xdada
times 256 dw 0xface