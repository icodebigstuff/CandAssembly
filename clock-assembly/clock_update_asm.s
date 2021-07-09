.text
.global set_tod_from_secs
set_tod_from_secs:
### args are
### %edi = int time_of_day
### %rsi = tod_t *tod

    ##Block A: Check for Errors

    cmpl	$86400,%edi
	jg      .OUT
	cmpl    $0,%edi
	jl      .OUT


	##Bloch B: Calculation for hours

	cmpl $0,%edi
	je .ZERO #Label to deal with midnight hour

    movl    %edi,%eax           # eax now has time_of_day
        cqto                    # prep for division
    movl   $3600,%r10d
        idivl  %r10d            #int hours = time_of_day/3600;
        movl %eax,%r10d         #r10d has hours

    ##Block C: Calculations of Seconds and Minutes (eax will have minutes, ecx will have seconds)

.BODY:
    movl %eax,%ecx              #ecx has hours
    movl %edi,%eax              #eax has time of day
    imull $3600,%ecx            #hours*3600
    subl %ecx,%eax              #time_of_day = time_of_day -(hours*3600)

    movl %eax,%ecx              #ecx (seconds value) = time_of_day -(hours * 3600),
    cqto #prep for division
    movl $60,%r9d
    idivl %r9d                  #minute = sec/60;
    movl %eax,%ecx              #eax now has minutes
    jmp .OTHER


    #Block D: .Other label to ensure that times stay within bounds

.OTHER:
    cmpl $0,%r10d #if hours is equal to 0
    je .HR
    cmpl $12,%r10d #if hours is greater then 0
    jg .G_HR
    jmp .SUCCESS

    ##BLOCK E: Hours is Zero condition (sets values to 0 and 12 to hours)

.ZERO:
    movl $12,%r10d
    movl $0,%ecx
    movl $0,%edx
    movl $0,%r11d
    jmp .SUCCESS

    #Block F: Changes hours to 12 if 0

.HR:
    movl $12,%r10d #change hours to 12
    jmp .SUCCESS

    #Block G: Subtracts 12 from hours to keep it within range

.G_HR:
    subl $12, %r10d
    jmp .SUCCESS

    #Block H: Sets values in struct and checks if PM needs to be set, if not returns

.SUCCESS:
        movl %r10d,0(%rsi) #tod->hours = time_of_day/3600;
        movl %ecx,2(%rsi)  #tod->minutes = (time_of_day -(hours * 3600))/60
        movl %edx, 4(%rsi) #tod->seconds = (time_of_day -(hours * 3600)) -(minute*60)
        cmpl $43200,%edi   #checks to see if time is pm
        jge .ISPM
        movl $0, %eax
        ret

    #Block I: Sets pm and returns
.ISPM:
    movb $1,6(%rsi)
    movl $0, %eax
        ret

    #Block J: Error block, sets eax to 1 and returns

.OUT:
    movl	$1, %eax
    ret

.data



my_array:                       # declare multiple ints in a row
        .int 0b0111111
        .int 0b0000110
        .int 0b1011011
        .int 0b1001111
        .int 0b1100110
        .int 0b1101101
        .int 0b1111101
        .int 0b0000111
        .int 0b1111111
        .int 0b1101111

state:                  #constant state variable
        .int 0b0000000

.text
.global set_display_bits_from_tod
set_display_bits_from_tod:

### args are
### %rsi = int *display
### %rdi = tod_t *tod

    #Block A: Check values to make sure they're in bounds

    movq    %rdi,%r9       # extract hours
	sarq    $0,%r9        # no shift needed
    andq    $0xFF,%r9       # r9 = hours, mask low byte
    cmpq $12,%r9
    jg .END
    cmpq $0,%r9
    jl .END
    movq    %rdi,%r10       # extract minutes
	sarq    $16,%r10         # move minutes to low order bits
    andq    $0xFF,%r10       # r10 = minutes
    cmpq $59,%r10
    jg .END
    cmpq $0,%r10
    jl .END
    movq    %rdi,%r11      # extract seconds
	sarq    $32,%r11          # move seconds to low order bits
    andq    $0xFF,%r11      # r11 = seconds
    cmpq $59,%r11
    jg .END
    cmpq $0,%r11
    jl .END





    #Block B: Calculations for min_ones and min_tens

    movq   %r10,%rax #tod.minutes in rax
    cqto
    movq    $10,%r11
        idivq   %r11

    movq %rdx,%r10 #min_ones in r10 (min_ones = tod.minutes %10)
    movq %r10,%r11 #min_ones in r11
    movq %rax,%rcx #min_tens in rcx (min_tens = (tod.minutes/10))


    #Block B: Calculations of hr_ones and hr_tens



    movq   %r9,%rax #tod.hours in rax
    cqto
    movq    $10,%r10
        idivq   %r10
    movq %rdx,%r9 #hr_ones in r9 (hr_ones = tod.hours%10)
    movq %rax,%r8 #hr_tens in r8 (hr_tens = tod.hours/10)


    #Block C: Load in array, state, and check to see if pm is needed

    leaq    my_array(%rip),%rdx #Pointer to head of array in rdx
    movl   state(%rip),%eax    # load state into register eax

    movq    %rdi,%r10       # extract ispm
	sarq    $48,%r10        # shift by 48 to the right needed
    andq    $0xFF,%r10       # r10 = tod.ispm, mask low byte
    cmpq $1,%r10
    je .SET1 #label to jump to set as pm
    cmpq $0,%r10
    je .SET2 #label to jump to set as am



    #Block D: Calc label to calculate shifts and uses bitwise or to change bits - leading number is kept (FOR AM use only)

.CALC:

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%r8,4),%eax   #bitwise or to set display hour-tens position. Equivalent to (arr[hr_tens] << 21)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%r9,4),%eax   #bitwuse or to set display hour-ones position. Equivalent to(arr[hr_ones] << 14)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%rcx,4),%eax  #bitwise or to set display minute-tens position. Equivalent to(arr[min_tens] << 7)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%r11,4),%eax  #bitwise or to set display minute-ones position. Equivalent to (arr[min_ones])

    jmp .FIN

    #Block E: Calc label to calculate shifts and uses bitwise or to change bits - leading number is kept (FOR PM use only)

.CALC2:
    sall    $8,%eax         #left shift state by 8 (sets PM)
    orl (%rdx,%r8,4),%eax   #bitwise or to set display hour-tens position. Equivalent to (arr[hr_tens] << 21)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%r9,4),%eax   #bitwise or to set display hour-ones position. Equivalent to(arr[hr_ones] << 14)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%rcx,4),%eax  #bitwise or to set display minute-tens position. Equivalent to(arr[min_tens] << 7)

    sall    $7,%eax         #left shift state by 7
    orl (%rdx,%r11,4),%eax  #bitwise or to set display minute-ones position. Equivalent to (arr[min_ones])

    jmp .FIN

    #Block F: SET3 label to set bits in the case that the leading zero needs to be removed (FOR PM use only)


.SET3:
    sall    $8,%eax         #left shifts state by 8
    orl $0,%eax             #turns to 0s

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%r9,4),%eax   #bitwise or to set display hour-ones position. Equivalent to(arr[hr_ones] << 14)

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%rcx,4),%eax  #bitwise or to set display minute-tens position. Equivalent to(arr[min_tens] << 7)

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%r11,4),%eax  #bitwise or to set display minute-ones position. Equivalent to (arr[min_ones])


    jmp .FIN

    #Block G: SET label to set bits in the case that the leading zero needs to be removed (FOR AM use only)

.SET:
    sall    $7,%eax         #left shifts state by 7
    orl $0,%eax             #sets to 0s

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%r9,4),%eax   #bitwise or to set display hour-ones position. Equivalent to(arr[hr_ones] << 14)

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%rcx,4),%eax  #bitwise or to set display minute-tens position. Equivalent to(arr[min_tens] << 7)

    sall    $7,%eax         #left shifts state by 7
    orl (%rdx,%r11,4),%eax  #bitwise or to set display minute-ones position. Equivalent to (arr[min_ones])


    jmp .FIN

    #Block H: re-extract hours, shift to set 1, and jump to relevant labels (SETS display to PM)

.SET1:
    movq    %rdi,%r10       # extract hours
	sarq    $0,%r10         # no shift needed
    andq    $0xFF,%r10
    orl $1,%eax             #sets bits to 1 to be shifted
    cmpq $9,%r10
    jle .SET3               #label with calculations to remove leading number (0)
    jmp .CALC2              #label with calculations not removing leading number

    #Block I: re-extract hours, shift to set 1, and jump to relevant labels (SETS display to AM)

.SET2:
    movq    %rdi,%r10       # extract hours
	sarq    $0,%r10         # no shift needed
    andq    $0xFF,%r10
    orl $1,%eax             #set bits to 1 to be shifted later in labels
    cmpq $9,%r10
    jle .SET                #label with calculations to remove leading number (0)
    jmp .CALC               #label with calculations not removing leading number




    #Block J: Successful completion and return

.FIN:
    movl %eax,(%rsi)
    movl $0,%eax
    ret


    #Block J: Error label to indicate error and return
.END:
    movq $1,%rax
    ret



.text
.global clock_update
clock_update:

        #Block A: Calls functions, deals with stack and its values

        pushq   %rbp            #push base pointer onto stack
        movq    %rsp, %rbp      #Copy value of stack pointer to base pointer
        subq    $16, %rsp       #allocates 16 bytes
        pushq   $0              #makes room for tod
        movl    TIME_OF_DAY_SEC(%rip), %edi #moves time of day in secs into edi
        leaq    -8(%rbp),       %rsi #tod address is now in rsi
        call    set_tod_from_secs
        cmpq    $1,%rax         #checks for error
        je      .ERROR
        movq    -8(%rbp), %rdi  #tod address now in rdi
        leaq    CLOCK_DISPLAY_PORT(%rip), %rsi #address of display in rsi
        call    set_display_bits_from_tod
        movq    $0, %rax        #0 in rax indicating success
        movq %rbp,%rsp          #Epilogue to return stack pointer
        popq %rbp
        ret


        #Block B: Error label because return of set_tod_from_secs function is 1

.ERROR:
        movq %rbp,%rsp #Epilogue to return stack pointer
        popq %rbp
        ret



