module HeapSort (heapSort) where

-- Swap indices
swap :: Ord a => [a] -> Int -> Int -> [a]
swap ls i1 i2
  | i1 == i2  = ls
  | otherwise = front ++ mid ++ back
  where
    [a, b] = if i1 < i2 then [i1, i2] else [i2, i1]
    front  = (take a ls) ++ [ls !! b]
    mid    = (take (b - a - 1) . drop (a + 1)) ls
    back   = (ls !! a) : drop (b + 1) ls

-- Return index with largest element
largestIndex :: Ord a => [a] -> [Int] -> Int -> Int
largestIndex ls is size = (snd . maximum) [(ls !! x, x) | x <- is, x < size]

-- Make parent and nodes follow max-heap property
maxHeapify :: Ord a => [a] -> Int -> Int -> [a]
maxHeapify ls size parent
  | parent  >= size    = ls
  | largest == parent  = ls
  | otherwise          = maxHeapify swapped size largest
  where
    lChild  = parent * 2
    rChild  = parent * 2 + 1
    largest = largestIndex ls [parent, lChild, rChild] size
    swapped = swap ls parent largest

-- maxHeapify list
buildMaxHeap :: Ord a => [a] -> Int -> [a]
buildMaxHeap ls i
  | i == 0    = mheap
  | otherwise = buildMaxHeap mheap (i - 1)
  where
    mheap = maxHeapify ls (length ls) i

-- Push largest element to back and heapify rest of elements
heapSort' :: Ord a => [a] -> Int -> [a]
heapSort' list 0     = list
heapSort' list index = heapSort' heapified (index - 1)
  where
    swapped   = swap list 0 index
    heapified = maxHeapify swapped index 0

heapSort :: Ord a => [a] -> [a]
heapSort ls  = heapSort' (buildMaxHeap ls mid) size
  where
    size = length ls - 1
    mid  = div size 2
