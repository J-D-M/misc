module MergeSort (mergeSort) where

-- Merge two sorted lists
merge :: Ord a => [a] -> [a] -> [a]
merge [] []         = []
merge [] (x:xs)     = x : merge [] xs
merge (x:xs) []     = x : merge xs []
merge (l:ls) (r:rs)
  | l < r     = l : merge ls (r:rs)
  | otherwise = r : merge (l:ls) rs

-- Divide into sublists and merge
mergeSort :: Ord a => [a] -> [a]
mergeSort ls
  | length ls == 1  = ls
  | otherwise       = merge left right
    where
      half  = length ls `div` 2
      left  = (mergeSort . take half) ls
      right = (mergeSort . drop half) ls
