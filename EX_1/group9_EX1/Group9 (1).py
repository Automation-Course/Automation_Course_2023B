import sys


def convertLeftSideTo16(input):
    hexBaseLibrary = "0123456789ABCDEF" #all possible hex numbers
    hexOutput = ""
    if input == 0:
        return "0"
    while input > 0:
        remainder = input % 16
        hexOutput = hexBaseLibrary[remainder] + hexOutput
        input = int(input / 16)
    return(hexOutput)

def convertRightSideTo16(input):
    hexBaseLibrary = "0123456789ABCDEF" #all possible hex numbers
    hexOutput = ""
    counter = 3
    while counter > 0 and input != float(0):
        input = input * 16
        hexOutput = hexOutput + hexBaseLibrary[int(input)]
        input = float("0." + str(input).split(".")[1])
        counter = counter - 1
    return(hexOutput)

def base10to16():
    boolTenInput = False
    while boolTenInput == False:
        ten_input = input("Please enter number in base 10: ")
	#if ten_input[0] == "-":
	    #print("Please enter positive number only!)

        if "." in ten_input:
            input_split = ten_input.split(".")
            if len(input_split) != 2:
                print("Try again. Number can contain only 1 decimal ")
            else:
                whole_input = input_split[0] #left side of decimal
                decimal_input = input_split[1] #right side of decimal
                if whole_input.isdigit() == True and decimal_input.isdigit() == True:
                    boolTenInput = True
                    left = convertLeftSideTo16(int(whole_input))
                    right = convertRightSideTo16(float("0." + decimal_input))
                    print("Your number in base 16 is: " + left + "." + right)
                    menu()
                else:
                    print("Try again. Numbers only")

        elif ten_input.isdigit() == True:
            boolTenInput = True
            ten_input = int(ten_input)
            print("Your number in base 16 is: " + convertLeftSideTo16(ten_input))
            menu()

        else:
            print("Try again. Number is not in base 10")


def checkIfBase16(input):
    hexBaseLibrary = "0123456789ABCDEF" #all possible hex numbers
    for char in input:
        if char not in hexBaseLibrary:
            print("Number not in base 16!")
            return False
    return True

def convertLeftSideTo10(input):
    hexBaseLibrary = "0123456789ABCDEF"  # all possible hex numbers
    counter = len(input)
    ans = 0
    for char in input:
        ans = ((16 ** (counter - 1)) * hexBaseLibrary.index(char)) + ans
        counter = counter - 1
    return ans

def convertRightSideTo10(input):
    hexBaseLibrary = "0123456789ABCDEF"  # all possible hex numbers
    counter = -1 #right side of decimal starts with 16^-1
    ans = 0
    for char in input:
        ans = ((16 ** (counter)) * hexBaseLibrary.index(char)) + ans
        counter = counter - 1
    return ans

def base16to10():
    hexBaseLibrary = "0123456789ABCDEF" #all possible hex numbers
    bool16Input = False
    while bool16Input == False:
        sixteen_input = input("Please enter number in base 16: ")
	#if ten_input[0] == "-":
	    #print("Please enter positive number only!)

        if "." in sixteen_input:
            input_split = sixteen_input.split(".")
            if len(input_split) != 2:
                print("Try again. Number can contain only 1 decimal ")
            else:
                whole_input = input_split[0] #left side of decimal
                decimal_input = input_split[1] #right side of decimal
                if checkIfBase16(whole_input) == True and checkIfBase16(decimal_input) == True:
                    bool16Input = True
                    left = convertLeftSideTo10(whole_input)
                    right = convertRightSideTo10(decimal_input)
                    ans = left + right
                    print("Your number in base 10 is: " + str(ans))
                    menu()
                else:
                    print("Try again. Numbers only")

        elif checkIfBase16(sixteen_input) == True:
            print("Your number in base 10 is: " + str(convertLeftSideTo10(sixteen_input)))
            bool16Input = True
            menu()

        else:
            print("Try again. Number is not in base 16")


def menu():
    base_input = input("What would you like to do?\n  1: Base 10 to 16\n  2: Base 16 to 10\n  3: Exit\nEnter your option: ")
    boolInput = False
    while boolInput == False:
        if base_input.isdigit() == False:
            base_input = input("Please enter number only: ")
        else:
            base_input = int(base_input)
            if base_input not in [1, 2, 3]:
                base_input = input("Please enter number 1, 2, or 3 only: ")
            else:
                boolInput = True

    if base_input == 1:
        base10to16()

    elif base_input == 2:
        base16to10()

    else:
        print("Goodbye")
        sys.exit()


print("Welcome to 10/16 Base Calculator!")
menu()