module File_System where

import System.IO
import Control.Monad



firstStar = do
         contents <- readFile "file.in"  --file.in
         print $ checkSum $ restructure (countNums $ rewrite $ toInt $ (reverse . tail . reverse) contents) $ rewrite $ toInt $ (reverse . tail . reverse) contents


secondStar = do
         contents <- readFile "file.in"
         print $ checkSum $ restructure2 $ rewrite $ toInt $ (reverse . tail . reverse) contents


mult :: Int -> Int -> [Int]
mult x y = [x | _ <- [1..y]]


countNums :: [Int] -> Int
countNums xs = length $ filter (>=0) xs


toInt :: String -> [Int]
toInt xs = [(read :: String -> Int) [c] | c <- xs]


rewrite :: [Int] -> [Int]
rewrite xs = helper xs [] True 0
               where helper [] ys _ _ = ys
                     helper (x:xs) ys True ind = helper xs (ys ++ mult ind x) False (ind + 1)
                     helper (x:xs) ys False ind = helper xs (ys ++ mult (-1) x) True ind


popNegative :: [Int] -> [Int]
popNegative (x:xs) | x == -1 = popNegative xs
                   | otherwise = xs


firstNum :: [Int] -> Int
firstNum (x:xs) | x >= 0 = x
                | otherwise = firstNum xs


restructure :: Int -> [Int] -> [Int]
restructure a xs = helper (reverse xs) xs []
                  where helper toPut (x:xs) new | length new == a = new
                                                | x == -1 = helper (popNegative toPut) xs (new ++ [firstNum toPut])
                                                | otherwise = helper toPut xs (new ++ [x])


getBlockLength :: Int -> [Int] -> Int
getBlockLength x xs = length $ filter (==x) xs

getBlockIndex :: Int -> [Int] -> Int
getBlockIndex a xs = head [i | (x, i) <- zip xs [0..], x == a]

firstFree :: Int -> [Int] -> Int
firstFree a xs = helper a xs 0
                   where helper _ [] ind = ind
                         helper a (x:xs) ind | take a xs == mult (-1) a = ind
                                             | otherwise = helper a xs (ind + 1)


moveBlock :: Int -> [Int] -> [Int]
moveBlock num xs | firstFree (getBlockLength num xs) xs >= getBlockIndex num xs = xs
                 | otherwise = take (firstFree (getBlockLength num xs) xs + 1) xs ++ mult num (getBlockLength num xs) ++ drop (getBlockLength num xs + firstFree (getBlockLength num xs) xs + 1) (take (getBlockIndex num xs) xs) ++ mult (-1) (getBlockLength num xs)++ drop (getBlockIndex num xs + getBlockLength num xs) xs


getLastIndex :: [Int] -> Int
getLastIndex xs = helper xs 0
                    where helper [] num = num
                          helper (x:xs) num = helper xs (max x num)


restructure2 :: [Int] -> [Int]
restructure2 xs = helper (getLastIndex xs) xs
                    where helper 0 ys = ys
                          helper num ys = helper (num - 1) (moveBlock num ys)


checkSum :: [Int] -> Int
checkSum xs = sum [max x 0 * y | (x, y) <- zip xs [0..]]
