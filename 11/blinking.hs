module Main where

import System.IO
import Control.Monad
import Data.Map (Map)
import Useful.Dictionary

data Tree a = Leaf a | Node (Tree a) (Tree a)

main :: IO ()
main = do
  resultFirst <- firstStar
  print resultFirst
  resultSecond <- secondStar
  print resultSecond




firstStar = do
         contents <- readFile "stones.in"  --file.in
         return $ doTheBlinks 25 $ toInt $ splitInput $ (reverse . tail . reverse) contents


secondStar = do
         contents <- readFile "stones.in"
         return $ doTheBlinks 75 $ toInt $ splitInput $ (reverse . tail . reverse) contents


-- SOF ftw
wordsWhen     :: (Char -> Bool) -> String -> [String]
wordsWhen p s =  case dropWhile p s of
                      "" -> []
                      s' -> w : wordsWhen p s''
                            where (w, s'') = break p s'



splitInput :: String -> [String]
splitInput = wordsWhen (==' ')


toInt :: [String] -> [Int]
toInt = map (read :: String -> Int)


evenDigits :: Int -> Bool
evenDigits num = even (numDigits2 num)


numDigits :: Int -> Int
numDigits num = helper num 1
                  where helper num n | num `div` 10 == 0 = n
                                     | otherwise = helper (num `div` 10) n+1
-- learning:
numDigits2 :: Int -> Int
numDigits2 num = length $ show num

power :: Int -> Int -> Int
power 1 num = num
power n num = num * power (n-1) num



splitNum :: Int -> Int -> (Int, Int)
splitNum splitInd num = divMod num (power splitInd 10)


-- well this isn't an improvement over the previous implementation obviously upsi
splitNum2 :: Int -> Int -> [Int]
splitNum2 m n = [fst $ splitNum m n, snd $ splitNum m n]


-- trying to optimize blinking a bit, decent idea with bad implementation
blink :: Int -> Int -> Int
blink 0 _ = 1
blink blinksLeft 0 | blinksLeft >= 4 = 2 * (blink (blinksLeft - 4) 2) + blink (blinksLeft - 4) 4 + blink (blinksLeft - 4) 0
                   | otherwise = blink (blinksLeft - 1) 1
blink blinksLeft 1 | blinksLeft >= 3 = blink (blinksLeft + 1) 0
                   | otherwise = blink (blinksLeft - 1) 2024
blink blinksLeft 2 | blinksLeft >= 3 = 2 * (blink (blinksLeft -3) 4) + blink (blinksLeft - 3) 8 + blink (blinksLeft -3) 0
                   | otherwise = blink (blinksLeft - 1) 4048
blink blinksLeft 4 | blinksLeft >= 3 = blink (blinksLeft - 3) 8 + blink (blinksLeft - 3) 0 + blink (blinksLeft - 3) 9 + blink (blinksLeft - 3) 6
                   | otherwise = blink (blinksLeft - 1) 8096
blink blinksLeft num | evenDigits num = blink (blinksLeft - 1) (fst $ splitNum (numDigits num `div` 2) num) + blink (blinksLeft - 1) (snd $ splitNum (numDigits num `div` 2) num)
                     | otherwise = blink (blinksLeft - 1) (num * 2024)


individualBlink :: Int -> [Int]
individualBlink n | n == 0 = [1]
                  | evenDigits n = splitNum2 (numDigits2 n `div` 2) n
                  | otherwise = [2024 * n]

-- after cheating a bit: trying to learn dictionaries in haskell
blink2 :: Int -> Map Int Int -> Int
blink2 0 dic = sum [x | (_, x) <- dictToList dic]
blink2 n dic = blink2 n $ undefined


doTheBlinks :: Int -> [Int] -> Int
doTheBlinks n xs = sum [blink n x | x <- xs]


doTheBlinks2 :: Int -> [Int] -> Int
doTheBlinks2 n xs = blink2 n $ dict $ [(x, 1) | x <- xs]
