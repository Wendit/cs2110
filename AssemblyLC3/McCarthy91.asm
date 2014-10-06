;Wendi Tang
;10/6/2014
.orig x3000

	LD R6, STACK
	LD R0, VAL

	
	STR R0,R6,0	;Pass in parameter
	JSR MC91	;Jump to MC91
	LDR R0,R6,0	;Load the anwser
	ST R0, ANS
	HALT

	STACK	.fill xF000
	VAL	.fill -30
	ANS	.blkw 1

	; Finish this function!
	MC91 ADD R6,R6,-4;
	BP STR R5,R6,1 	;Store old FP
	ADD R5,R6,0	;FP = SP
	STR R7,R6,2	;Store return address	
	ADD R6,R6,-3	;Move SP
			;FP = x
	STR R0,R5,-1	;\Store registers
	STR R1,R5,-2	;|
	STR R2,R5,-3	;/

	LDR R0,R5,4	;Load n
	ADD R1,R0,-15	;\R1 = n-100
	ADD R1,R1,-15	;|
	ADD R1,R1,-15	;|
	ADD R1,R1,-15	;|
	ADD R1,R1,-15	;|
	ADD R1,R1,-15	;|
	ADD R1,R1,-10	;/
	BRnz ELSE	;if(n - 100 <= 0) else
	ADD R0,R0,-10	;\put return in R5+3
	STR R0,R5,3	;/
	BR LEAVING	;

	;else
	ELSE ADD R1,R0,11;x = n + 11
	
	STR R1,R6,0	;Pass in parameter
	JSR MC91	;Jump to MC91
	JSR MC91	;Jump to MC91
	LDR R1,R6,0	;
	STR R1,R5,3	;
	BR LEAVING	;
	

	LEAVING LDR R0,R5,-1;\Load registers
	LDR R1,R5,-2	;|
	LDR R2,R5,-3	;/
	ADD R6,R5,0	; SP = FP
	LDR R7,R5,2	;Load return address
	LDR R5,R5,1	;Load return value
	ADD R6,R6,3	;R6 = return value
	RET

.end
