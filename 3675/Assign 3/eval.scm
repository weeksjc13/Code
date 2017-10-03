;Josh Weeks
;CSCI 3675
;Program 3
;9/30/19
;Tab: none

(define (eval-expr E env)
  (cond
    ((number? E) E) ;E is a number so it stays a number
    ((symbol? E) (cadr (assoc E env)))
    ((eqv? (car E) 'closure) E)
    ((eqv? (car E) 'let)  (let* (
                                  (newvar (caadr E)) ;NEWVAR variable to represent NEWVAL
                                  (newval (eval-expr(cadadr E) env)) ;NEWVAL represents NEWVAR
                                  (newexpr (caddr E)) ;NEWEXPR represents the expression
                                  (newpair (list newvar newval)) ;NEWPAIR the NEWVAR and NEWVAL are put together
                                  (newenv (cons newpair env)) ;NEWENV newpair with new enviroment
                                )
                                (eval-expr newexpr newenv) ;E is expression   env is the new enviroment with NEWPAIR
                          )      
    )                     
    
    ((eqv? (car E) 'plus)     (apply + (eval-params (cdr E) env)))
    ((eqv? (car E) 'minus)    (apply - (eval-params (cdr E) env)))
    ((eqv? (car E) 'times)    (apply * (eval-params (cdr E) env)))
    ((eqv? (car E) 'divide)   (apply / (eval-params (cdr E) env)))
    ((eqv? (car E) 'function) (list 'closure (cadr E) (caddr E) env))
    ((eqv? (car E) 'call)     (eval-expr
                                (caddr (eval-expr (cadr E) env)) ;E
                                (cons (list (cadr (eval-expr (cadr E) env))(eval-expr (caddr E) env)) env) ;env
                              )
    )
    ((eqv? (car E) 'if) (if (= (eval-expr (cadr E) env) (or 0.0 0)) ;(if A B C) if A = 0 or 0.0 then return evalation of C
                               (eval-expr (cadddr E) env) ;(if A B C) -> C
                               (eval-expr (caddr E) env) ;(if A B C) -> B
                        )
    )
    
    (else '())  ;expression not recognized 
  )
)



;makes a list after eval-expr is called on the parameters
(define (eval-params E env)
  (if (null? E) '()
    (cons (eval-expr (car E) env) (eval-params (cdr E) env))
  )
)

(define (test)
  
  ;plus
  (display "PLUS") (newline)
  (display (eval-expr '(plus 2 3) '( ))) (newline) ;= 5
  (display (eval-expr '(plus (times 2 3) (minus 4 2)) '( ))) (newline) ;= 8

  ;if
  (display "IF") (newline)
  (display (eval-expr '(if (times 2 4) (plus 1 8) (divide 5 0)) '( ))) (newline) ;= 9
  (display (eval-expr '(if (minus 5 5) (divide 1 0) (plus 1 8)) '( ))) (newline) ;= 9

  ;association
  (display "ASSOCIATION") (newline)
  (display (eval-expr 'x '((y 2) (x 5)))) (newline) ;=5
  (display (eval-expr '(times x 3) '((x 5) (y 2)))) (newline) ;=15
  (display (eval-expr '(times x 3) '((x 5) (x 2)))) (newline) ;=15
  (display (eval-expr '(times x 3) '((x 2) (x 5)))) (newline) ;=6

  ;let
  (display "LET") (newline)
  (display (eval-expr '(let (z 15) (plus z z)) '( ))) (newline) ;= 30. 
  (display (eval-expr '(let (r (plus 2 5)) (times r 2)) '( ))) (newline) ;= 14.
  (display (eval-expr '(let (s 5) (let (t (plus s s)) (times s (plus t 3)))) '( ))) (newline) ;= 65

  ;function, call
  (display "FUNCTION CALL CLOSURE") (newline)
  (display (eval-expr '(let (f (function z (times z (plus w 1))))(call f(times 2 a))) '((a 5)(w 20)))) (newline) ;=210

)

(test)