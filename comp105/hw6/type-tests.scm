(val e1 ((@ length int) ((@ cons int) 1 ((@ append int) '(1 2) '(3)))))
; type is int (value is 4)

(val e2 (type-lambda ('a) (lambda (('a x) ('a y)) ((@ = 'a) x y))))
; type is (forall ('a) ('a 'a -> bool))

(val e3 (type-lambda ('a) (lambda (('a x)) x)))
; type is (forall ('a) (function ('a) 'a))

(val e4 '(1 (2 (#t))))
; type error

(val e5 ((@ e2 int) #t #t))
; type error
