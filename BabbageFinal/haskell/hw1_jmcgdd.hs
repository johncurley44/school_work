{---------------------------------------------------
John Curley - jmcgdd
CS4450 - Principles of Programming Languages
October 3, 2014
HW1
----------------------------------------------------}

module HW1_jmcgdd where

import Prelude


-- Question 1
fact :: Int -> Int
fact n			| n <= 0		= 1
				| otherwise		= n*(fact (n-1))
			
-- Dr. Harrison told me it was acceptable to set a limit on the input value based
--	on what my computer can handle before crashing and requested that I put my
--	computer specs here:
{-		
	Lenovo ideapad
	AMD- A8-3520M APU
	6GB RAM
-}
-- Question 2
fib :: Int -> Int
fib n			| n <= 0		= 0
				| n == 1		= 1
				| n > 35		= error "Number too high, please enter a value n <= 35"
				| otherwise		= fib(n-2) + fib(n-1)
			
-- Question 3
munge :: (Int->Int) -> (Int->Int) -> Int -> Int
munge f g n		| (mod n 2) == 0	= f n
				| otherwise			= g n

-- Question 4
mono :: (Int->Int) -> Int -> Int -> Bool
mono f x y		| x == y			= True
				| (f x)<=(f (x+1))	= mono f (x+1) y
				| (f x)>(f (x+1))	= False
				
-- Question 5
runAgain :: Int -> (a->a) -> (a->a)
runAgain n f	| n <= 0			= id
				| otherwise			= f.(runAgain (n-1) f)
				
-- Question 6
stutter :: Int -> [Char] -> [Char]
stutter n s 	| n <= 0			= s
				| otherwise			= s++(stutter (n-1) s)

