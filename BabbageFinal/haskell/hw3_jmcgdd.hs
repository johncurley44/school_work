{---------------------------------------------------
John Curley - jmcgdd
CS4450 - Principles of Programming Languages
October 16, 2014
HW3
----------------------------------------------------}

module HW3_jmcgdd where

import Prelude

data Op			= Val Int | Plus | Minus | Mul | IntDiv deriving (Show, Eq)
type PExp		= [Op]

data RPNError = DivByZero | InvalidInput deriving (Show, Eq)
type RPNResult = Either RPNError Int

--Question 1 (so not worry about other inputs besides +, -, /, * and int?

toPExp :: String -> Op
toPExp s		| s=="+"			= Plus
				| s=="-"			= Minus
				| s=="*"			= Mul
				| s=="/"			= IntDiv
				| otherwise			= Val (read s :: Int)


rpnParse :: String -> PExp
rpnParse s		= map toPExp (words s)

--Question 2
leftFoldFunc :: [Int] -> Op -> [Int]
leftFoldFunc (p:q:qs) Plus		= q+p:qs
leftFoldFunc (p:q:qs) Minus 	= q-p:qs
leftFoldFunc (p:q:qs) Mul 		= q*p:qs
leftFoldFunc (p:q:qs) IntDiv 	= (quot q p):qs
leftFoldFunc p (Val i)			= i:p
leftFoldFunc _ _				= error "Bad Input"

eval :: PExp -> Int
eval p		= if length (foldl leftFoldFunc [] p) == 1 then head (foldl leftFoldFunc [] p) else error "Bad Input"

--Question 3

evalSafe :: PExp -> RPNResult
evalSafe p	= if length (foldl leftFoldFuncSafe [] p) == 1 then head (foldl leftFoldFuncSafe [] p) else Left InvalidInput

leftFoldFuncSafe :: [RPNResult] -> Op -> [RPNResult]
leftFoldFuncSafe (Left l:ls) _					= [Left l]
leftFoldFuncSafe l (Val i)						= (Right i):l
leftFoldFuncSafe [] op							= [Left InvalidInput]
leftFoldFuncSafe (Right l:Right m:ms) Plus		= Right (m+l):ms
leftFoldFuncSafe (Right l:Right m:ms) Minus 	= Right (m-l):ms
leftFoldFuncSafe (Right l:Right m:ms) Mul 		= Right (m*l):ms
leftFoldFuncSafe (Right 0:Right m:ms) IntDiv	= [Left DivByZero]
leftFoldFuncSafe (Right l:Right m:ms) IntDiv 	= Right (quot m l):ms
leftFoldFuncSafe _ _							= [Left InvalidInput]

--Question 4

rpnTrans :: PExp -> Either String String
rpnTrans p	= if length (foldl opToString [] p) == 1 then head (foldl opToString [] p) else Left "Bad Input"
opToString :: [Either String String] -> Op -> [Either String String]
opToString (Left s:ss) op					= [Left "Bad Input"]
opToString s (Val i)						= Right (show i):s
opToString [] op							= [Left "Bad Input"]
opToString (Right s:Right t:ts) Plus		= Right ("("++t++"+"++s++")"):ts
opToString (Right s:Right t:ts) Minus		= Right ("("++t++"-"++s++")"):ts
opToString (Right s:Right t:ts) Mul			= Right ("("++t++"*"++s++")"):ts
opToString (Right "0": Right t:ts) IntDiv	= [Left "DivByZero"]
opToString (Right s:Right t:ts) IntDiv		= Right ("("++t++"/"++s++")"):ts
opToString _ _								= [Left "Bad Input"]

--Question 5

fullTrans :: String -> Either String String
fullTrans s = rpnTrans (rpnParse s)
--Original Question 5

fullPreTrans :: String -> Either String String
fullPreTrans s	= if length (foldr opToStringPre [] (prefixParse s)) == 1 then head ( foldr opToStringPre [] (prefixParse s)) else Left "Bad Input"

prefixParse :: String -> PExp
prefixParse s	= map toPExp (words s)

opToStringPre :: Op -> [Either String String] -> [Either String String]
opToStringPre (Val i) s							= Right (show i):s
opToStringPre op []								= [Left "Bad Input"]
opToStringPre Plus (Right s:Right t:ts)			= Right ("("++s++"+"++t++")"):ts
opToStringPre Minus (Right s:Right t:ts)		= Right ("("++s++"-"++t++")"):ts
opToStringPre Mul (Right s:Right t:ts)			= Right ("("++s++"*"++t++")"):ts
opToStringPre IntDiv (Right s: Right "0":ts)	= [Left "DivByZero"]
opToStringPre IntDiv (Right s:Right t:ts)		= Right ("("++s++"/"++t++")"):ts 
opToStringPre _ _								= [Left "Bad Input"]