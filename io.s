global outb

; Sposta Cursore (Visibile a C tramite io.h)

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret
