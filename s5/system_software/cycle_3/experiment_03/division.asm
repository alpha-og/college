ASSUME CS:CODE, DS:DATA
DATA SEGMENT
  num1 DW 1234H
  num2 DB 56H
  quotient DW ?
  remainder DW ?
DATA ENDS
CODE SEGMENT
  START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    MOV AX, num1
    DIV num2
    MOV quotient, AX
    MOV remainder, DX
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
