(= 4 4)    ; should be #t
(or #t #f) ; should be #t
(not #t)   ; should be #f
'(1 2 3 4) ; '(1 2 3 4) -> pair with v2
'(1)       ; '(1) -> pair with nil
'()        ; '() -> nil case
