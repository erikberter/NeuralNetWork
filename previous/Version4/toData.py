import string
import random

letters = string.ascii_lowercase[:26]

def id_generator():
    return ''.join(random.choice(letters) for _ in range(random.randint(4,9)))

ff = open("data5ESFIRsmall.txt","w")

f = open("dictionaries/eng.txt","r")
lines = f.read().split()

#englis spanisj french ita randm

ff.write("260 3\n")
for pal in lines:
    if(len(pal)<10):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="1 0 0 0 0\n"
        ff.write(zz)
f.close()
f = open("dictionaries/spa.txt","r")
lines = []
lines = lines = f.read().split()
for pal in lines:
    if(len(pal)<10):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="0 1 0 0 0\n"
        ff.write(zz)
f.close()
f = open("dictionaries/fch.txt","r")
lines = []
lines = lines = f.read().split()
for pal in lines:
    if(len(pal)<10):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="0 0 1 0 0\n"
        ff.write(zz)
    f.close()
f = open("dictionaries/ita.txt","r")
lines = []
lines = lines = f.read().split()
for pal in lines:
    if(len(pal)<10):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="0 0 0 1 0 \n"
        ff.write(zz)
linesS = []
for i in range(0,2000):
    linesS.append(id_generator())
for pal in linesS:
    if(len(pal)<10):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="0 0 0 0 1\n"
        ff.write(zz)