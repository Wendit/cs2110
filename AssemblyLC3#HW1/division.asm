; DO NOT ADD ANY LINES THAT BEGIN WITH @plugin OR YOU RISK GETTING A ZERO FOR THIS PART.

; Author: Wendi Tang
; GtId:903088141 

.orig x3000
		LD R0, U				; U				x3000
		LD R1, V				; V				x3001
		LD R2,QUOTIENT				;Load R4 from QUOTIENT		x3002

		ADD R1,R1,0				;Change cc			x3003
		BRnp WHILELOOP				;If R1 is 0			x3004

		IVDEN AND R2,R2,0			;Set R2 to 0 			x3005
		AND R0,R0,0				;Set R0 to 0 			x3006
		ADD R2,R2,-1				;Set R2 to -1 			x3007
		ST R2,QUOTIENT				;Set QUTIENT to -1		x3008
		BR STOP					;BR to STOP to stop the program x3009


		WHILELOOP ADD R3,R1,0			;Copy R1 to R3 			x300A
		NOT R3,R3				;Flip all bits in R3 		x300B
		ADD R3,R3,1				;Make a 2's complement 		x300C
		ADD R4,R0,R3				;ADD R0 and R3 			x300D
		BRn STOP				;If R0 is smaller than R1,stop  x300E	
	
		ADD R0,R4,0				;Load R0 from R4		x300F
		ADD R2,R2,1				;Increment R2 			x3010
		ST R2,QUOTIENT				;Set QUTIENT to R2 		x3011
		BR WHILELOOP				;Branch to whileloop		x3012
		
		STOP ST R0,REMAINDER			;Set REMAINDER to R0 		x3013						
		HALT					;Stop program 			x3014

		; Change U and V to suit your needs
		U .fill 2932				; Initialize U 			
		V .fill 172				; Initialize V 			
		QUOTIENT .blkw 1			; Store your quotient here 	
		REMAINDER .blkw 1			; Store your remainder here 	
.end

