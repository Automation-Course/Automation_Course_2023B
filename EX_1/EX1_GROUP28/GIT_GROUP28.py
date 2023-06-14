def get_numeric(dig): #Returns the number corresponding to the letter in the hexadecimal number
    if dig.lower() == "a":
        return 10
    if dig.lower() == "b":
        return 11
    if dig.lower() == "c":
        return 12
    if dig.lower() == "d":
        return 13
    if dig.lower() == "e":
        return 14
    if dig.lower() == "f":
        return 15
    return dig

def get_sighn(dig): #Returns the number/letter corresponding to the number of powers of 16 entered in the number
    if dig == 10:
        return "A"
    if dig == 11:
        return "B"
    if dig == 12:
        return "C"
    if dig == 13:
        return "D"
    if dig == 14:
        return "E"
    if dig == 15:
        return "F"
    return str(dig)

def check_if_number_is_integer(input): #Returns true if all chars are digits and false otherwise
    try:
        val = int(input)
    except ValueError:
        try:
            val = float(input)
        except ValueError:
            return False
    if float(input) < 0:
        print("The calculator only converts positive numbers")
        return False
    return True


def check_hex(number):  #Checks if the number contains only digits, period or letters between A and F
    good_dig = ['a', 'b', 'c', 'd', 'e', 'f']
    for dig in number:
        if dig == ".":#If contains a dot - OK, continue checking the rest of the number
            continue
        elif not check_if_number_is_integer(dig):#if dig not int
            if dig.lower() not in good_dig: #If not between A and F
                print("the number is not correct positive Hexadecimal number: chars only between A to F and no '-'")
                return(False) #Not an hexadecimal number
                break
    return(True) #hexadecimal number


def hex_to_dec(number): #convert hexadecimal number to decimal number
    ans = 0
    if "." in number: #If not an integer
        point_index = number.index(".")
        number_length = len(number)
        numbers_after_point = number_length - point_index - 1 # What is the lowest power that needs to be multiplied by
        while number[-1] != ".":#As long as we calculate the number after the point
            now = int(get_numeric(number[-1])) #The last digit in the hexadecimal number
            ans += now*(16*(numbers_after_point*(-1))) #Add the value of the number in decimal base to the answer
            number = number[:-1] #remove the last digit from the hexadecimal number
            numbers_after_point -= 1 #increases the power
        number = number[:-1] #remove the dot
    highest_power = int(len(number) - 1) #highest power for Integer
    while len(number) > 0:#befor point starts from highest power
        now = int(get_numeric(number[0])) #The first digit in the hexadecimal number
        ans += now * (16 ** highest_power) #Add the value of the number in decimal base to the answer
        number = number[1:]# #remove the first digit from the hexadecimal number
        highest_power -= 1 #decreases the power
    return ans

def dec_to_hex(number): #convert decimal number to hexadecimal number
    if '.' in number: #If not an integer
        if int(number[number.index('.') + 1 :]) > 0: #if after not dot only zeros
            number = float(number)
    else:
        number = int(number)
    ans = []
    i = 0
    while 16**(i+1) <= number: #What is the largest power of 16 that fits into the number
        i += 1
    while number > 0: #As long as we haven't reset the decimal number
        if i == -1: #If you reach the -1 power, put a period first
            ans.append(".")
        ans.append(0) #Add a digit to the result
        if number - 16**i >= 0: #If the current power of 16 is entered in the decimal number Count how many times
            count = 1
            number -= 16 ** i
            while number - 16 ** i >= 0:
                count += 1
                number -= 16 ** i
            ans[-1] = get_sighn(count) # Check what the number is in hexadecimal base and add to the answer
        i -= 1
    return ''.join(ans) #Convert list to string and return

def get_base(): #Get a base to convert and validate
    print("From which base to which base would you like to calculate?\nplease choose option:")
    print("1. from 10 to 16\n2. from 16 to 10")
    while True:
        option = input()
        if option != '1' and option != '2':
            print("invalid option choice\nplease choose 1 or 2:")
            continue
        break
    if int(option) == 1:
        return 10
    return 16


def get_number(fromm): #Get number to convert and validate
    while True:
        print("please insert number to convert:")
        number = input()
        if int(fromm) == 10 and not check_if_number_is_integer(number):
            print("the number is not positive decimal number, please try again")
            continue
        if int(fromm) == 16 and not check_hex(number):
            continue
        break
    return number


def calculator(number,fromm ,to): #convert the number according to user's request
    if fromm == '16' and to == '10':
        print("the number in decimal is: " + str(hex_to_dec(number)))
    if fromm == '10' and to == '16':
        print("the number in Hexadecimal base is: " + str(dec_to_hex(number)))

while True:
    fromm = get_base()
    number = get_number(fromm)
    if fromm == 10:
        calculator(str(number), '10', '16')
    else:
        calculator(str(number), '16', '10')
    while True:
        print("To convert another number press 1, to finish press 0")
        choise = input()
        if choise == '0':
            print("goodbye")
        elif choise != '1':
            print("Please choose from the options offered")
            continue
        break
    if choise == '0':
        break

print(calculator("123a", 16, 10))




        