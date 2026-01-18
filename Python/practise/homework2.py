def main():
    i = 0
    while i < 5:
        j = 5
        while j > 0:
            if j < i+1:
                j -= 1
                continue
            else:
                print(j,end="")
                j -= 1

        print()
        i += 1
main()