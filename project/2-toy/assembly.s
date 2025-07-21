	.arch msp430g2553
	.p2align 1,0
	.text

	.global red_green
	.extern P1OUT

red_green:
	cmp #0, r12
	jeq red
	cmp #1, r12
	jeq green
	cmp #2, r12
	jeq both
	pop r0

red:
	bic #64, &P1OUT     	; Clear green (BIT6)
	bis #1, &P1OUT      	; Set red (BIT0)
	pop r0

green:

	bic #1, &P1OUT      	; Clear red
	bis #64, &P1OUT     	; Set green
	pop r0

both:
	bis #65, &P1OUT     	; Set both (BIT0 | BIT6)
	pop r0
