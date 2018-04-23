
sep = '========================================================================'

def createHeading(test, title):
    print '\n', sep
    print 'Test ID = ', test
    print 'Test Title = ', title 

def showValues(expected, received):
    print 'Expected Value = ', expected
    print 'Received Value = ', received
    if expected == received: print 'Test Passed'
    else: print 'Test *** FAILED ***'

def createFooter():
    print sep