;;==============================================
;; NAME:Wendi Tang
;;==============================================
;Traverse through an array

.orig x3000

	LEA R0, ARRAY		; R0 is the array address

	; Start your code here
	ADD R1,R0,0		; R1(min) = array[0] address
	AND R2,R2,0 		; R2(sum) = 0
	AND R3,R3,0		; R3(length) = 0
	AND R4,R4,0		; R4(i) = 0

	WHILE ADD R5,R0,R4	; R5 = array[i] address
	LDR R5,R5,0		; R5 = array[i] value
	ADD R6,R5,1		;\ If(array[i] = -1)
	BRz END			;/ goto END
	;else
	LDR R6,R1,0		;R6 = min value
	NOT R7,R6		;\R7 = -min
	ADD R7,R7,1		;/
	ADD R7,R5,R7		;R7 = array[i] - min
	BRzp SKIPSWITCH		;
	ADD R7,R0,R4		;R7 = array[i] address
	ADD R1,R7,0		;min address = array[i] address

	SKIPSWITCH ADD R2,R2,R5	;sum = sum + array[i]
	ADD R4,R4,1		;i++
	BR WHILE		;
	
	END ADD R3,R4,0		;length = i
	LDR R6,R1,0		;R6 = min value
	ST  R6,MIN_VAL		;Store min value
	ST  R2,SUM		;Store sum
	ST  R3,LENGTH		;Store length
	HALT			;


MIN_VAL .fill 0			; Store the mininum value in the array at this label
SUM	.fill 0			; Store the sum of all of the entries in the array at this label
LENGTH	.fill 0			; Store the length of the array at this label

ARRAY	.fill 1			; The first element of the array
	.fill 3
	.fill 7
	.fill 4
	.fill 2
	.fill 9
	.fill 30
	.fill 3
	.fill 4			; The last element of the array
	.fill -1		; -1 will follow the last element of the array	


.end
