ASSUME CS:CODE, DS:DATA
DATA SEGMENT
  str DB "hello world, this is some test string$"
  substr DB "is$"
  found DB "Substring found$"
  notFound DB "Substring not found$"
DATA ENDS
CODE SEGMENT
  START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    LEA BX, str

  FIND:
    MOV SI, BX
    LEA DI, substr

  CHECK:
    MOV DL, [DI]
    INC DI
    CMP DL, "$"
    JE FOUND
    MOV AL, [SI]
    INC SI
    CMP AL, "$"
    JE NOT_FOUND
    CMP AL, DL
    JE CHECK
    INC BX
    JMP FIND

  NOT_FOUND:
    LEA DX, notFound
    JMP CLEANUP

  FOUND:
    LEA DX, found
    JMP CLEANUP

  CLEANUP:
    MOV AH, 09H
    INT 21H
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
