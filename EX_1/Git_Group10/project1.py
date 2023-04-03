def decimal_to_hexadecimal(decimal_num):
    # Convert decimal number to hexadecimal number
    if decimal_num == 0:
        return 0
    hexadecimal_num = ''
    while decimal_num > 0:
        remainder = decimal_num % 16
        if remainder < 10:
            hexadecimal_num = str(remainder) + hexadecimal_num
        else:
            hexadecimal_num = chr(remainder + 55) + hexadecimal_num
        decimal_num //= 16
    return hexadecimal_num

def hexadecimal_to_decimal(hexadecimal_num):
    # Convert hexadecimal number to decimal number
    if hexadecimal_num == "0":
        return 0
    decimal_num = 0
    power = len(hexadecimal_num) - 1
    for digit in hexadecimal_num:
        if digit.isnumeric():
            decimal_num += int(digit) * (16 ** power)
        else:
            decimal_num += (ord(digit) - 55) * (16 ** power)
        power -= 1
    return decimal_num

def checkHexInput(hexadecimal_num):
    #check if the hexadecimal input number is valid
    for digit in hexadecimal_num:
        if 48 <= ord(digit) <= 57 or 65 <= ord(digit) <= 70:
            continue
        elif 97 <= ord(digit) <= 102:
            print("Only Capital Letters")
            return False
        else:
            return False
    return True





while True:
    #prints menu
    print("Please select an operation:")
    print("1. Decimal to Hexadecimal")
    print("2. Hexadecimal to Decimal")
    print("3. Exit")

    choice = input("Enter your choice (1/2/3): ")

    if choice == '1': #option 1: convert Decimal to Hexadecimal
        try:
            num = input("Enter decimal number: ")
            if num[0] == '0' and len(num) > 1:# checks if first digit is 0
                print("First digit can't be 0")
                print()
                continue
            if num[0] == '-':# checks if input is positive
                print("Only positive numbers")
                print()
                continue
            decimal_num = int(num)
            hexadecimal_num = decimal_to_hexadecimal(decimal_num)
            print(f"Hexadecimal representation: {hexadecimal_num}")
            print()
        except:
            print("Invalid input, try again...")
            print()
    elif choice == '2': #option 2: Hexadecimal to Decimal
        try: 
            hexadecimal_num = input("Enter hexadecimal number: ")
            if hexadecimal_num[0] == '-':# checks if input is positive
                print("Only positive numbers")
                print()
                continue
            if not checkHexInput(hexadecimal_num): #checks if input is valid
                print("Invalid input")
                print()
                continue
            if hexadecimal_num[0] == '0' and len(hexadecimal_num) > 1:# checks if first digit is 0
                print("First digit can't be 0")
                print()
                continue
            decimal_num = hexadecimal_to_decimal(hexadecimal_num)
            print(f"Decimal representation: {decimal_num}")
            print()
        except:
            print("Invalid input, try again...")
            print()
    elif choice == '3':#option 3: exit the program
        break
    else:
        print("Invalid input")
        print()