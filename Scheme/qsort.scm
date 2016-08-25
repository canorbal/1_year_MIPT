(define (split lst t i)
    (let coil ((low '())
        (high '())
        (lst lst))

    (cond ((null? lst)
           (i low high))
           ((t (car lst))
            (coil low (cons (car lst) high ) (cdr lst)))
           (else
            (coil (cons (car lst) low) high (cdr lst))))))


;sign means sort ascending / descending

(define (qsort lst sign)
    (if (null? lst)
      '()
    (split (cdr lst)
     (lambda (i) (sign i (car lst)))
     (lambda (low high)
      (append (qsort low sign)
       (list (car lst))
       (qsort high sign))))))

; call example
(define lst1 (list 3 1 2))
(display  (qsort lst1 < ))
