	GET led.h
	GET buzzer.h
	GET switches.h

	
	.data
state:	.word 0
	

	
	.text
jt:	.word default	;jt[0]
	.word case1	;jt[1]
	.word case2	;jt[2]
	.word case3	;jt[3]
	.word case4	;jt[4]

	
	.global state_advance
state_advance:
	;; checking for default state
	cmp #5, &state	;state - 5
	jnc default

	mov &state,r12
	add r12, r12
	mov jt(r12), r0

	;; switch table

case1:	mov #1,red_on
	mov #0,green_on
	call led_update
	mov #7644, r12
	call buzzer_set_period
	jmp end

case2:	mov #0,red_on
	mov #1,green_on
	call led_update
	mov #5102, r12
	call buzzer_set_period
	jmp end			

case3:	mov #1,red_on
	mov #1,green_on
	call led_update
	mov #4049, r12
	call buzzer-set_period
	jmp end

case4:	mov #0,red_on
	mov #0,green_on
	call led_update
	mov #5405, r12
	call buzzer_set_period
	jmp end

default:
	mov #1,red_on
	mov #1,green_on
	call led_update
	mov #6000, r12
	call buzzer_set_period
	jmp end

end:	pop r0
	
