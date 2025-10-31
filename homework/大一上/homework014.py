def mv(locat,x:float,y:float):
    return [(locat[0]+float(x)),(locat[1]+float(y))]
def rotate(angle_now:float,angle_change:float):
    angle_now += angle_change
    return angle_now
def set_pattern(pattern:str):
    return pattern
def set_color(color:str):
    return color
def stamp():
    return

def main():
    locat = [0.0,0.0]
    angle = 0.0
    pattern = "no_pattern"
    color = "black"
    instruction = []
    call = False

    for _ in range(6):
        instruction.append(list(map(str, input().split())))
    #print(instruction)

    for i in range(6):
        match instruction[i][0]:
            case "reset":
                locat = [0,0]
                angle = 0.0
                pattern = "no_pattern"
                color = "black"
            case "mv":
                locat = mv(locat,instruction[i][1],instruction[i][2])
            case "rotate":
                if -360 <= float(instruction[i][1]) <= 360:
                    angle = rotate(angle,float(instruction[i][1]))
            case "set_pattern":
                pattern = set_pattern(instruction[i][1])
            case "set_color":
                color = set_color(instruction[i][1])
            case "stamp":
                call = True
                if not 0 <= angle < 360:
                    angle = angle % 360
                print(f'Stamping... [position: ({locat[0]:.2f}, {locat[1]:.2f}), rotation: {angle:.2f} degrees, pattern: {pattern}, color: {color}]')

    if not call:
        print("Stamping canceled")
    #print(color)
main()