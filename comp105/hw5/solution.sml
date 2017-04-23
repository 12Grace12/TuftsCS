(* exceptions used for following functions *)
exception not_a_list;
exception invalid_indexing;
exception invalid_arguments;
exception invalid_expression; 

(*** part A: compound ***)
(* given a binary operator binop, an integer n, a value x, applies the operator to x n times and returns *)
fun compound binop 0 x = x
  | compound binop n x = binop (x, (compound binop (n - 1) x));

(* given two integers n & m, returns n^m *)
fun exp _ 0 = 1
  | exp n m = compound op * (m - 1) n; 

(*** part B: using foldr, foldl ***)
(* given a list l, returns the reversed list *)
fun myrev l = foldl (op ::) [] l;

(* given a list (of either integer or real) l, returns the minimum value of l *)
fun minlist (z::zs) = foldl (fn (x,y) => if x > y then y else x) z zs
  | minlist _       = raise not_a_list;

(*** part C: implementing foldl, foldr ***)
(* given a function f, an accumulator n, and a list l, returns the foldr of the list (with accumulator) *)
fun myfoldr f n [] = n
  | myfoldr f n (x::xs) = (f (x,(myfoldr f n xs)));

(* given a function f, an accumulator n, and a list l, returns the foldl of the list (with accumulator) *)
fun myfoldl f n [] = n
  | myfoldl f n (x::xs) = (myfoldl f (f (x,n)) xs);

(*** part D: flatten ***)
(* given a list of lists l, flattens l into a single list *)
fun flatten []    = []
  | flatten ((x)::(xs)) = (x@(flatten xs));

(*** part E: using exceptions ***)
(* given an index n and a list l, returns the n-th element of l (or raises the proper exception *)
fun mynth 0 (x::xs) = x
  | mynth n (x::xs) = mynth (n - 1) xs
  | mynth _ _     = raise invalid_indexing;

(*** part F: pair-wise fold ***)
(* given a function f, an accumulator n, and a tuple of two lists of elements (same type as n) *)
(* returns the pair-wise foldr of the two lists *)
fun pairfoldr f n ([],[]) = n
  | pairfoldr f n ((x::xs),(y::ys)) = (f (x,y,(pairfoldr f n (xs,ys))))
  | pairfoldr _ _ _       = raise invalid_arguments;

(*** part G: expression trees ***)
(* given datatype from assignment *)
datatype Exp = VAL of int
             | BINARY of Op * Exp * Exp
             | UNARY of Op * Exp
      and Op = PLUS | MINUS | TIMES | DIVIDE;

(* given an expression e of datatype Exp, this function returns evaluation of e *)
fun evalexp (VAL(v)) = v
  | evalexp (UNARY  (PLUS,  e))       = (evalexp e)
  | evalexp (UNARY  (MINUS, e))       = ~(evalexp e)
  | evalexp (BINARY (PLUS,   e1, e2)) = (evalexp e1) + (evalexp e2)
  | evalexp (BINARY (MINUS,  e1, e2)) = (evalexp e1) - (evalexp e2)
  | evalexp (BINARY (TIMES,  e1, e2)) = (evalexp e1) * (evalexp e2)
  | evalexp (BINARY (DIVIDE, e1, e2)) = (evalexp e1) div (evalexp e2)
  | evalexp _        = raise invalid_expression;

(* given an expression e of datatype Exp, checks if e is valid math expression (no unary divide or times) *)
fun checkexp (UNARY (DIVIDE, _))  = false
  | checkexp (UNARY (TIMES,  _))  = false
  | checkexp (UNARY  (_, e))      = checkexp e
  | checkexp (BINARY (_, e1, e2)) = checkexp e1 andalso checkexp e2 
  | checkexp (VAL _)              = true;

(* given an expression e of datatype Exp, returns the converted scheme expression of e *)
fun toscheme (VAL(v)) = Int.toString(v)
  | toscheme (UNARY (PLUS, e)) = toscheme e
  | toscheme (UNARY (MINUS, e)) = "(- 0 " ^ toscheme e ^ ")"
  | toscheme (BINARY (PLUS, e1, e2)) = "(+ " ^ toscheme e1 ^ " " ^ toscheme e2 ^ ")"
  | toscheme (BINARY (MINUS, e1, e2)) = "(- " ^ toscheme e1 ^ " " ^ toscheme e2 ^ ")"
  | toscheme (BINARY (TIMES, e1, e2)) = "(* " ^ toscheme e1 ^ " " ^ toscheme e2 ^ ")"
  | toscheme (BINARY (DIVIDE, e1, e2)) = "(/ " ^ toscheme e1 ^ " " ^ toscheme e2 ^ ")"
  | toscheme _ = raise invalid_expression;

(* given an expression e of datatype Exp, returns the converted ml expression of e *)
fun toml e =
    let
        (* helper function used to keep track of precedence as recursing through expression e *)
        (* if converted an expression of lower precedence than parent, parentheses may be necessary *)
        fun toml_help (VAL(v)) p = if v < 0 andalso p = 3 then ("(" ^ Int.toString(v) ^ ")") else Int.toString(v) 
          | toml_help (UNARY (PLUS, e)) p  = toml_help e p
          | toml_help (UNARY (MINUS, e)) 3 = "(~" ^ toml_help e 3 ^ ")"
          | toml_help (UNARY (MINUS, e)) _ = "~" ^ toml_help e 3
          | toml_help (BINARY (PLUS, e1, e2)) 0 = toml_help e1 0 ^ " + " ^ toml_help e2 0
          | toml_help (BINARY (PLUS, e1, e2)) _ = "(" ^ toml_help e1 0 ^ " + " ^ toml_help e2 0 ^ ")"
          | toml_help (BINARY (MINUS, e1, e2)) 0  = toml_help e1 0 ^ " - " ^ toml_help e2 1
          | toml_help (BINARY (MINUS, e1, e2)) _ = "(" ^ toml_help e1 0 ^ " - " ^ toml_help e2 1 ^ ")"
          | toml_help (BINARY (TIMES, e1, e2)) 2  = "(" ^ toml_help e1 1 ^ " * "  ^ toml_help e2 1 ^ ")"
          | toml_help (BINARY (TIMES, e1, e2)) _  = toml_help e1 1 ^ " * "  ^ toml_help e2 1
          | toml_help (BINARY (DIVIDE, e1, e2)) 2 = "(" ^ toml_help e1 1 ^ " div " ^ toml_help e2 2 ^ ")"
          | toml_help (BINARY (DIVIDE, e1, e2)) _ = toml_help e1 1 ^ " div " ^ toml_help e2 2
          | toml_help _ _ = raise invalid_expression;
    in
        toml_help e 0
    end;
