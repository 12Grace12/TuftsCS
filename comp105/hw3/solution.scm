;; function taken from Ramsey p.83, used to determine if element is an atom
(define atom? (x) (or (number? x) (or (symbol? x) (or (boolean? x) (null? x)))))

;; Problem 2a
;;
;; given atom x and list xs, returns the count of x in xs (not including nested lists)
(define count (x xs)
    (if (null? xs)
        0
        (+ 
            (if (= (car xs) x) 1 0)
            (count x (cdr xs))
        )
    )
)
(check-expect (count 'a '(a a b a)) 3)     ; standard case
(check-expect (count 'a '(1 b a (c a))) 1) ; list inside list (doesn't count)
(check-expect (count 'a '(b c d)) 0)       ; no matches present
(check-expect (count 'a '()) 0)            ; empty list

;; Problem 2b
;;
;; given atom x and list xs, returns the count of x in xs (including in nested lists)
(define countall (x xs)
    (if (null? xs)
        0
        (+
            (if (atom? (car xs))
                (if (= (car xs) x) 1 0)
                (countall x (car xs))
            )
            (countall x (cdr xs))
        )
    )
)
(check-expect (countall 'a '(a a b a)) 3)     ; standard case (no nested lists)
(check-expect (countall 'a '(1 b a (c a))) 2) ; nested list (counting matches)
(check-expect (countall 'a '(b c d)) 0)       ; no matches present
(check-expect (countall 'a '((a (a)) a b)) 3) ; double nested list
(check-expect (countall 'a '()) 0)            ; empty list

;; Problem 2c
;;
;; given list xs, returns a mirrored list (including nested lists)
(define mirror (xs)
    (if (null? xs)
        xs
        (append 
            (mirror (cdr xs)) 
            (list1 
                (if (atom? (car xs)) 
                    (car xs) 
                    (mirror (car xs))
                )
            )
        )
    )
)

(check-expect (mirror '(1 2 3 4 5)) '(5 4 3 2 1))                 ; simple mirror
(check-expect (mirror '((a (b 5)) (c d) e)) '(e (d c) ((5 b) a))) ; nested lists mirror
(check-expect (mirror '()) '())                                   ; empty list

;; Problem 2d
;;
;; given list xs, returns a flattened list with no remaining nested lists
(define flatten (xs)
    (if (null? xs)
        '()
        (append 
            (if (atom? (car xs))
                (list1 (car xs))
                (flatten (car xs))
            )
            (flatten (cdr xs))
        )
    )
)
(check-expect (flatten '((I Ching) (U Thant) (E Coli))) '(I Ching U Thant E Coli)) ; flattening pairs
(check-expect (flatten '(((((a)))))) '(a))                                         ; flatten super nested list   
(check-expect (flatten '((a b) ((c d) e))) '(a b c d e))                           ; flatten many nested lists

;; Problem 2e
;;
;; helper function used by contig-sublist? for when xs and ys are currently matching contigiously
(define active-contig-sublist? (xs ys)
    (if (null? xs)
        #t
        (if (null? ys)
            #f
            (if (= (car xs) (car ys))
                (active-contig-sublist? (cdr xs) (cdr ys))
                #f
            )
        )
    )
)

;; given lists xs and ys, checks if xs is a sublist that is contigiously contained within ys
(define contig-sublist? (xs ys)
    (if (null? xs)
        #t
        (if (null? ys)
            #f
            (if (= (car xs) (car ys))
                (if (active-contig-sublist? (cdr xs) (cdr ys))
                    #t
                    (contig-sublist? xs (cdr ys))
                )
                (contig-sublist? xs (cdr ys))
            )
        )
    )
)
(check-expect (contig-sublist? '(a b c) '(a b a b c))   #t) ; sublist contained as section potential sublist
(check-expect (contig-sublist? '(a b c) '(x a y b z c)) #f) ; is sublist, but not contig
(check-expect (contig-sublist? '(a y b) '(x a y b z c)) #t) ; is sublist and contig
(check-expect (contig-sublist? '(x)     '(x a y b z c)) #t) ; is single element list
(check-expect (contig-sublist? '()      '(x a y))       #t) ; ys contains all elements of empty list
(check-expect (contig-sublist? '(x)     '())            #f) ; ys is empty and thus doesn't have any sublists

;; Problem 2f
;;
;; given lists xs and ys, checks if xs is a sublist within ys (doesn't have to be contigious)
(define sublist? (xs ys)
    (if (null? xs)
        #t
        (if (null? ys)
            #f
            (if (= (car xs) (car ys))
                (sublist? (cdr xs) (cdr ys))
                (sublist?      xs  (cdr ys))
            )
        )
    )
)
(check-expect (sublist? '(a b c) '(x a y b z c)) #t) ; is sublist but not contig (doesn't matter)
(check-expect (sublist? '(a y b) '(x a y b z c)) #t) ; is sublist and is contig
(check-expect (sublist? '(a z b) '(x a y b z c)) #f) ; contains same elements but not in right order
(check-expect (sublist? '(x d z) '(x a y b z c)) #f) ; doesn't contain 'd
(check-expect (sublist? '()      '()           ) #t) ; empty lists contain same thing

;; Problem 6
;;
;; given predicate f and list xs, returns the largest prefix of xs where all elements meet predicate f
(define takewhile (f xs)
    (if (null? xs)
        '()
        (if (f (car xs))
            (append (list1 (car xs)) (takewhile f (cdr xs)))
            '()
        )
    )
)

;; given predicate f and list xs, returns the remains of xs with the largest prefix of elements meeting f removed 
(define dropwhile (f xs)
    (if (null? xs)
        '()
        (if (f (car xs))
            (dropwhile f (cdr xs))
            xs
        )
    )
)

(define even? (x) (= (mod x 2) 0))
(check-expect (takewhile even? '(2 4 6 7 8 10 12)) '(2 4 6))                                       ; standard takewhile case
(check-expect (dropwhile even? '(2 4 6 7 8 10 12)) '(7 8 10 12))                                   ; standard dropwhile case
(check-expect (append (takewhile even? '(2 4 6 7 8)) (dropwhile even? '(2 4 6 7 8))) '(2 4 6 7 8)) ; basic law from Ramsey p.181
(check-expect (takewhile even? '()) '())                                                           ; empty case - takewhile
(check-expect (dropwhile even? '()) '())                                                           ; empty case - dropwhile

;; Problem 15
;;
;; The procedure defined returns the square root of the sum of two squares 
;; (sqrt((x*x) + (y*y))). At first glance it seems like it should return 
;; (sqrt((x+x) * (y+y))) but there is a small difference that comes from the 
;; remapping of the * operation and + operation. We formally think that * should
;; return the product of two expressions and that + should return the sum of two
;; expressions. However, with the use of "let" vector-length redefines these
;; operations and actually switches their meaning (* returns a sum and + returns
;; a product). This works because we are using let (as opposed to let* or letrec)
;; which evaluates the expressions of let [e1 and e2 in (let (v1 e1) (v2 e2) e)]
;; before mapping the variables to these expressions. If we used let*, we would
;; first evaluate *, then set + to *, then evaluate + (now equal to the product),
;; and finally set * to +, which results in * and + being equal to the product.
;; For this reason, by using let it allows us to switch the definitions of * and +
;; and return the square-root of the sum of two squares.

;; Problem 31
;;
;; For my solution to Exercise 31, see scheme-theory.pdf

;; Problem A
;;
;; given integer n and list xs, returns a list with the first n elements of xs
(define take (n xs)
    (if (or (= n 0) (null? xs))
        '()
        (cons (car xs) (take (- n 1) (cdr xs)))       
    )
)

;; given integer n and list xs, returns a list without the first n elements of xs
(define drop (n xs)
    (if (or (= n 0) (null? xs))
        xs
        (drop (- n 1) (cdr xs))
    )
)
(check-expect (take 2 '(1 2 3 4)) '(1 2))                                        ; standard case
(check-expect (drop 2 '(1 2 3 4)) '(3 4))                                        ; standard case
(check-expect (append (take 3 '(1 2 3 4 5)) (drop 3 '(1 2 3 4 5))) '(1 2 3 4 5)) ; algebraic law for take / drop
(check-expect (take 5 '(1 2 3)) '(1 2 3))                                        ; takes more elements than present
(check-expect (drop 5 '(1 2 3)) '())                                             ; drops more elements than present

;; Problem B
;;
;; given lists a & b, merges the elements of a & b to make an associated pair list
(define zip (a b)
    (if (or (null? a) (null? b))
        '()
        (cons
            (list2 (car a) (car b))
            (zip (cdr a) (cdr b))
        )   
    )
)

;; given list a, breaks the associated pair list into distinct key and value lists
(define unzip (a)
    (list2 (map car a) (map cadr a)) 
)
(check-expect (zip '(1 2 3) '(a b c)) '((1 a) (2 b) (3 c)))              ; standard case
(check-expect (unzip '((1 a) (2 b) (3 c))) '((1 2 3) (a b c)))           ; standard case
(check-expect (unzip (zip '(1 2 3) '(a b c))) (list2 '(1 2 3) '(a b c))) ; algebraic law between two (standard)
(check-expect (unzip (zip '() '())) (list2 '() '()))                     ; algebraic law between empty lists

;; Problem C
;;
;; given function f and list xs, returns the value x in xs that returns the greatest value for f(x)
(define arg-max (f xs)
    (if (= 1 (length xs)) 
        (car xs)
        (if (>= (f (car xs)) (f (arg-max f (cdr xs))))
            (car xs)
            (arg-max f (cdr xs))
        )
    )
)

(define square (x) (* x x))
(check-expect (arg-max square '(4 3 5 2 1)) 5) ; standard case

;; Problem D
;;
;; helper function used to check of there is a key k in the pair list l
(define has-key? (k l)
    (if (null? l)
        #f
        (if (= (caar l) k)
            #t
            (has-key? k (cdr l))
        )
    )
)

;; helper function used to bind a pair p into the list l in successor format
(define bind-pair (p l)
    (bind 
        (car p)
        (append 
            (if (null? (cadr p))
                '() 
                (cdr p)
            )
            (find (car p) l)
        ) 
        l
    )
)

;; helper function used to add the value of key-value pair as a terminating vertex to graph
(define add-val-pair (p l) 
    (if (has-key? (cadr p) l) ; if value already a key in list, no need to add to list
        l
        (bind-pair (list2 (cadr p) '()) l)
    )
)

;; given an edge list el, returns a successor map of said edge list
(define successors-map-of-edge-list (el)
    (let*
        ((l (foldl bind-pair  '() el))  ; loop through el and add each pair into list l
         (l (foldl add-val-pair l el))) ; loop through el and add the values for terminating verticies        
        l   
    )
)

;; helper function which turns single vertex mapping into list of edges
(define edge-list-of-single-map (m)
    (if (null? (cadr m))
        '()
        (cons 
            (list2 (car m) (caadr m))
            (edge-list-of-single-map
                (list2 (car m) (cdadr m))
            )
        )
    )  
)

;; given a successor mapping, returns the corresponding edge list
(define edge-list-of-successors-map (sm)
    (if (null? sm)
        '()
        (append 
            (edge-list-of-single-map (car sm))     ; converts first mapping
            (edge-list-of-successors-map (cdr sm)) ; continues to convert rest of mappings
        )
    )
)
(check-expect (successors-map-of-edge-list '((A B) (A C) (B C))) '((A (C B)) (B (C)) (C ()))) ; standard case
(check-expect (edge-list-of-successors-map '((A (B C)) (B (C)) (C ()))) '((A B) (A C) (B C))) ; standard case

;; Problem E
;;
;; given sorted lists xs and ys, returns a sorted merging of the two lists 
(define merge (xs ys)
    (if (null? xs)
        ys
        (if (null? ys)
            xs
            (if (< (car xs) (car ys))
                (cons (car xs) (merge (cdr xs) ys))
                (cons (car ys) (merge xs (cdr ys)))
            )
        )
    )
)
(check-expect (merge '(1 2 3) '(4 5 6)) '(1 2 3 4 5 6)) ; lists already sorted (just merge)
(check-expect (merge '(1 3 5) '(2 4 6)) '(1 2 3 4 5 6)) ; lists not already sorted
(check-expect (merge '()      '(1 2 3)) '(1 2 3))       ; a list is empty

;; Problem F
;;
;; given lists xs and ys, returns merged list with alternating elements from xs and ys
(define interleave (xs ys)
    (if (and (null? xs) (null? ys))
        '()
        (append 
            (append 
                (if (null? xs) xs (list1 (car xs))) 
                (if (null? ys) ys (list1 (car ys)))
            )
            (interleave 
                (if (null? xs) xs (cdr xs))
                (if (null? ys) ys (cdr ys))
            )
        )
    )
)
(check-expect (interleave '(1 2 3) '(a b c))       '(1 a 2 b 3 c))       ; standard case 
(check-expect (interleave '(1 2 3) '(a b c d e f)) '(1 a 2 b 3 c d e f)) ; ys is longer than xs
(check-expect (interleave '(1 2 3 4 5 6) '(a b c)) '(1 a 2 b 3 c 4 5 6)) ; xs is longer than ys
(check-expect (interleave '()            '(a b c)) '(a b c))             ; a list is null
