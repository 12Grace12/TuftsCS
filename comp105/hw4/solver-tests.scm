(val f1 '(and (or x (not y)) (and (not x) y)))
(val s1 'no-solution)

(val f2 '(and (not (or x (and y z))) (or (not (and x y (or z x))) (and (not x) y z))))
(val s2 '((x #f) (y #f)))

(val f3 '(not (or x (and y (not x)))))
(val s3 '((x #f) (y #f)))
