def dec_to_hex(num):
    hexa = ""
    while num > 0:
        whole = num // 16
        remainder = num % 16
        hexa = ''.join((number_to_letter(remainder), hexa))
        num = whole
    print(hexa)


def hex_to_dec(num):
    count = len(num) - 1
    hexnum = 0
    for letter in num:
        hexnum += int(letter_to_number(letter)) * (16**count)
        count -= 1
    print(hexnum)


def number_to_letter(number):
    if number == 10:
        return "A"
    elif number == 11:
        return 'B'
    elif number == 12:
        return 'C'
    elif number == 13:
        return 'D'
    elif number == 14:
        return 'E'
    elif number == 15:
        return 'F'
    else:
        return str(number)


def letter_to_number(letter):
    if letter == 'a' or letter == 'A':
        return 10
    elif letter == 'b' or letter == 'B':
        return 11
    elif letter == 'c' or letter == 'C':
        return 12
    elif letter == 'd' or letter == 'D':
        return 13
    elif letter == 'e' or letter == 'E':
        return 14
    elif letter == 'f' or letter == 'F':
        return 15
    else:
        return letter


def check_number_hex(num):
    for letter in num:
        if not letter.isdigit() and not letter_is_hex(letter):
            return False
    return True


def letter_is_hex(letter):
    if letter == 'a' or letter == 'A' or letter == 'b' or letter == 'B' or letter == 'c' or letter == 'C'\
     or letter == 'd' or letter == 'D' or letter == 'e' or letter == 'E' or letter == 'f' or letter == 'F':
        return True
    return False


def main():
    while True:
        val = input("press 1 to go from hex to dec \n"
                    "press 2 to to go from dec to hex\n"
                    "press 0 to exit:\n")
        if val == '1':
            number = input("enter number:\n")
            if check_number_hex(number):
                hex_to_dec(number)
            else:
                print('number not hexadecimal')
        if val == '2':
            number = input("enter number:\n")
            if number.isnumeric():
                dec_to_hex(int(number))
            else:
                print('number not decimal')
        if val == '0':
            break


main()
