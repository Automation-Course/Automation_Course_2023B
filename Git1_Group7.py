# A symbol table that maps the decimal/hexadecimal characters to their matching values
symbols = {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, 'A':10, 'B':11, 'C':12 , 'D' :13 ,'E':14, 'F':15}

def hexToDecimal(hexNumber):
    """Convert Hexadecimal to Decimal"""
    if not checkHexadecimalInput(hexNumber):
        return "Not a valid hexadecimal string"
    sum = 0
    for c in hexNumber:
        sum *= 16
        sum += symbols[c]
    return sum

def decimaltoHex(decimalNumber):
    """Converts Decimal to Hexadecimal"""
    if not checkDecimalInput(decimalNumber):
        return "Not a valid decimal string"
    a = []
    answer = ""
    num = parseDecimal(decimalNumber)
    while num >= 16:
        mod = num % 16
        num = num // 16
        a.append(mod)
    a.append(num)
    a.reverse()
    for c in a:
       answer = answer + getKey(c)
    return answer

def parseDecimal(decimalString):
    """Parses the given decimal string to a decimal number"""
    if not checkDecimalInput(decimalString):
        return "Not a valid decimal string"
    sum = 0
    for c in decimalString:
        sum *= 10
        sum += symbols[c]
    return sum


def getKey(val):
    """Returns the key from the value"""
    for key, value in symbols.items():
        if val == value:
            return key
    return None


def checkDecimalInput(input):
    """Checks if the input is a valid decimal number"""
    for c in input:
        if (c not in symbols) or (symbols[c] < 0 or symbols[c] > 9):
            return False
    return True


def checkHexadecimalInput(input):
    """Checks if the input is a valid hexadecimal number"""
    for c in input:
        if c not in symbols:
            return False
    return True


def convertLoop():
    """Allows the user to convert from decimal to hex or from hex to decimal"""
    while True:
        baseInput = input("\nChoose your desired conversion:\n"
                          "1. Decimal(10) to Hexadecimal(16)\n"
                          "2. Hexadecimal(16) to Decimal(10)\n")
        if baseInput == "1":
            userInput = input("Enter your decimal number: ")
            while not checkDecimalInput(userInput):
                print("Invalid decimal number, try again.")
                userInput = input("Enter your decimal number: ")
            print(decimaltoHex(userInput))
            break
        elif baseInput == "2":
            userInput = input("Enter your hexadecimal number: ")
            while not checkHexadecimalInput(userInput.upper()):
                print("Invalid hexadecimal number, try again.")
                userInput = input("Enter your hexadecimal number: ")
            print(hexToDecimal(userInput.upper()))
            break
        else:
            print("Invalid input!")

def main():
    while True:
        convertLoop()
        continueInput = input("\nPress 'y' if you would you like to convert another number (or press any other key to exit)\n")
        if continueInput.lower() != 'y':
            break

main()