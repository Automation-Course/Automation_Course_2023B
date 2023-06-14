# dictionary for conversion
conversion_dictionary = {0: '0', 1: '1', 2: '2', 3: '3',
                         4: '4', 5: '5', 6: '6', 7: '7',
                         8: '8', 9: '9', 10: 'A', 11: 'B',
                         12: 'C', 13: 'D', 14: 'E', 15: 'F'}


# function which converts decimal value to hexadecimal value
def decimalToHexadecimal(decimal: int):
    hexadecimal = ''
    while decimal > 0:
        remainder = decimal % 16
        hexadecimal = conversion_dictionary[remainder] + hexadecimal
        decimal = decimal // 16
    return hexadecimal


# function which converts hexadecimal value to decimal value
def hexadecimalToDecimal(hex_string):
    hex_chars = "0123456789abcdef"
    hex_string = hex_string.lower()
    decimal = 0

    # check if any char is hexadecimal
    for char in hex_string:
        if char in hex_chars:
            decimal = decimal * 16 + hex_chars.index(char)
        else:
            inp = input("Invalid input. Please provide a valid hexadecimal number.\n")
            hexadecimalToDecimal(inp)
    return decimal


# main
if __name__ == '__main__':
    option = input('select option:\n'
                   '1. Decimal To Hexadecimal\n'
                   '2. Hexadecimal To Decimal\n')
    while option != '1' and option != '2':
        option = input('invalide selection:\n'
                       '1. Decimal To Hexadecimal\n'
                       '2. Hexadecimal To Decimal\n')
    if option == '1':
        flag = True
        # while input not valid
        while flag:
            x = input('enter decimal:\n')
            # input need to be int
            try:
                x = int(x)
                print(decimalToHexadecimal(x))
                flag = False
            except:
                print("Invalid input.Please provide a valid decimal number.")
    if option == '2':
        hex = input("enter hexadecimal:\n")
        print(hexadecimalToDecimal(hex))




