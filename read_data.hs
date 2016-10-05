#!/usr/bin/runhaskell

import HBatteries.Serial 
import HBatteries.Common 
import System.IO
import System.Environment
import Text.Read 
import qualified Data.ByteString.Char8 as B

import Graphics.Gnuplot.Simple 

str2Float :: String -> Double
str2Float x  = case readMaybe x of 
    Nothing -> 0.0
    Just x -> x

isDataLine line 
    |  length fields > 5 = True
    |  otherwise = False
    where fields = B.split ',' $ line 

lineToData line = map (\x -> str2Float $ B.unpack x ) $ take 2 $ B.split ',' $ line

readAndPlot usb = do 
    line <- readline usb
    if isDataLine line 
      then do 
        let d = lineToData line
        print d
      else do 
        print line 

main = do
    args <- getArgs
    s <- openSerial (args!!0) 38400
    mapM (\x -> readAndPlot s) [1..]
    closeSerial s
    putStrLn "All done"
