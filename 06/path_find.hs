module Path_Find where

import System.IO
import Control.Monad
import Data.List

main = do
         contents <- readFile "map.in"
         print $ countVisits $ replaceMapX $ splitInput contents


-- SOF ftw
wordsWhen     :: (Char -> Bool) -> String -> [String]
wordsWhen p s =  case dropWhile p s of
                      "" -> []
                      s' -> w : wordsWhen p s''
                            where (w, s'') = break p s'

type Pos = (Int, Int)
type Direction = (Pos, Pos)


turnRight :: Direction -> Direction
turnRight (pos, dir) | dir == (1, 0) = (pos, (0, 1))
                     | dir == (0, 1) = (pos, (-1, 0))
                     | dir == (-1, 0) = (pos, (0, -1))
                     | dir == (0, -1) = (pos, (1, 0))


charAtPos :: Direction -> [String] -> Char
charAtPos ((x, y), _) xs = (xs!!y)!!x


getNextPos :: Direction -> Direction
getNextPos ((x, y), (a, b)) = ((x + a, y + b), (a, b))


getRealNextPos :: [String] -> Direction -> Direction
getRealNextPos xs dir | isUnallowedPos $ getNextPos dir = getNextPos dir
                      | charAtPos (getNextPos dir) xs == '#' = getRealNextPos xs $ turnRight dir -- turn
                      | otherwise = getNextPos dir


getFirstPos :: [String] -> Direction
getFirstPos xs = head [((i, j), (0, -1)) |  (s, j) <- zip xs [0..], (c, i) <- zip s [0..], c == '^']



--replaceX :: Direction -> [String] -> [String]
--replaceX ((x, y), _) xs =


splitInput :: String -> [String]
splitInput = wordsWhen (=='\n')


isUnallowedPos :: Direction -> Bool
isUnallowedPos (pos, _) | fst pos < 0 = True
                        | snd pos < 0 = True
                        | fst pos > 129 = True
                        | snd pos > 129 = True
                        | otherwise = False


replaceMapX :: [String] -> [Pos]
replaceMapX xs = helper False (getFirstPos xs) xs []
               where helper True _ _ v = v
                     helper _ dir xs v = helper (isUnallowedPos $ getRealNextPos xs dir) (getRealNextPos xs dir) xs (fst dir: v)


countVisits :: [Pos] -> Int
countVisits v = sum $ [1 | i <- nub v]


countX :: [String] -> Int
countX xs = sum $ map sumX xs
        where sumX cs = sum [1 | c <- cs, c == 'X']
