{---------------------------------------------------
John Curley - jmcgdd
CS4450 - Principles of Programming Languages
October 6, 2014
HW2
----------------------------------------------------}

module HW2_jmcgdd where

import Prelude

-- Question 1
data Bool3 = F | T | U
	deriving (Eq, Show)
	
-- Question 2
not' :: Bool3 -> Bool3
not' U		= U
not' F		= T
not' T		= F

and', or', xor', nor', nand'  :: Bool3 -> Bool3 -> Bool3
--Somehow merge mirror cases? (and' U x/and' x U)
and' U T		= U
and' U x		= x
and' T U		= U
and' x U		= x
and' T x		= x
and' F x		= F

or' U T			= T
or' U x			= x
or' T U			= T
or' x U			= x
or' T x			= T
or' F x			= x

xor' U x		= U
xor' x U		= U
xor' T x		= not' x
xor' F x		= x

nor' x y		= not' (or' x y)

nand' x y		= not' (and' x y)

-- Question 3
-- i.e. all inputs/output are of type Bool3 right? (or functions that only deal with Bool3?
-- L/R ever different?
toTernaryL :: (Bool3 -> Bool3 -> Bool3) -> Bool3 -> Bool3 -> Bool3 -> Bool3
toTernaryL f p q r		= f (f p q) r

--toTernaryR :: (Eq p, Eq q, Eq r) => (Bool3 -> Bool3 -> Bool3) -> p -> q -> r -> Bool3
toTernaryR :: (Bool3 -> Bool3 -> Bool3) -> Bool3 -> Bool3 -> Bool3 -> Bool3
toTernaryR f p q r		= f p (f q r)

-- Question 4

equiv1 :: (Bool3 -> Bool3) -> (Bool3 -> Bool3) -> Bool
equiv1 f g		| (f T == g T) && (f F == g F) && (f U == g U)		= True
				| otherwise											= False

equiv2 :: (Bool3 -> Bool3 -> Bool3) -> (Bool3 -> Bool3 -> Bool3) -> Bool
equiv2 f g		| equiv1 (f T) (g T) && equiv1 (f F) (g F) && equiv1 (f U) (g U)	= True
				| otherwise															= False

equiv3 :: (Bool3 -> Bool3 -> Bool3 -> Bool3) -> (Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool
equiv3 f g		| equiv2 (f T) (g T) && equiv2 (f F) (g F) && equiv2 (f U) (g U)	= True
				| otherwise															= False
				
-- Question 5
assoc :: (Bool3 -> Bool3 -> Bool3) -> Bool
assoc f			| equiv3 (toTernaryL f) (toTernaryR f)	= True
				| otherwise								= False

-- Question 6
moreThanTernaryL :: (Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3
moreThanTernaryL f a b c d e	= f (f a b c) d e

moreThanTernaryR :: (Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3
moreThanTernaryR f a b c d e	= f a b (f c d e)

moreThanTernaryC :: (Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3
moreThanTernaryC f a b c d e	= f a (f b c d) e

equiv4 :: (Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3) -> (Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool
equiv4 f g		| equiv3 (f T) (g T) && equiv3 (f F) (g F) && equiv3 (f U) (g U)	= True
				| otherwise															= False
								
equiv5 :: (Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3) -> (Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool
equiv5 f g		| equiv4 (f T) (g T) && equiv4 (f F) (g F) && equiv4 (f U) (g U)	= True
				| otherwise															= False
				
assoc3 :: (Bool3 -> Bool3 -> Bool3 -> Bool3) -> Bool
assoc3 f		| (equiv5 (moreThanTernaryL f) (moreThanTernaryR f)) && (equiv5 (moreThanTernaryL f) (moreThanTernaryC f))	= True
				| otherwise																									= False