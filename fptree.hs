import Prelude hiding (lines, words, readFile)

import qualified Data.Text.Lazy as T
import Data.Text.Lazy.IO (readFile)
import qualified Data.HashTable.IO as M
import Control.Monad
import System.Exit
import Data.IORef
import System.Environment

type Histogram = M.CuckooHashTable T.Internal.Text Int



-- Read lines in a file and make a histogram
main = do
    [filename] <- getArgs
    content <- readFile filename
    hist <- M.new
    
    forM (T.lines content) $ \line ->
        forM (T.words line) $ \word -> do
            count <- M.lookup hist word
            M.insert hist word (maybe 1 (+1) count)
    print hist
    exitSuccess
    