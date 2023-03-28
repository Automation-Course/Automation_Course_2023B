
 #A function that converts a decimal number to a hexadecimal number.
 #paramter dec_num: An integer representing the decimal number.
 #return: A string representing the hexadecimal number.
def dec_to_hex(dec_num):
    hex_list = []
    # Convert decimal to hexadecimal by dividing by 16 and adding the registers to a list
    while dec_num > 0:
        register = dec_num % 16
        if register < 10:
            hex_list.append(str(register))
        else:
            #The chr() is  used to turn an ASCII value into a character. chr() in python converts integers to char data types.
            #The ord() function returns the number representing the unicode code of a specified character.
            hex_list.append(chr(ord('A') + register - 10))  
        dec_num //= 16
    # Reverse the list of registers and convert it to a string
    hex_list.reverse()
    return ''.join(hex_list)



#A function that converts a hexadecimal number to a decimal number.
#paramter hex_num: A string representing the hexadecimal number.
# return: An integer representing the decimal number.

def hex_to_dec(hex_num):
    dec_num = 0
    # Convert hexadecimal to decimal by multiplying each digit by the appropriate power of 16
    for i in range(len(hex_num)):
        char = hex_num[i]
        if '0' <= char <= '9':
            dec_num += int(char) * (16 ** (len(hex_num) - 1 - i))
        elif 'A' <= char <= 'F':
            dec_num += (ord(char) - ord('A') + 10) * (16 ** (len(hex_num) - 1 - i))
    return dec_num


#
def main():
    print("Wellcome to the Hexadecimal-Decimal Calculator")
    while True:
        
        # Display menu options to the user
        print("Enter 1 to convert decimal to hexadecimal")
        print("Enter 2 to convert hexadecimal to decimal")
        print("Enter 3 to exit")
        
        # Get user input and validate it
        choice = input("Enter your choice: ")
        print("")
        while choice not in ['1', '2', '3']:
            print("Invalid choice. Please enter 1, 2, or 3.")
            choice = input("Enter your choice: ")
        choice = int(choice)
        
        # Perform the selected conversion or exit the program
        if choice == 1:
            
            # Get a decimal number from the user and validate it
            dec_num = input("Enter decimal number: ")
            
            #The isdigit() method returns True if all the characters are digits, otherwise False
            while not dec_num.isdigit(): 
                print("")
                print("Invalid input. Please enter a decimal number.")
                print("")
                dec_num = input("Enter decimal number: ")
            dec_num = int(dec_num)
            
            # Convert the decimal number to hexadecimal and display the result
            print("")
            print(f"The Hexadecimal: {dec_num} = {dec_to_hex(dec_num)}")
        elif choice == 2:
            
            # Get a hexadecimal number from the user and validate it
            hex_num = input("Enter hexadecimal number: ").upper()
            while not all(char in '0123456789ABCDEF' for char in hex_num):
                print("")
                print("Invalid input. Please enter a hexadecimal number.")
                print("")
                hex_num = input("Enter hexadecimal number: ").upper()
            # Convert the hexadecimal number to decimal and display the result
            print("")
            print(f"The Decimal: {hex_num} = {hex_to_dec(hex_num)}")
        elif choice == 3:
            # Exit the program
            print("Goodbye")
            break
        
        # Wait for the user to press Enter before continuing
        input("Press Enter to continue...")
        print()

if __name__ == '__main__':
    main()
