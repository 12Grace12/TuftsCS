;;
;; Problem A
;;
(define f-impertive (y)
    (letrec
        ((x e)                                        ; set x originally
         (f (lambda (x) (if (p x y) (f (g x y)) x)))) ; recursively set x using f
        (h (f x) y)                                   ; return result of h w/ new x & y
    )
)

;;
;; Problem 10b (Ramsey p.174)
;;
;; given a non-empty integer list xs, returns the maximum of the list
(define max* (xs)
    (foldr (lambda (x n) (if (> x n) x n)) (car xs) (cdr xs))        
)
(check-expect (max* '(1 2 3 5 3 4)) 5) ; standard case
(check-expect (max* '(1 1 1)) 1)       ; duplicate max case

;;
;; Problem 10c (Ramsey p.174)
;;
;; given a non-empty integer list xs, returns the greatest common divisor of
;; the elements in the list 
(define gcd* (xs)
    (foldr (lambda (x n) (gcd x n)) (car xs) (cdr xs)) 
)
(check-expect (gcd* '(18 12 24 60)) 6) ; standard case
(check-expect (gcd* '(11 19 37 53)) 1) ; gcd = 1
(check-expect (gcd* '(10 10)) 10)      ; gcd = element
(check-expect (gcd* '(0  10)) 10)      ; gcd = large element

;;
;; Problem 10d (Ramsey p.174)
;;
;; given a non-empty integer list xs, returns the least common multiple
;; of the elements in the list 
(define lcm* (xs)
    (foldr (lambda (x n) (lcm x n)) (car xs) (cdr xs))
)
(check-expect (lcm* '(4 3 6)) 12)  ; standard case 
(check-expect (lcm* '(5 12 6)) 60) ; standard case
(check-expect (lcm* '(1 3 12)) 12) ; lcm = largest element
(check-expect (lcm* '(5 2 0)) 0)   ; lcm = 0

;;
;; Problem 10e (Ramsey p.174)
;;
;; given a non-empty integer list xs, returns the sum of the elements in xs
(define sum (xs)
    (foldr + 0 xs)
)
(check-expect (sum '(1 2 3 4 5 0 5)) 20) ; standard case
(check-expect (sum '(1 2 -3 4)) 4)       ; negative number
(check-expect (sum '()) 0)               ; empty list

;;
;; Problem 10f (Ramsey p.174)
;;
;; given a non-empty integer list xs, returns the product of the elements in xs
(define product (xs)
    (foldr * 1 xs)
)
(check-expect (product '(1 2 3 4)) 24) ; standard case
(check-expect (product '(5 100 0)) 0)  ; 0 in list

;;
;; Problem 10g (Ramsey p.174)
;;
;; given two lists xs & ys, returns the appended list of the two '(xs ys)
(define append (xs ys)
    (foldr cons ys xs)
)
(check-expect (append '(1 2 3) '(4 5 6)) '(1 2 3 4 5 6)) ; standard case
(check-expect (append '() '()) '())                      ; two empty lists
(check-expect (append '() '(1 2 3)) '(1 2 3))            ; one empty list

;;
;; Problem 10i (Ramsey p.174)
;;
;; given a list xs, returns the simply reversed version of xs
;; (this does not do deep reversal / in nested lists)
(define reverse (xs)
    (foldl cons '() xs)
)
(check-expect (reverse '(1 2 3)) '(3 2 1))     ; simple reverse
(check-expect (reverse '()) '())               ; empty list reverse
(check-expect (reverse '((1 2) 3)) '(3 (1 2))) ; showing no deep reverse

;;
;; Problem 10j (Ramsey p.174)
;;
;; given an element x and a list xs, returns the list with x inserted (after
;; the first element greater than x)
;; (helper function used in insertion-sort)
;; (code taken from p.86 of Ramsey)
(define insert (x xs)
    (if (null? xs)
        (list1 x)
        (if (< x (car xs))
            (cons x xs)
            (cons (car xs) (insert x (cdr xs)))
        )
    )
)

;; given an integer list xs, returns the sorted list (sorting through insertion sort)
(define insertion-sort (xs)
    (foldl insert '() xs)
)
(check-expect (insertion-sort '(5 7 4 8 3 9 0)) '(0 3 4 5 7 8 9)) ; simple case
(check-expect (insertion-sort '(1 2 3 4 5 6 7)) '(1 2 3 4 5 6 7)) ; already sorted
(check-expect (insertion-sort '()) '())                           ; empty list

;;
;; Problem 11 (Ramsey p.174)
;;
;; given a list xs, returns the length of the list
(define length (xs)
    (foldr (lambda (x n) (+ n 1)) 0 xs)
)
(check-expect (length '(1 2 3 4 5)) 5) ; standard case
(check-expect (length '()) 0)          ; empty list

;; given a function f and a list xs, returns the list where each element is
;; the mapping f for each element in xx
(define map (f xs)
    (foldr (lambda (x n) (cons (f x) n)) '() xs)
)
(check-expect (map (lambda (x) (* 4 x)) '(1 2 3 10)) '(4 8 12 40))  ; standard case
(check-expect (map (lambda (x) (> 5 x)) '(1 3 7 4)) '(#t #t #f #t)) ; predicate f

;; given a predicate p and a list xs, returns the list of elements from xs
;; that meets the predicate
(define filter (p xs)
    (foldr (lambda (x n) (if (p x) (cons x n) n)) '() xs)
)
(check-expect (filter (lambda (x) (>= x 5)) '(8 2 4 6 1 5)) '(8 6 5)) ; standard case
(check-expect (filter (lambda (x) #f) '(1 2 3)) '())                  ; always false predicate

;; given a predicate p and a list xs, returns a bool indicating if there
;; is an element in xs that meets the predicate
(define exists? (p xs)
    (foldr (lambda (x n) (or (p x) n)) #f xs)
)
(check-expect (exists? (lambda (x) (>= x 5)) '(8 2 4 6 1)) #t)      ; standard true case
(check-expect (exists? (lambda (x) (= 0 (mod x 2))) '(1 3 5 7)) #f) ; standard false case

;; given a predicate p and a list xs, returns a bool indicating if all elements
;; in xs meet the predicate
(define all? (p xs)
    (foldr (lambda (x n) (and (p x) n)) #t xs)
)
(check-expect (all? (lambda (x) (>= x 5)) '(8 2 4 6 1)) #f)      ; standard false case
(check-expect (all? (lambda (x) (= 0 (mod x 2))) '(4 6 8 2)) #t) ; standard true case

;; 
;; Problem M
;; (See hofs-theory.pdf file for proof)

;;
;; Problem 16a (Ramsey p.176)
;;
;; given an element e and a set s, returns the set with in it
(define add-element (e s)
    (lambda (x) (or (s x) (= x e)))
)
(check-expect ((add-element 3 (lambda (x) #f)) 3) #t) ; add 3 to set, check if 3 in set
(check-expect ((add-element 3 (lambda (x) #f)) 4) #f) ; add 3 to set, check if 4 in set

;; given sets s1 & s2, returns the set union (combination) of s1 & s2
(define union (s1 s2)
    (lambda (x) (or (s1 x) (s2 x)))
)
(check-expect ((union (lambda (x) (= (mod x 2) 0)) (lambda (x) (and (< x 10) (>= x 0)))) 3) #t) ; union of event set and digit set, is 3 in it?
(check-expect ((union (lambda (x) (= (mod x 2) 0)) (lambda (x) (!= (mod x 2) 0))) 4) #t)        ; union of even set and odd set, is 4 in it?
(check-expect ((union (lambda (x) #f) (lambda (x) (and (< x 10) (>= x 0)))) 10) #f)             ; union of empty set and digit set, is 10 in it?
(check-expect ((union (lambda (x) #f) (lambda (x) #f)) 5) #f)                                   ; union of empty set and empty set, nothing it it

;; given sets s1 & s2, returns the set intersection (what they both share)
;; of s1 & s2
(define inter (s1 s2)
    (lambda (x) (and (s1 x) (s2 x)))
)
(check-expect ((inter (lambda (x) (= (mod x 2) 0)) (lambda (x) (and (< x 10) (>= x 0)))) 2) #t) ; intersection of even and digit sets (2 is even / digit)
(check-expect ((inter (lambda (x) (= (mod x 2) 0)) (lambda (x) (and (< x 10) (>= x 0)))) 3) #f) ; intersection of even and digit sets (3 is odd but digit)
(check-expect ((inter (lambda (x) #f) (lambda (x) (and (< x 10) (>= x 0)))) 5) #f)              ; intersection of empty set and digit sets (nothing in empty)

;; given sets s1 & s2, returns the set difference (what s1 has minus what s2 has)
(define diff (s1 s2)
    (lambda (x) (and (s1 x) (not (s2 x))))
)
(check-expect ((diff (lambda (x) #t) (lambda (x) (and (< x 10) (>= x 0)))) 3) #f) ; difference btwn allset and digits, doesn't have digits
(check-expect ((diff (lambda (x) #t) (lambda (x) (= (mod x 2) 0))) 15) #t)        ; difference btwn allset and evens, 15 not even, thus #t 
(check-expect ((diff (lambda (x) #t) (lambda (x) (= (mod x 2) 0))) 16) #f)        ; difference btwn allset and evens, 16 even, thus #f

;;
;; Problem 16b (Ramsey p.176)
;;
;; given an (polymorphic) equality function, returns the list containing the operations
;; used for / with sets
(define mk-set-ops (eqfun)
    (list6
        (lambda (x)   #f)                                    ; empty set
        (lambda (x s) (s x))                                 ; member?
        (lambda (e s) (lambda (x) (or  (s x) (eqfun e x))))  ; add element
        (lambda (x s1 s2) (or  (s1 x) (s2 x)))               ; union
        (lambda (x s1 s2) (and (s1 x) (s2 x)))               ; intersection
        (lambda (x s1 s2) (and (s1 x) (not (s2 x))))         ; difference
    )
)

;;
;; Problem 23 (Ramsey p.179)
;;
;; given a boolean formula f, a failure function fail, and a success function,
;; returns an associative list of values for the variables in f that makes
;; the equation f true
;; (for more information on function and its uses, see 3.10.1 in Ramsey)
(define make-formula-true (f fail succ)
    (letrec
        ;; make-formula takes in a formula, bool, current associated pair list,
        ;; failure and success functions and attempts to make formula true
        ;;     it does this by either binding the formula and the bool in curr
        ;;     or passing it to a correct function that can handle the formula
        ((make-formula (lambda (formula bool cur failure success)
            (if (atom? formula)
                (if (null? (find formula cur))
                    (success (bind formula bool cur) failure)
                    ;; checks if current bool matches previous bool values in curr
                    (if (= (find formula cur) bool)
                        (success cur failure)
                        (failure)
                    )
                )
                (if (= 'not (car formula))
                    ;; flip bool for not case
                    (make-formula (cadr formula) (not bool) cur failure success)
                    (if (= 'and (car formula))
                        ;; check if currently inside demorgan's law case (not (and x y))
                        (if (= #t bool)
                            (make-all (cdr formula) bool cur failure success)
                            (make-any (cdr formula) bool cur failure success)
                        )
                        ;; check if currently inside demorgan's law case (not (or x y))
                        (if (= 'or (car formula))
                            (if (= #t bool)
                                (make-any (cdr formula) bool cur failure success)
                                (make-all (cdr formula) bool cur failure success)
                            )
                            ;; standard case (likely nested list)
                            (make-formula (car formula) bool cur failure success)
                        )
                    )
                )
            )
         ))
         ;; given a formula list, try to make any of the variables true
         (make-any (lambda (formula bool cur failure success) 
            (if (null? formula)
                (failure) ; if end of list found, no variable in formula could have been true (thus failure)
                (make-formula (car formula) bool cur 
                    ;; if one variable fails, continue to check rest of list
                    (lambda () (make-any (cdr formula) bool cur failure success)) success)
            )
         ))
         ;; given a formula list, try to make all of the variables true
         (make-all (lambda (formula bool cur failure success)
            (if (null? formula) 
                (success cur failure) ; if end of list found, all variables were true (thus success)
                (make-formula (car formula) bool cur failure
                    ;; if one variable is successful, continue to check rest of list
                    (lambda (cur resume) (make-all (cdr formula) bool cur resume success)))
            )
         )))
    (make-formula f #t '() fail succ))    
)
(check-expect (make-formula-true '(or a b) (lambda () 'no-solution) (lambda (cur resume) cur)) '((a #t)))              ; standard or
(check-expect (make-formula-true '(not a) (lambda () 'no-solution) (lambda (cur resume) cur)) '((a #f)))               ; standard not
(check-expect (make-formula-true '(not (not a)) (lambda () 'no-solution) (lambda (cur resume) cur)) '((a #t)))         ; double not
(check-expect (make-formula-true '(and a (not a)) (lambda () 'no-solution) (lambda (cur resume) cur)) 'no-solution)    ; no-solution case
(check-expect (make-formula-true '(not (and x y)) (lambda () 'no-solution) (lambda (cur resume) cur)) '((x #f)))       ; demorgan's law v1
(check-expect (make-formula-true '(not (and b (not a))) (lambda () 'no-solution) (lambda (cur resume) cur)) '((b #f))) ; demorgan's law v2
(check-expect (make-formula-true '(not (or x y)) (lambda () 'no-solution) (lambda (cur resume) cur)) '((x #f) (y #f))) ; demorgan's law v3
(check-expect (make-formula-true '(or (not (and (or x y) z)) z) (lambda () 'no-solution) (lambda (cur resume) cur)) '((x #f) (y #f)))              ; complex sequence v1
(check-expect (make-formula-true '(and (or (not x) y) (not (or y z))) (lambda () 'no-solution) (lambda (cur resume) cur)) '((x #f) (y #f) (z #f))) ; complex sequence v2
(check-expect (make-formula-true '(not (or x (and y (not x)))) (lambda () 'no-solution) (lambda (cur resume) cur)) '((x #f) (y #f)))               ; complex sequence v3
(check-expect (make-formula-true '(or (and (not x) (and y x)) (and x (not x)))  (lambda () 'no-solution) (lambda (cur resume) cur)) 'no-solution)  ; complex no-solution v1
(check-expect (make-formula-true '(and (or x (not y)) (and (not x) y)) (lambda () 'no-solution) (lambda (cur resume) cur)) 'no-solution)           ; complex no-solution v2

;;
;; Extra Credit Problem
;;
;; given a function (binary comparison), returns a function that can be used to quicksort a list of integers
;; - breaks list up into two pieces (left & right) which are split around a pivot value (the contents of left
;;   and right determined using the function f)
;; - continues to breakdown lists until the length of a list is 1, then returns itselft (base case)
;; - merges these two lists using foldr and the accumulating right sorted portion of the list
(define qsort (f)
    (lambda (xs)
        (if (<= (length xs) 1)
            xs
            (let*
                ((piv   (car xs))
                 (right (filter ((curry f) piv) (cdr xs)))
                 (left  (filter (o not ((curry f) piv)) (cdr xs))))
            (foldr cons (cons piv ((qsort f) right)) ((qsort f) left)))
        )
    )
)
(check-expect ((qsort <) '(6 9 1 7 4 14 8 10 3 5 11 15 2 13 12)) '(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)) ; standard case
(check-expect ((qsort >) '(6 9 1 7 4 14 8 10 3 5 11 15 2 13 12)) '(15 14 13 12 11 10 9 8 7 6 5 4 3 2 1)) ; standard high-to-low case
(check-expect ((qsort !=) '(1 2 3 1)) '(1 1 2 3))                                                        ; not-equal operator for f
(check-expect ((qsort >) '()) '())                                                                       ; empty set
