module Path_Find where

import System.IO
import Control.Monad



firstStar = do
         contents <- readFile "equats.in"  --equats.in
         print $ sum $ map checkEqua $ splitLines $ splitInput contents


secondStar = do
         contents <- readFile "equats.in"
         print $ addEquas $ splitLines $ splitInput contents


-- SOF ftw
wordsWhen     :: (Char -> Bool) -> String -> [String]
wordsWhen p s =  case dropWhile p s of
                      "" -> []
                      s' -> w : wordsWhen p s''
                            where (w, s'') = break p s'



splitInput :: String -> [String]
splitInput = wordsWhen (=='\n')


type Equa = (Int, [Int])


splitLine :: String -> Equa
splitLine xs = (read (head $ wordsWhen (==':') xs) :: Int, map (read :: String -> Int) $ wordsWhen (==' ') ((wordsWhen (==':') xs)!!1))

splitLines :: [String] -> [Equa]
splitLines = map splitLine

concatenation :: Int -> Int -> Int
concatenation a b = read $ show a ++ show b :: Int


-- 0 if not possible, otherwise return the Int
checkEqua :: Equa -> Int
checkEqua (num, xs) = if helper num xs (*) 1 || helper num xs (+) 0 then num else 0
                      where helper num [] _ res = num == res
                            helper num ls op res = helper num (tail ls) (*) (res `op` (head ls)) || helper num (tail ls) (+) (res `op` (head ls))

checkEqua2 :: Equa -> Int
checkEqua2 (num, xs) = if helper num xs (*) 1 || helper num xs (+) 0 || helper num xs concatenation 0 then num else 0
                      where helper num [] _ res = num == res
                            helper num ls op res = helper num (tail ls) (*) (res `op` (head ls)) || helper num (tail ls) (+) (res `op` (head ls)) || helper num (tail ls) concatenation (res `op` (head ls))


addEquas :: [Equa] -> Int
addEquas es = sum $ map checkEqua2 es
