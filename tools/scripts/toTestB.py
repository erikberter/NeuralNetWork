import string
import random

letters = string.ascii_lowercase[:26]

def id_generator():
    return ''.join(random.choice(letters) for _ in range(random.randint(4,9)))
#lenguage

f = open("wordsSbig.txt","r")
lines = f.read().split()
ff = open("testSRbig.txt","w")
fff = open("wordsSRbig.txt","w")
ff.write("260\n")
for pal in lines:
    if(len(pal)<10 and len(pal)>3):
        zz = ""
        for j in range(0,len(pal)):
            zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
        for j in range(0,10-len(pal)):
            zz+="".join(["0 " for i in range(0,26)])
        zz+="\n"
        ff.write(zz)
        fff.write(pal+" 1\n")
"""
#random
ff = open("testRbig.txt","w")
fff = open("wordsRbig.txt","w")
ff.write("260\n")
for i in range(0,70000):
    pal = id_generator()
    zz = ""
    for j in range(0,len(pal)):
        zz+="".join(["0 " if pal[j]!=letters[i] else "1 "for i in range(0,26)])
    for j in range(0,10-len(pal)):
        zz+="".join(["0 " for i in range(0,26)])
    zz+="\n"
    ff.write(zz)
    fff.write(pal+" 1\n")
"""