import pyautogui
import sys

x0, y0 = (960, 540)

def main( ):
    try:
        while True:
            pyautogui.moveTo( x0, y0 )
            x, y = pyautogui.position()
            print( x, y )
    except KeyboardInterrupt:
        print( 'Received interrupt' )
        quit(1)

if __name__ == '__main__':
    main()
