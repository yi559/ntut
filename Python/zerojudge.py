while(True):
    try:
        data = input()
        token = data.split()
        stack = []
        output = []

    except EOFError:
        break