; Author: Wendi Tang
; GtId:903088141 

.orig x3000
		LD R0, K				;Load R0(K) from K			x3000
		AND R1,R1,0				;Clear R1(found)			x3001

		;while not found
		WHILELOOP ADD R1,R1,0			;Test R1				x3002
		BRnp STOP				;If isFound is true, stop		x3003
		
		ADD R0,R0,1				;k++					x3004
		ADD R2,R0,0				;R2(isPrime) = k			x3005
		AND R3,R3,0				;clear R3				x3006
		ADD R3,R3,1				;R3(i) = 1				x3007
		
	
		FORLOOP ADD R3,R3,1			;i++ 					x3008
		ADD R4,R3,R3				;R4(2i)=R3+R3				x3009
		JSR NEGATER4				;Negate R4				x300A
		ADD R4,R4,R0				;Test K-2i				x300B
		BRnz SKIP				;					x300C
		ADD R2,R2,0				;Test isPrime				x300D
		BRz SKIP				;					x300E
		
		ADD R4,R3,0				;R4=R3(i)				x300F
		JSR NEGATER4				;Negate R4				x3010

		ADD R2,R0,0				;Reset R2(isPrime) = k before %		x3011
		SUBSTRACT ADD R5,R2,R4			;R5 = R2-R4				x3012
		BRn FORLOOP				;					x3013
		ADD R2,R5,0				;isPrime = k%i				x3014
		BR SUBSTRACT				;					x3015

		SKIP ADD R1,R2,0			;found = isPrime;			x3016
		BR WHILELOOP				;					x3017
		
	
		STOP ST R0,NEXTPRIME			;Store R0 in NEXTPRIME			x3018
		HALT					;Stop the program			x3019

		NEGATER4 NOT R4,R4			;Flip all bits in R4			x301A
		ADD R4,R4,1				;2's complement				x301B
		RET					;Return to previous address		x301C
		


;put numbers in the memory
		K		.fill	992		; K					
		NEXTPRIME	.blkw 	1		; store your answer here					
.end
