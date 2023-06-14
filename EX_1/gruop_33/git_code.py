a=[6,12,5,2]
def calculator(a,base): # base of the origin
    numbers =[0,1,2,3,4,5,6,7,8,9]
    if a is None:
        return
    if base == 16:
        index = 0
        for item in a:

                if item == 'A':
                    a[index] = 10

                elif item == 'B':
                    a[index] = 11

                elif item == 'C':
                    a[index] = 12

                elif item == 'D':
                    a[index] = 13

                elif item == 'E':
                    a[index] = 14

                elif item == 'F':
                    a[index] = 15

                else:
                    if item  not in numbers:
                        print("one of the items is incorrect!")
                        return
                index += 1
        i = 0
        ten_base = 0
        for num in reversed(a):
            ten_base += num * (16 ** i)
            i += 1
        return ten_base
    elif base == 10:

        ans = []
        i = 0
        num = 0

        for item in reversed(a):  # convert from array to int
            if item not in numbers:
                print("one of the items is incorrect!")
                return
            num += item * (10 ** i)
            i += 1
            z = 1
        while z >= 1:
            z = num / 16
            num = int(z)
            rest = z - num
            ans.append(int(rest * 16))
        ans.reverse()

        index = 0
        for item in ans:
            if item <0:
                print("one of the items is incorrect!")
            if item>9:
                if item == 10:
                    ans[index] = 'A'

                elif item == 11:
                    ans[index] = 'B'

                elif item == 12:
                    ans[index] = 'C'

                elif item == 13:
                    ans[index] = 'D'

                elif item == 14:
                    ans[index] = 'E'

                elif item == 15:
                    ans[index] = 'F'

                else:
                    print("one of the items is incorrect!"
                index += 1
        return ans
    else:
        print("the origin base is incorrect!")
        return

c = calculator(a,10)
print(c)