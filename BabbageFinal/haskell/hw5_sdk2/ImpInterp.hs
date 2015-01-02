module ImpInterp where

import Prelude hiding (exp)
import ImpSyntax
import ImpParser hiding (stmt, prog)

-----------------------------------
--      Addresses and Values     --
-----------------------------------

type Address    = Int
data Value      = Number Int
                | Loc Address
                | Nil
                | FunVal (Env -> State -> [Value] -> Value)

instance Show Value where
  show (Number i) = show i
  show (FunVal _) = "Function Value not Showable"

instance Eq Value where
  Number i == Number j = i==j
  _ == _ = error "Num eqs compared to vals" --undefined

instance Ord Value where
  Number i <= Number j = i <= j
  _ <= _ = undefined
  Number i >= Number j = i >= j
  _ >= _ = undefined


--
-- How would you define Value arithmetic?
--

instance Num Value where
  Number i + Number j = Number (i+j)
  Number i + Loc j    = Loc (i+j)
  Loc i + Number j    = Loc (i+j)
  Loc i + Loc j       = Loc (i+j)
  Number i * Number j = Number (i*j)
  Number i - Number j = Number (i-j)
  negate = undefined
  abs = undefined
  signum = undefined
  fromInteger = undefined

-----------------------------------
--    Environment Operations     --
-----------------------------------

type Env        = Name -> Value

tweek x v r = \ y -> if x==y then v else r y

extend :: Env -> [(Name, Value)] -> Env
extend r []         = r
extend r ((x, v):bs) = tweek x v (extend r bs)

-----------------------------------
--        State Operations       --
-----------------------------------

type State = (Address, Address -> Value)

alloc :: State -> State
alloc (a, s) = (a + 1, s)

-- assigns a value to an address in a State
update :: Address -> Value -> State -> State
update x v (a, s) = (a, s')
    where
       s' = tweek x v s

-- 1. Look up value bound to x
-- 2. If it's a number, return it.
-- 3. If it's an address, look up the contents in the state.
varread :: Name -> Env -> State -> Value
varread x r (_, s) = case (r x) of
                         Number i -> Number i
                         Loc a    -> s a

--
varstore :: Name -> Value -> Env -> State -> State
varstore x v r s = case r x of
                        Number i -> error "argh!"
                        Loc a    -> update a v s

-----------------------------------
--    Expression Semantics       --
-----------------------------------

exp :: Exp -> Env -> State -> Value
exp (Add e1 e2) r s    = (exp e1 r s) + (exp e2 r s)
exp (Sub e1 e2) r s    = (exp e1 r s) - (exp e2 r s)
exp (Mul e1 e2) r s    = (exp e1 r s) * (exp e2 r s)
exp (Neg e) r s        = -(exp e r s)
exp (Var x) r s        = varread x r s
exp (LitInt m) _ _     = Number m
exp (FunCall f xs) r s = fv r s vs
    where
       FunVal fv = r f
       vs        = map (\ e -> exp e r s) xs


-----------------------------------
--      Boolean Semantics        --
-----------------------------------

bool :: BExp -> Env -> State -> Bool
bool (IsEq  e1 e2) r s = exp e1 r s == exp e2 r s
bool (IsNEq e1 e2) r s = not(exp e1 r s == exp e2 r s)
bool (IsGT  e1 e2) r s = exp e1 r s >  exp e2 r s
bool (IsGTE e1 e2) r s = exp e1 r s >=  exp e2 r s
bool (IsLT e1 e2)  r s = exp e1 r s < exp e2 r s
bool (IsLTE e1 e2) r s = exp e1 r s <= exp e2 r s
bool (And   b1 b2) r s = bool b1 r s &&  bool b2 r s
bool (Or    b1 b2) r s = bool b1 r s || bool b2 r s
bool (Not b)       r s = not (bool b r s)
bool (LitBool x)  _  _  = x

-----------------------------------
--     Statement Semantics       --
-----------------------------------

--stmt :: Stmt -> Env -> State -> State
stmt :: Stmt -> Env -> State -> (Value, State)
stmt (Assign x e) r s = (Nil, varstore x (exp e r s) r s)
stmt (If b pt pf) r s = if (bool b r s)
                          then (stmts pt r s)
                          else (stmts pf r s)
stmt (While b p) r s  = if (bool b r s)
                          then (stmts (p++[While b p]) r s)
                          else (Nil, s)
stmt (Let x e p) r s  = stmts p r' s''
                          where (ax, s') = alloc s
                                r'      = tweek x (Loc ax) r
                                s''     = update ax v (ax, s')
                                v       = exp e r s
stmt (Return e) r s   = (v, s)
    where
      v = exp e r s

-----------------------------------
--  Statement List Semantics     --
-----------------------------------

--stmts :: [Stmt] -> Env -> State -> State
stmts :: [Stmt] -> Env -> State -> (Value, State)
stmts [] _ s       = (Nil, s)
stmts (Return e : sts) r s = stmt (Return e) r s
stmts (st:[]) r s = stmt st r s
stmts (st:sts) r s = stmts sts r (snd (stmt st r s))

-----------------------------------
-- Program & Function Semantics  --
-----------------------------------

--
-- Recall that
--
--type Prog = ([FunDefn], [Stmt])
--type FunDefn = (Name, [Name], [Stmt])

fundef :: FunDefn -> Env -> State -> ([Value] -> Value)
fundef (n, xs, ps) r s vs = v
     where
       (v, _) = stmts ps r' s
       r'    = extend r (zip xs vs)

prog (fdecls, body) = stmts body r0 s0
  where
    fds = map (FunVal . fundef) fdecls
    fs  = map fst3 fdecls
           where fst3 (x, _, _) = x
    r0  = extend (\ n -> error ("Unbound: " ++ n)) (zip fs fds)
    s0  = (0, \ a -> error ("Unititialized Location: " ++ show a))

interp fn = do p <- parseImp fn
               let result = fst (prog p)
               print result

-----------------------------------
--          Examples             --
-----------------------------------

dbl :: FunDefn
dbl = ("double", ["m"], [Return (Add (Var "m")  (Var "m"))])

ad :: FunDefn
ad = ("add", ["m", "n"], [Return (Add (Var "m")  (Var "n"))])

factorial :: FunDefn
factorial = ("fac", ["n"], [If (IsEq (Var "n") (LitInt 0)) [Return (LitInt 1)] [Return (Mul (Var "n") (FunCall "fac" [Sub (Var "n") (LitInt 1)]))]])
