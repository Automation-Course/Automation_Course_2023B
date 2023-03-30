![](Aspose.Words.cc2f4be2-d224-4384-99be-1834a1ff39e8.001.png)

`  `The system asks for a number and it's base.

`  `If the Base is 10, then it converts to base 16, else it converts base 16 to base 10.

`  `The system calls Dec2Hex function which takes integer parameter.

`  `This integer is repetitively divided by 16 until it reaches 0.

`  `For each iteration we get modulo(remainder) of the division and adds ahead to the result hex string.

If the modulo is less the 10 then we add as is to the result. But if it is more than 9 then we get the   Hex character of the modulo by subtracting 10 and adding to ascii of "A" .

`  `Hex to Decimal Conversion:

![](Aspose.Words.cc2f4be2-d224-4384-99be-1834a1ff39e8.002.png)

`  `The function Hex2Dec converts Hex numeral to Decimal.

`  `The function takes Hex string as a parameter and returns Integer.   The function goes through each character of the string.

For each iteration it multiplies the result with 16 and adds the corresponding decimal value to the   result.

If the Character lies between '0' and '9' then decimal value is obtain by subtracting the ascii of   character by '0' 

If the Character lies between 'A' and 'F' then decimal value is obtain by subtracting the ascii of   character by 'A' and adding 10.

Similarly If the Character lies between 'a' and 'f' then decimal value is obtain by subtracting the ascii   of character by 'a' and adding 10. 

`  `The function returns Exception if the character is not a hex character.
