#!/usr/bin/runhaskell

import HBatteries.Serial 
import HBatteries.Common 
import System.IO
import System.Environment
import Text.Read 
import Data.Time
import qualified Data.ByteString.Char8 as B
import System.Process
import Control.Concurrent
import Text.Printf


outfile = "sensor.dat"

str2Float :: String -> Double
str2Float x  = case readMaybe x of 
    Nothing -> 0.0
    Just x -> x

isDataLine line 
    |  length fields > 5 = True
    |  otherwise = False
    where fields = B.split ',' $ line 

lineToData line = case B.stripSuffix (B.singleton '\r') line of 
    Nothing -> line 
    Just l -> B.snoc l '\n'

readSaveAndPlot usb gnuplot datafile n = do 
    line <- readline usb
    if isDataLine line 
      then do 
        let d = lineToData line
        let fields = map (B.unpack) $ B.split ',' d 
        B.appendFile datafile d
        -- plot at every 100'th time step.
        if mod n 10 == 0 then do
            -- Write data to gnuplot pipe
            let title = printf "Title = %s, State =%s" (fields!!2) (last fields) 
            hPutStrLn gnuplot $ "set title \"" ++ title ++ "\""
            hPutStrLn gnuplot "plot \"< tail -n 1000 ./sensor.dat\" using 2 with lines" 
        else
            return ()
        print d
      else do 
        print line 

main = do
    args <- getArgs
    t <- getCurrentTime
    B.writeFile outfile $ B.pack $ "# Timestamp " ++ show t 
    s <- openSerial (args!!0) 38400
    (inp, out, err, p) <- runInteractiveProcess "gnuplot" [ ] Nothing Nothing
    hSetBuffering inp LineBuffering
    hSetBinaryMode inp False
    hPutStrLn inp "set terminal x11" 
    hPutStrLn inp "set datafile separator \",\""
    {-hPutStrLn inp "plot \"< tail -n 1000 ./sensor.dat\" using 2 with lines" -}
    {-hPutStrLn inp "pause 1; reread"-}
    mapM (\x -> readSaveAndPlot s inp outfile x) [1..]
    closeSerial s
    terminateProcess p
    putStrLn "All done"
