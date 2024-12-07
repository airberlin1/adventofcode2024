module Path_Find where

import System.IO
import Control.Monad
import Data.List


-- it misses a few loops that are caused by the new obstacle, python program is correct :(
main = do
         contents <- readFile "map.in"
         print $ countNewObstacles (nub $ fst $ replaceMapX ((-5, -5), (0, -1)) (getFirstPos $ splitInput contents) $ splitInput contents) $ splitInput contents --first star


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

checkDirs :: Direction -> [Direction]
checkDirs dir = [dir, turnRight dir]


replaceMapX :: Direction -> Direction -> [String] -> ([Direction], Bool)
replaceMapX check_dir dir xs = helper False dir xs [] 0
               where helper True _ _ v _ = (v, False)
                     helper _ _ _ v 50000 = (v, True)
                     helper _ dir xs v cnt = if getRealNextPos xs dir `elem` (checkDirs check_dir) then (v, True) else helper (isUnallowedPos $ getRealNextPos xs dir) (getRealNextPos xs dir) xs (dir: v) (cnt + 1)


countVisits :: [Direction] -> Int
countVisits v = sum $ [1 | i <- nub v]


countX :: [String] -> Int
countX xs = sum $ map sumX xs
        where sumX cs = sum [1 | c <- cs, c == 'X']


visitsHaveLoop :: [Pos] -> Bool
visitsHaveLoop v = or [(drop i v) == (take i $ drop (2 * i) v) | i <- [1..480]]


reduceToPos :: [Direction] -> [Pos]
reduceToPos xs = [pos | (pos, dir) <- xs]


checkLoop :: Direction -> [String] -> Bool
checkLoop dir xs = snd $ replaceMapX dir (turnRight dir) xs -- chech here for harder to find loops


countNewObstacles :: [Direction] -> [String] -> Int
countNewObstacles dir xs = sum [1 | i <- nub $ reduceToPos (helper xs dir []), i /= fst (getFirstPos xs) ]
                      where helper xs dirs d2 | null dirs = d2
                                              | isUnallowedPos (getNextPos (head dirs)) = helper xs (tail dirs) d2
                                              | charAtPos (getNextPos (head dirs)) xs == '#' = helper xs (tail dirs) d2
                                              | checkLoop (head dirs) xs = helper xs (tail dirs) (getNextPos (head dirs) : d2)
                                              | otherwise = helper xs (tail dirs) d2
