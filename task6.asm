section .data
    const1 dq 2.0
    const2 dq -2.0
    const3 dq 8.0
    const4 dq -5.0
    fmt db `%f\n`
    
section .bss
    tmp resq 1

section .text

global f1
f1:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp + 8]
    fldl2e
    fmulp ;x*log_2(e)
    
    fld st0
    frndint
    fxch st1
    fsub st0, st1
    f2xm1
    fld1
    faddp
    fscale
    
    fld qword [const1]
    faddp
    
    fxch
    fstp qword [tmp]
   
    pop ebp
    ret
    
global f2
f2:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp + 8]
    fld qword [const2]
    fmulp
    fld qword [const3]
    faddp
    
    pop ebp
    ret
    
global f3
f3:
    push ebp
    mov ebp, esp
   
    finit 
    fld qword [const4]
    fld qword [ebp + 8]
    fdivp

    pop ebp
    ret
    
global df1
df1:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp + 8]
    fldl2e
    fmulp ;x*log_2(e)
    
    fld st0
    frndint
    fxch st1
    fsub st0, st1
    f2xm1
    fld1
    faddp
    fscale

    fxch
    fstp qword [tmp]
                                    
    pop ebp
    ret   
    
global df2
df2:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [const2]
    
    pop ebp
    ret
    
global df3
df3:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [const4]
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmul
    fdivp
    fchs
           
    pop ebp
    ret
    
global d2f1
d2f1:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp + 8]
    fldl2e
    fmulp ;x*log_2(e)
    
    fld st0
    frndint
    fxch st1
    fsub st0, st1
    f2xm1
    fld1
    faddp
    fscale

    fxch
    fstp qword [tmp]    

    pop ebp
    ret
    
global d2f2
d2f2:
    push ebp
    mov ebp, esp
    
    finit
    fldz

    pop ebp
    ret
    
global d2f3
d2f3:
    push ebp
    mov ebp, esp
    
    finit
    fld qword [const4]
    fld qword [const1]
    fmulp
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmul st1, st0
    fmulp 
    fdivp

    pop ebp
    ret