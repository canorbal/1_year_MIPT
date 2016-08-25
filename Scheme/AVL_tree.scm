; node = list ( data, (left), (right))
; where (left) is list (left_data, left_left,left_right) and (right) is analog.

(define left cadr)
(define right caddr)
(define data car)

(define (get-height avl_tree)
  (if (null? avl_tree) 0
      (+ 1
         (max (get-height (left avl_tree))
              (get-height (right avl_tree))))))

;as usual 4 types of rotates in avl_tree

(define (ll avl_tree)
  (list (data (left avl_tree))
        (left (left avl_tree))
        (list (data avl_tree)
              (right (left avl_tree))
              (right avl_tree))))

(define (rr avl_tree)
  (list (data (right avl_tree))
        (list (data avl_tree)
              (left avl_tree)
              (left (right avl_tree)))
        (right (right avl_tree))))

(define (big_left_rotate avl_tree)
  (ll (list (data avl_tree)
            (rr (left avl_tree))
            (right avl_tree ))))

(define (big_right_rotate avl_tree)
  (rr (list (data avl_tree)
            (left avl_tree)
            (ll (right avl_tree)))))

(define (insert key avl_tree)
  (cond ((null? avl_tree)
         (list key '() '()))
        ((< key (data avl_tree))
         (let ((temple_node (list (data avl_tree)
                               (insert key (left avl_tree))
                               (right avl_tree))))
           (when (= 2 (- (get-height (left temple_node))
                         (get-height (right temple_node))))
                 (if (< key (data (left temple_node)))
                     (set! temple_node (ll temple_node))
                     (set! temple_node (big_left_rotate temple_node))))
           temple_node))
        ((> element (data avl_tree))
         (let ((temple_node (list (data avl_tree)
                          (left avl_tree)
                          (insert element (right avl_tree)))))
           (when (= 2 (- (get-height (right temple_node))
                         (get-height (left temple_node))))
                 (if (> element (data (right temple_node)))
                     (set! temple_node (rr temple_node))
                     (set! temple_node (big_right_rotate temple_node))))
           temple_node))
        (else
         avl_tree)))

(define (print_tree_right avl_tree level)
 (print_tree (right avl_tree) (+ level 1))
 (display (make-string (* 4 level) #\ ))
 (display "    /\n"))

(define (print_tree_left avl_tree level)
 (display (make-string (* 4 level) #\ ))
 (display "    \\\n")
 (print_tree (left avl_tree) (+ level 1)))



(define (print_tree avl_tree level)
  (if (not (equal? '() (right avl_tree)))
    (print_tree_rightight avl_tree level))
 (display (make-string (* 4 level) #\ ))
 (display (data avl_tree))
 (display "\n")
 (if (not (equal? '() (left avl_tree)))
    (print_tree_left avl_tree level)))



(define (insert_num n tree)       ;this func copies tree 1000 times :(. It's bad
 (if (> n 0)
  (begin (set! tree (insert (random 1000) tree))
   (insert_num (- n 1) tree))
   ;(print_tree tree 0)))
 ))

(define tree '())
(insert_num 10000 tree)
