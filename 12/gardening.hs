
module Main where
-- yeah ok let's not actually do that
main = do
      contents <- readFile "test.in"
      print $ splitInput contents --first star


-- SOF ftw
wordsWhen     :: (Char -> Bool) -> String -> [String]
wordsWhen p s =  case dropWhile p s of
                      "" -> []
                      s' -> w : wordsWhen p s''
                            where (w, s'') = break p s'

type Pos = (Int, Int)
type Direction = (Pos, Pos)

splitInput :: String -> [String]
splitInput = wordsWhen (=='\n')
