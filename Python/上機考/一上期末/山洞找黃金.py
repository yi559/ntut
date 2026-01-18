def dfs(bag, number, m, total_value, total_weight, visit):
    if number == '0' or number in visit:
        return total_value

    value, weight, next1, next2 = bag[number]
    weight = int(weight)
    value = int(value)

    if total_weight + weight > m:
        return total_value

    total_weight += weight
    total_value += value
    visit.add(number)

    v1 = dfs(bag, next1, m, total_value, total_weight, visit.copy())
    v2 = dfs(bag, next2, m, total_value, total_weight, visit.copy())

    return max(v1, v2)

def main(): 
    n,first = input().split() 
    m = int(input()) 
    bag = {} 
    for _ in range(int(n)): 
        number,value,weight,next1,next2 = input().split() 
        bag[number] = [value,weight,next1,next2] 
        print(dfs(bag,first,m,0,0,set()))
main()