(* testing compound *)
12 = compound (op +) 1 6;
1  = compound (op div) 1 5;

(* testing exp *)
9   = exp 3 2;
125 = exp 5 3;

(* testing myrev *)
[9, 9, 4, 5, 2, 1] = myrev [1, 2, 5, 4, 9, 9];
[5, 4, 3, 2, 1]    = myrev [1, 2, 3, 4, 5];

(* testing minlist *)
1 = minlist [1, 2, 3];
3 = minlist [5, 7, 3, 4];

(* testing myfoldr & myfold *)
0 + 3 + 2 + 1 = myfoldr (fn (x,y) => x + y) 0 [1,2,3];
1 = myfoldr (fn (x, y) => if x > y then y else x) 100 [1, 2, 3];
6 = myfoldl (fn (x,y) => x + y) 0 [1,2,3];
3 = myfoldl (fn (x,y) => if x > y then y else x) 100 [5, 7, 3, 4];
[5, 4, 3, 2, 1] = myfoldl (op ::) [] [1, 2, 3, 4, 5];
[5, 4, 3, 2, 1] = foldl (op ::) [] [1,2,3,4,5]; 

(* testing flatten *)
[1,2,3,4,5,6] = flatten [[1], [2, 3, 4], [], [5, 6]]; 
[5,4,8,9,10]  = flatten [[5], [4], [8,9], [10]];

(* testing mynth *)
3  = mynth 2 [1,2,3];
~1 = (mynth 3 [1,2,3] handle invalid_indexing => ~1);

(* testing pairfoldr *)
12 = pairfoldr (fn (x,y,z) => x + y + z) 0 ([1,2,3],[1,2,3]);
3  = pairfoldr (fn (x,y,z) => (x + y) div z) 1 ([3,2,1],[3,2,1]);

(* testing evalexp *)
7  = evalexp (BINARY (PLUS, VAL(4), VAL(3)));
~7 = evalexp (UNARY (MINUS, BINARY(PLUS, VAL(4), VAL(3))));

(* testing checkexp *)
true  = checkexp (UNARY (PLUS, VAL(3)));
false = checkexp (UNARY (DIVIDE, VAL(3)));
false = checkexp (BINARY (TIMES, (UNARY (DIVIDE, VAL(3))), VAL(3)));

(* testing toscheme *)
"(+ 4 (- 0 3))" = toscheme (BINARY (PLUS, VAL(4), (UNARY (MINUS, VAL(3)))));
"(- 0 (+ 4 3))" = toscheme (UNARY (MINUS, (BINARY (PLUS, VAL (4), VAL (3)))));

(* testing toml *)
"4 + ~3"        = toml (BINARY (PLUS, VAL(4), (UNARY (MINUS, VAL(3)))));
"~(4 + 3)"      = toml (UNARY (MINUS, (BINARY (PLUS, VAL (4), VAL (3)))));
"4 div (3 + 2)" = toml (BINARY (DIVIDE, VAL(4), (BINARY (PLUS, VAL(3), VAL(2)))));
"3" = toml (UNARY (PLUS, VAL(3)));
"1 * 2 + 3" = toml (BINARY (PLUS, BINARY (TIMES, VAL(1), VAL(2)), VAL(3)));
"(1 + 2) * 3" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), VAL(3)));
"(1 + 2) * 3 div 4" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), BINARY(DIVIDE, VAL(3), VAL(4))));
"(1 + 2) * (3 - 4)" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), BINARY(MINUS, VAL(3), VAL(4))));
"(1 + 2) * (3 + 4) div 5" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), BINARY(DIVIDE, BINARY(PLUS, VAL(3), VAL(4)), VAL(5))));
"(1 + 2) * (3 + 4) * (5 + 6)" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), BINARY(TIMES, BINARY(PLUS, VAL(3), VAL(4)), BINARY(PLUS, VAL(5), VAL(6)))));
"(1 + 2) * 3 div 4 * (5 + 6)" = toml (BINARY (TIMES, BINARY(PLUS, VAL(1), VAL(2)), BINARY(TIMES, BINARY(DIVIDE, VAL(3), VAL(4)), BINARY(PLUS, VAL(5), VAL(6)))));
"~1" = toml (UNARY(MINUS, VAL(1))); 
"~(~2)" = toml (UNARY(MINUS, VAL(~2))); 
"~(~1)" = toml (UNARY(MINUS, (UNARY(MINUS, VAL(1))))); 
"~1 - ~1" = toml (BINARY (MINUS, (UNARY(MINUS, VAL(1))), (UNARY(MINUS, VAL(1)))));
"2 - (3 + 4)" = toml (BINARY(MINUS, VAL(2), BINARY(PLUS, VAL(3), VAL(4))));
"2 + 3 - 4" = toml (BINARY(PLUS, VAL(2), BINARY(MINUS, VAL(3), VAL(4))));
"2 - (3 - 4)" = toml (BINARY(MINUS, VAL(2), BINARY(MINUS, VAL(3), VAL(4))));
"2 - 3 + 4" = toml (BINARY(PLUS, BINARY(MINUS, VAL(2), VAL(3)), VAL(4)));
"(3 - 4) * ~1" = toml (BINARY(TIMES, BINARY(MINUS, VAL(3), VAL(4)), VAL(~1)));
"~(~1)" = toml (UNARY(MINUS, VAL(~1)));
"~(~(~1))" = toml (UNARY(MINUS, UNARY(MINUS, VAL(~1))));
"2 div (3 div 4)" = toml (BINARY(DIVIDE, VAL(2), BINARY(DIVIDE, VAL(3), VAL(4))));
"2 div (3 * 4)" = toml (BINARY(DIVIDE, VAL(2), BINARY(TIMES, VAL(3), VAL(4))));
"2 div 3 div 4" = toml (BINARY(DIVIDE, BINARY(DIVIDE, VAL(2), VAL(3)), VAL(4)));
"2 div 3 * 4" = toml (BINARY(TIMES, BINARY(DIVIDE, VAL(2), VAL(3)), VAL(4)));
"2 * 3 * 4" = toml (BINARY(TIMES, BINARY(TIMES, VAL(2), VAL(3)), VAL(4)));
"1 * 2 * (3 - 4)" = toml (BINARY (TIMES, BINARY(TIMES, VAL(1), VAL(2)), BINARY(MINUS, VAL(3), VAL(4))));

