# fn to check Luhn's algorithm
def check(num):
    sum = int(0)
    for i in range(len(num)):
        r = int(len(num) - i - 1)
        x = int(num[r])

        if not r % 2 == 0:
            if x * 2 <= 9:
                sum += (x * 2)
            else:
                sum += ((x * 2) % 10)
                sum += int(((x * 2) / 10))
        else:
            sum += x

    if sum % 10 == 0:
        return True
    else:
        return False


num = input("Number: ")

if not check(num):
    print("INVALID")
else:
    if num[0:2] == "34" or num[0:2] == "37":
        print("AMEX")
    elif num[0:2] == "51" or num[0:2] == "52" or num[0:2] == "53" or num[0:2] == "54" or num[0:2] == "55":
        print("MASTERCARD")
    elif num[0:1] == "4":
        print("VISA")
    else:
        print("INVALID")
