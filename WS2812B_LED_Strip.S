;---------------
; Assembly Code
;---------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"
;------------------------
.global PORTDbyte
.global ColorByte
;====================================================================
PORTDbyte:
;---------
    MOV   R30, R24      ;receive PORTD byte via R24 (to set DIN HIGH)
    LDI   R31, 0        ;R31 = 0 (to set DIN LOW)
    RET                 ;return to calling function in C++ sketch
;====================================================================
ColorByte:
    RCALL Logic1  
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RCALL Logic1
    RET

bob:
;---------
    LDI   R17, 8        ;setup counter to cover 8 bits
agn:ROL   R24           ;store MSB in carry flag
    BRCS  logic1        ;& jump to label if C flag is set (logic 1)
    RCALL Logic0        ;otherwise output logic 0
    OUT   PORTE, R31
    JMP   ext           ;jump to label
logic1:
    RCALL Logic1        ;output logic 1
    OUT   PORTE, R31
ext:DEC   R17           ;decrement counter by 1
    BRNE  agn           ;jump & repeat if counter not zero
    RET                 ;return to calling function in C++ sketch
;====================================================================
Logic0:
;--------------------------NOP = 1 CLK cycle = 0.0625us
    ;0.40us high pulse (6T) now this needs to be 0.3us so 4.8T
    ;----------------------
    OUT   PORTE, R30    ;set DIN pin HIGH
    NOP
    NOP
    NOP
    NOP
    ;NOP
    ;----------------------
    ;0.85us low pulse (14T) now this needs to be 0.9us so 14.4T
    ;----------------------
    OUT   PORTE, R31    ;set DIN pin LOW
    NOP
    NOP
    NOP
    NOP
    ;NOP
    ;NOP
    ;NOP
    ;NOP
    ;NOP
    ;NOP
    ;NOP ;this one didn't change
    ;----
    RET
;====================================================================
Logic1:
;---------------------------
    ;0.80us high pulse (13T) now this needs to be 0.9 so 14.4T
    ;-----------------------
    OUT   PORTE, R30 ;high
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    ;NOP
    ;NOP
    ;NOP
    ;NOP ;this one was added
    ;---------------------
    ;0.45us low pulse (7T) now this needs to be 0.3us so 4.8T
    ;---------------------
    OUT   PORTE, R31    
    ;NOP
    ;NOP
    ;NOP
    ;NOP
    ;----
    RET