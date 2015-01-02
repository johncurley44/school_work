{---------------------------------------------------
John Curley - jmcgdd
CS4450 - Principles of Programming Languages
September 11, 2014
HW0
----------------------------------------------------}

{-
-- practice problem 
square :: Integer -> Integer
square x = x * x

smaller :: (Integer, Integer) -> Integer
smaller (x, y) = if x <= y then x else y
-}

module Hw0_jmcgdd where

import Prelude
import Data.Char


--Question 1

nextlet :: Char -> Char
nextlet l 	| not(isAlpha(l))			= l
			| l == 'z'					= 'a'
			| l == 'Z'					= 'A'
			| otherwise					= chr((ord(l)+1))


--Question 2

digitval :: Char -> Int
digitval d	| not(isDigit(d))			= -1
			| otherwise					= digitToInt(d)
			
--Question 3

twine :: (a -> b) -> (a -> c) -> a -> (b,c)
twine f g a = (f(a), g(a))

--Question 4

cond :: Bool -> a -> a -> a
cond p x y	| p				= x
			| otherwise		= y
			
--Question 5

age :: (Int, Int, Int) -> (Int, Int, Int) -> Int
age (d1, m1, y1) (d2, m2, y2)	| (m2 > m1)					= (y2 - y1)
								| (m2 == m1) && (d2 >= d1)	= (y2 - y1)
								| otherwise					= (y2 - y1 - 1)
								
f2 :: (f -> a -> b) -> f -> a -> b
f2 f a b = f a b