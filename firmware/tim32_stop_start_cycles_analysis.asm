; Analysis of the number of clock cycles between stop and start of the 32-bit timer, extracted from the *.lss file.
; Compare with AVR Instruction Set Manual.
; Phillip Durdaut, 2020

;/* stop counter */
;tim32_stop();
632:	67 d0       	rcall	.+206    		; 0x702 <tim32_stop>										; 3 cycles

		;void tim32_stop(void)
		;TCCR1B = 0;
		702:	10 92 81 00 	sts	0x0081, r1	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>				; 2 cycles
		706:	08 95       	ret																			; 4 cycles



;/* get number of ticks from 32-bit counter */
;main_tim32_ticks = tim32_get_ticks();
634:	81 d0       	rcall	.+258    		; 0x738 <tim32_get_ticks>									; 3 cycles

		;uint32_t tim32_get_ticks(void)
		;return TCNT1 + tim32_ticks;
		738:	20 91 84 00 	lds	r18, 0x0084	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>				; 2 cycles
		73c:	30 91 85 00 	lds	r19, 0x0085	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>				; 2 cycles
		740:	80 91 77 01 	lds	r24, 0x0177	; 0x800177 <tim32_ticks>									; 2 cycles
		744:	90 91 78 01 	lds	r25, 0x0178	; 0x800178 <tim32_ticks+0x1>								; 2 cycles
		748:	a0 91 79 01 	lds	r26, 0x0179	; 0x800179 <tim32_ticks+0x2>								; 2 cycles
		74c:	b0 91 7a 01 	lds	r27, 0x017A	; 0x80017a <tim32_ticks+0x3>								; 2 cycles
		750:	bc 01       	movw	r22, r24															; 1 cycle
		752:	cd 01       	movw	r24, r26															; 1 cycle
		754:	62 0f       	add	r22, r18																; 1 cycle
		756:	73 1f       	adc	r23, r19																; 1 cycle
		758:	81 1d       	adc	r24, r1																	; 1 cycle
		75a:	91 1d       	adc	r25, r1																	; 1 cycle
		75c:	08 95       	ret																			; 4 cycles

		670:	6b 01       	movw	r12, r22															; 1 cycle	
		672:	7c 01       	movw	r14, r24															; 1 cycle



;/* reset 32-bit counter */
;tim32_clear();	
646:	60 d0       	rcall	.+192    		; 0x708 <tim32_clear>										; 3 cycles

		;void tim32_clear(void)
		;TCNT1 = 0;
		708:	10 92 85 00 	sts	0x0085, r1	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>				; 2 cycles
		70c:	10 92 84 00 	sts	0x0084, r1	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>				; 2 cycles
		;tim32_ticks = 0;
		710:	10 92 77 01 	sts	0x0177, r1	; 0x800177 <tim32_ticks>									; 2 cycles
		714:	10 92 78 01 	sts	0x0178, r1	; 0x800178 <tim32_ticks+0x1>								; 2 cycles
		718:	10 92 79 01 	sts	0x0179, r1	; 0x800179 <tim32_ticks+0x2>								; 2 cycles
		71c:	10 92 7a 01 	sts	0x017A, r1	; 0x80017a <tim32_ticks+0x3>								; 2 cycles
		720:	08 95       	ret																			; 4 cycles
	 

	 
;/* start counter */	 
;tim32_start();
648:	58 d0       	rcall	.+176    		; 0x6fa <tim32_start>										; 3 cycles

		;void tim32_start(void)
		;TCCR1B = 0x01;
		 714:	81 e0       	ldi	r24, 0x01	; 1															; 1 cycle
		 716:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>				; 2 cycles
		 71a:	08 95       	ret																			; 4 cycles
