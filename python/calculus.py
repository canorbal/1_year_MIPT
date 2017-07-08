import math

def get_expression():
    string = raw_input()
    
    if string=="":
        print('Wrong input!')
    
    return string

def is_number(str):
    
    if str == "":
        return True
    try:
        float(str) 
        return True
    
    except ValueError:
        return False
            
def delete_space(str):
    
    temp_string=[]
    i=0
    
    while i<len(str):
        if str[i]!=" ":
            temp_string.append(str[i])
        i=i+1
    
    return temp_string

def analys(string,count):
    
    number = ""
    i=count
    
    while i<len(string) and (string[i]=='.' or string[i].isdigit()):
         number=number+string[i]
         i=i+1
    
    return number


input_string=get_expression()
input_string=delete_space(input_string)

i=0

output_string =[]
stack = []
priority={'Ln':'5','LN':'5','ln':'5','cos':'5','sin':'5','^':'4','*':'3', '/':'3', '+':'2', '-':'2', '(':'1', ')':'1'}

while i<len(input_string):

    if input_string[i].isdigit() or input_string[i]=='e' or input_string[i]=='p':
        
        if input_string[i]=='e':
            output_string.append(math.e)
            i=i+1
            continue
        
        if input_string[i]=='p':
            output_string.append(math.pi)
            i=i+2
            continue

        output_string.append(analys(input_string,i)) 
        i=i+len(analys(input_string,i))
        continue

    if input_string[i]=="(":
        stack.append(input_string[i])
        i+=1
        continue

    if input_string[i]==")":
        
        while stack[len(stack)-1]!="(":
            output_string.append(stack[len(stack)-1])
            stack.pop(len(stack)-1)
        
        stack.pop(len(stack)-1)
        i+=1
        continue


    operation = input_string[i]
    
    if operation == "s":
        operation = "sin"
    if operation =="c":
        operation = "cos"
    if operation =="l" or operation == "L":
        operation ="ln"
    
    
    if len(stack)==0 or priority[stack[len(stack)-1]]<priority[operation]:
        stack.append(operation)
        i=i+len(operation)
        continue

    while len(stack)>=1 and  priority[stack[len(stack)-1]]>=priority[operation]:
        output_string.append(stack[len(stack)-1])
        stack.pop(len(stack)-1)
    
    stack.append(operation)
    i=i+len(operation)
    continue


while len(stack)>0:
    output_string.append(stack[len(stack)-1])
    stack.pop(len(stack)-1)


stack_of_numbers=[]
i=0
while i<len(output_string):
    
    if is_number(output_string[i]):
        stack_of_numbers.append(output_string[i])
        i=i+1
        continue
    
    if output_string[i]=="+":
        x=stack_of_numbers.pop()
        y=stack_of_numbers.pop()
        stack_of_numbers.append(float(x)+float(y))
        i=i+1
        continue
    
    if output_string[i]=="-":
        x=stack_of_numbers.pop()
        y=stack_of_numbers.pop()
        stack_of_numbers.append(float(y)-float(x))
        i=i+1
        continue
    
    if output_string[i]=="*":
        x=stack_of_numbers.pop()
        y=stack_of_numbers.pop()
        stack_of_numbers.append(float(x)*float(y))
        i=i+1
        continue
    
    if output_string[i]=="/":
        x=stack_of_numbers.pop()
        y=stack_of_numbers.pop()
        stack_of_numbers.append(float(y)/float(x))
        i=i+1
        continue
    
    if output_string[i]=="^":
        x=stack_of_numbers.pop()
        y=stack_of_numbers.pop()
        stack_of_numbers.append(float(y)**float(x))
        i=i+1
        continue
    
    if output_string[i]=="sin":
        x=stack_of_numbers.pop()
        stack_of_numbers.append(math.sin(float(x)))
        i=i+1
        continue
    
    if output_string[i]=="cos":
        x=stack_of_numbers.pop()
        stack_of_numbers.append(math.cos(float(x)))
        i=i+1
        continue
    
    if output_string[i]=="ln" or output_string[i]=="LN" or output_string=="Ln":
        x=stack_of_numbers.pop()
        stack_of_numbers.append(math.log(float(x)))
        i=i+1
        continue

print stack_of_numbers[0]
