import pyautogui, sys

print('Press Ctrl-C to quit.')

x0, y0 = (960, 540)

try:
    while True:
        pyautogui.moveTo( x0, y0 )
        x, y = pyautogui.position()
        positionStr = 'X:' + str(x0-x).rjust(4) + ' Y:' + str(y0-y).rjust(4)
        print( positionStr )
except KeyboardInterrupt:
    print '\n'
