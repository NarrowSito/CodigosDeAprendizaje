#calculadora de subneteo

print("Bienvenid@ a la calculadora IP")

#variables
IPDeUsuarioD=str(input("Dirección IP: "))
claseDeIP=str(input("Clase de IP: "))
numSubredes=int(input("Número de Subredes que necesita: "))
numHost=int(input("Número de host que necesita: "))
rangoIP=0
potenciaM=0
potenciaN=0
print(IPDeUsuarioD)
IPDeUsuarioD=IPDeUsuarioD.split(".")
octeto1=int(IPDeUsuarioD[0])
octeto2=int(IPDeUsuarioD[1])
octeto3=int(IPDeUsuarioD[2])
octeto4=int(IPDeUsuarioD[3])
IPDeUsuarioB=[]


bits=8
#traductor a binario
print("Calculando :3")


IPDeUsuarioB.append(bin(octeto1))
IPDeUsuarioB.append(bin(octeto2))
IPDeUsuarioB.append(bin(octeto3))
IPDeUsuarioB.append(bin(octeto4))


# #operaciones


while numSubredes >=(2**potenciaN -2):
    potenciaN= potenciaN + 1

# while numSubredes >=(2**potenciaM -2):
    # potenciaM= potenciaM + 1

octetoB1=IPDeUsuarioB[0]
octetoB2=IPDeUsuarioB[1]
octetoB3=IPDeUsuarioB[2]
octetoB4=IPDeUsuarioB[3]

print("el rango es igual a: " + str(potenciaN))
print("La clase de la IP es: " + claseDeIP)

octetoB1=str(octetoB1.replace("b",""))
octetoB2=str(octetoB2.replace("b",""))
octetoB3=str(octetoB3.replace("b",""))
octetoB4=str(octetoB4.replace("b",""))

IPClassC="c"
IPClassB="b"
IPClassA="a"

if (IPClassA==claseDeIP):
    for i in range(potenciaN):
        octetoB2=octetoB2+"1"
        if(len(octetoB2)) > 10:
            octetoB2=str("0011111111")
            octetoB3=octetoB3+"1"
        if(len(octetoB3))>10:
            octetoB3=str("0011111111")
            octetoB4=octetoB4+"1"
    while(len(octetoB3)<10):
        octetoB3=octetoB3+"0"
    while(len(octetoB4)<10):
        octetoB4=octetoB4+"0"

if(IPClassB==claseDeIP):
    for e in range(potenciaN):
        octetoB3=octetoB3+"1"
        if(len(octetoB3))>10:
            octetoB3=str("0011111111")            
            octetoB4=octetoB4+"1"
    while(len(octetoB4)<10):
        octetoB4=octetoB4+"0"

if (IPClassC==claseDeIP):
    for i in range(potenciaN):
        octetoB4=octetoB4+"1"
        if(len(octetoB4))==10:
            octetoB4=str("0011111111")
    while(len(octetoB4)<10):
            octetoB4=octetoB4+"0"

IPDeUsuarioB[0]=(octetoB1.replace("b",""))
IPDeUsuarioB[1]=(octetoB2.replace("b",""))
IPDeUsuarioB[2]=(octetoB3.replace("b",""))
IPDeUsuarioB[3]=(octetoB4.replace("b",""))


octeto1=(int(str(IPDeUsuarioB[0]),2))
octeto2=(int(str(IPDeUsuarioB[1]),2))
octeto3=(int(str(IPDeUsuarioB[2]),2))
octeto4=(int(str(IPDeUsuarioB[3]),2))

mascaraAdp=(str(octeto1)+"."+str(octeto2)+"."+str(octeto3)+"."+str(octeto4))
if octeto4>=256:
    print(str(mascaraAdp))
    octeto4=255
    print("Y los Host papi???\nlas saco del gorro vea??\nes para otra clase mi rey\n")

print("su mascara adaptada es: "+mascaraAdp)
