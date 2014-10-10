; Name:Wendi Tang
; GTID:903088141
;Calculate the value of a expression consisting of single positive digits, * or +

; Main
; Do not edit this function!

.orig x3000

	LD R6, STACK	; Initialize the stack

	LEA R0, STRING	; R0 = &str[0]
	ADD R1, R0, 0

SL_LOOP	LDR R2, R1, 0	; \ R1 = strlen(str)
	BRz SL_END	; |
	ADD R1, R1, 1	; |
	BR SL_LOOP	; |
SL_END	NOT R2, R0	; |
	ADD R2, R2, 1	; |
	ADD R1, R1, R2	; /

	ADD R6, R6, -2	; \ R0 = eval(str, len)
	STR R0, R6, 0	; |
	STR R1, R6, 1	; |
	LD R2, EVALPTR	; |
	JSRR R2		; |
	LDR R0, R6, 0	; |
	ADD R6, R6, 3	; /

	ST R0, ANS
	HALT

STACK	.fill xf000
ANS	.fill -1
EVALPTR	.fill EVAL
STRING	.stringz "1*2*5+3*4+8*9"
	.blkw 200


	; Write your function here

	EVAL ADD R6,R6,-4	;Move SP to leave space for return value,Ret Addr, Old FP
	STR R5,R6,1		;store R5(Old FP)
	ADD R5,R6,0		;FP = SPs
	STR R7,R5,2		;store R7(Ret Addr)

	;Allocate spaces for registers and locals
	ADD R6,R6,-5		;\
	STR R0,R5,-5		;|
	STR R1,R5,-4		;|
	STR R2,R5,-3		;/

				;FP-2 = i
				;FP-1 = left
				;FP-0 = right
				;FP+4 = char* string address
				;FP+5 = length
				;R0 = i
				;R1 = char
				;R2 = char* string address
				;R3 temp
				;R4 temp

	AND R0,R0,0		;i = 0
	LDR R2,R5,4		;R2 = str
	WHILE1 LDR R1,R5,5	;R1(temp) = length
	NOT R3,R1		;\R3 = -length
	ADD R3,R3,1		;/
	ADD R3,R0,R3		;R3 = i -length
	BRzp SKIPWHILE1		;if(i >= length) skip while loop 1

	ADD R3,R2,R0		;R3 = str + i
	LD  R4,PLUS		;R4 = '+'
	NOT R4,R4		;\Negate R4('+')
	ADD R4,R4,1		;/
	LDR R1,R3,0		;R1 = *(str + i)
	ADD R3,R1,R4		;R3 = *(str + i) - '+'
	BRnp SKIPPLUS		;if(*(str + 1) != '+') skip plus operation

	;JSR GETLR		;calculate left and right
	;left = eval(str, i)
	ADD R6, R6, -2		; \
	STR R2, R6, 0		; |
	STR R0, R6, 1		; |
	JSR EVAL		; |
	LDR R3, R6, 0		; |
	STR R3, R5, -1		; |Store left
	ADD R6, R6, 3		; /
	
	;right = eval(str + i + 1, len -i - 1)
	ADD R6, R6, -2		; \ 
	ADD R3, R2, R0		; | R3 = str + i
	ADD R3, R3, 1		; | R3 = str + i + 1
	STR R3, R6, 0		; | Push first variable 
	NOT R3, R0		; | R3 = -i -1
	LDR R1,R5,5		; | R1 = length
	ADD R3,R3,R1		; | R3 = length - i -1
	STR R3, R6, 1		; | Push second variable
	JSR EVAL		; |
	LDR R3, R6, 0		; |
	STR R3, R5, 0		; |Store right
	ADD R6, R6, 3		; /

	LDR R3,R5,-1		;R3 = left
	LDR R4,R5,0		;R4 = right
	ADD R3,R3,R4		;R3 = left + right
	STR R3,R5,3		;Store return value
	BR LEAVING		;

	SKIPPLUS ADD R0,R0,1	;i++
	BR WHILE1

	SKIPWHILE1 AND R0,R0,0	;i = 0
	WHILE2 LDR R1,R5,5	;R1(temp) = length
	NOT R3,R1		;\R3 = -length
	ADD R3,R3,1		;/
	ADD R3,R0,R3		;R3 = i -length
	BRzp SKIPWHILE2		;if(i >= length) skip while loop 2

	ADD R3,R2,R0		;R3 = str + i
	LD  R4,TIMES		;R4 = '*'
	NOT R4,R4		;\Negate R4('*')
	ADD R4,R4,1		;/
	LDR R1,R3,0		;R1 = *(str + i)
	ADD R3,R1,R4		;R3 = *(str + i) - '*'
	BRnp SKIPTIMES		;if(*(str + 1) != '*') skip times operation
	
	;JSR GETLR		;calculate left and right
	;left = eval(str, i)
	ADD R6, R6, -2		; \
	STR R2, R6, 0		; |
	STR R0, R6, 1		; |
	JSR EVAL		; |
	LDR R3, R6, 0		; |
	STR R3, R5, -1		; |Store left
	ADD R6, R6, 3		; /
	
	;right = eval(str + i + 1, len -i - 1)
	ADD R6, R6, -2		; \ 
	ADD R3, R2, R0		; | R3 = str + i
	ADD R3, R3, 1		; | R3 = str + i + 1
	STR R3, R6, 0		; | Push first variable 
	NOT R3, R0		; | R3 = -i -1
	LDR R1,R5,5		; | R1 = length
	ADD R3,R3,R1		; | R3 = length - i -1
	STR R3, R6, 1		; | Push second variable
	JSR EVAL		; |
	LDR R3, R6, 0		; |
	STR R3, R5, 0		; |Store right
	ADD R6, R6, 3		; /

	LDR R3,R5,-1		;R3 = left
	LDR R4,R5,0		;R4 = right
	
	AND R1,R1,0		;Clear R1
	ADD R4,R4,0		;Test R4
	MUTI BRnz SKIPMUTI	;\ Muti, result is in R1
	ADD R1,R1,R3		;|
	ADD R4,R4,-1		;|
	BR MUTI			;/
	
	SKIPMUTI STR R1,R5,3	;Store result
	BR LEAVING		;

	SKIPTIMES ADD R0,R0,1	;i++
	BR WHILE2		;

	SKIPWHILE2 LDR R3,R2,0	;R3 = *str
	LD R4,ZERO		;R4 = '0'
	NOT R4,R4		;\Negate R4
	ADD R4,R4,1		;/
	ADD R3,R3,R4		;R3 =  *str - '0'
	STR R3,R5,3		;Store return value
	
	LEAVING LDR R0,R5,-5	;\Restore everything
	LDR R0,R5,-5		;|
	LDR R1,R5,-4		;|
	LDR R2,R5,-3		;/
	ADD R6,R5,0		;Move SP
	LDR R7,R5,2		;Load return address
	LDR R5,R5,1		;Load old FP
	ADD R6,R6,3		;Move SP
	RET


	PLUS	.stringz "+"
	TIMES	.stringz "*"
	ZERO	.Stringz "0"
.end
