{---------------------------------------------------
John Curley - jmcgdd
CS4450 - Principles of Programming Languages
October 6, 2014
HW4
----------------------------------------------------}

module HW4_jmcgdd where

import Prelude
import PropLogic
import Control.Monad
import Data.List

--Question 1
liftAppend :: Maybe [Var] -> Maybe [Var] -> Maybe [Var]
liftAppend = liftM2 (++)

liftNub :: Maybe [Var] -> Maybe [Var]
liftNub = liftM nub

freeVars :: String -> Maybe [Var]
freeVars s			= case	(parse s) of
							Just (Atom a)		->	Just [a]
							Just (Not a)		->	liftNub (freeVars (show a))
							Just (And a b)		->	liftNub (liftAppend (freeVars (show a)) (freeVars (show b)))
							Just (Or a b)		->	liftNub (liftAppend (freeVars (show a)) (freeVars (show b)))
							Just (Imply a b)	->	liftNub (liftAppend (freeVars (show a)) (freeVars (show b)))
							Just (Iff a b)		->	liftNub (liftAppend (freeVars (show a)) (freeVars (show b)))
							otherwise			->	Nothing
							
							
--Question 2
liftAnd :: Maybe Bool -> Maybe Bool -> Maybe Bool
liftAnd = liftM2 (&&)

liftOr :: Maybe Bool -> Maybe Bool -> Maybe Bool
liftOr = liftM2 (||)

liftImply :: Maybe Bool -> Maybe Bool -> Maybe Bool
liftImply = liftM2 (<=)

liftEqual :: Maybe Bool -> Maybe Bool -> Maybe Bool
liftEqual = liftM2 (==)

liftNot :: Maybe Bool -> Maybe Bool
liftNot = liftM not

evalProp :: [(Var, Bool)] -> String -> Maybe Bool
evalProp p s		= 	case	(parse s) of
							Just (Atom a)		->	lookup a p
							Just (Not a)		->	liftNot (evalProp p (show a))
							Just (And a b)		->	liftAnd (evalProp p (show a)) (evalProp p (show b))
							Just (Or a b)		->	liftOr (evalProp p (show a)) (evalProp p (show b))
							Just (Imply a b)	->	liftImply (evalProp p (show a)) (evalProp p (show b))
							Just (Iff a b)		->	liftEqual(evalProp p (show a)) (evalProp p (show b))
							otherwise			->	Nothing

--Question 3 
--Could not get this to work, but if there is partial credit here is an explanation of what I tried to do with some of the functions
--		I attempted to create/use below.
--
--Explanation: I tried to make the helper function boolMap to create all possible combinations of boolean values given a certain length
-- 				of a list (specifically the list of free variables from freeVars). Then I tried to zip each of them individually with a
--				a copy of the freeVars result. Then I wanted to check to make sure each were true and return Just False if any of them
--				returned false, and Just True if they all returned True.


{-tautHelper :: String -> Var
tautHelper s		= case	(parse s) of
						Just (Atom a)			-> a 
						Just (And a b)			-> evalProp ( [tautHelper (show a)
liftZip :: Maybe [a] -> Maybe [b] -> Maybe [(a,b)] 
liftZip = liftM2 zip

liftLength :: Maybe [a] -> Maybe Int
liftLength = liftM length

liftMap :: Maybe (a -> b) -> Maybe [a] -> Maybe [b]
liftMap = liftM2 map
						
boolMap :: Int -> [[Bool]]
boolMap	0			=  [[]]
boolMap n		=  map (False:) bss ++ map (True:) bss
                                 where bss = boolMap (n-1)
								 

varsWithBools :: String -> Int -> Maybe [[Bool]] -> Maybe Bool
varsWithBools s n (b:bs)		| n > 1			= liftAnd (evalProp (liftZip (freeVars s) b) s) (varsWithBools s (n-1) bs)
								| n == 1		= evalProp ((liftZip (freeVars s)) b) s

liftBoolMap :: Maybe Int -> Maybe [[Bool]]
liftBoolMap = liftM boolMap

isTautology :: String -> Maybe Bool
isTautology s		= 	varsWithBools s len (liftBoolMap (Just len))
						where len = liftLength (freeVars s)

freeVarsList :: String -> Int -> [Maybe [Var]]
freeVarsList s n	| n>1		= [freeVars s]
					| otherwise	= liftAppend ([freeVars s]) (freeVarsList s (n-1))

evalBuilder :: String -> Maybe [(Var, Bool)]
evalBuilder s		= 	liftMap (liftZip fv) (liftBoolMap (liftLength fv))
						where fv = freeVars s

isTautology :: String -> Maybe Bool
isTautology s		= evalProp (evalBuilder s) s-}
								 
{-isTautology :: String -> Maybe Bool
isTautology s		= 	case	(parse s) of
							Just (Atom a)		->	(Atom a)
							Just (Not a)		->	liftNot (isTautology (show a))
							Just (And a b)		->	liftAnd (isTautology (show a)) (isTautology (show b))
							Just (Or a b)		->	liftOr (isTautology (show a)) (isTautology (show b))
							Just (Imply a b)	->	liftImply (isTautology (show a)) (isTautology (show b))
							Just (Iff a b)		->	liftEqual (isTautology (show a)) (isTautology (show b))
							otherwise			->	Nothing -}