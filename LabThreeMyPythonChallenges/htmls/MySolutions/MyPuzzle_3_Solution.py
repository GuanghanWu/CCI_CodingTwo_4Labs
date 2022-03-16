# This is solution of my third puzzle:

"""
this is a puzzle about Cryptography
"""
import requests
import re

url = "https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabThreeMyPythonChallenges/htmls/cats.html"
r = requests.get(url)
r.status_code
text = r.text
beginIndex = re.search('<!-- \[', text).span()[1]  # to get the begin index of the numbers
endIndex = re.search('] -->', text).span()[1] - len('] -->')  # to get the final index of the numbers
# print(ord('0'))
# print(ord('9'))
"""We can do the 4 divide first"""
myList = list()
str0 = ""
count = 0
c = beginIndex
# print(text[c])
te = text[c]
while c < endIndex:
    # print(ord(text[c]))
    while ord('0') <= ord(text[c]) <= ord('9'):
        str0 += text[c]
        c += 1
        if c >= endIndex:
            break
    if str0 != "":
        myList.append(int(int(str0) / 4))
    c += 1
    str0 = ""
"""Now we got the real ascii value, so let's see what they realy are"""
# print(myList)
myList2 = list()
for c in myList:
    myList2.append(chr(c))
    # print(chr(c),end="")
n = 0
"""
we can see many Mews and Silences, this can be connect to the 1 and 0, 
further more, they look like the MORSE CODE!!
so let's change it
"""

myMPd = list()  # myMorsePassword
str1 = ""
while n < len(myList2):
    while myList2[n] != ",":
        if myList2[n] == "M":
            str1 += "-"
        if myList2[n] == "S":
            str1 += "."
        n += 1
        if n >= len(myList2):
            break
    myMPd.append(str1)
    if n >= len(myList2):
        break
    if myList2[n] == ",":
        myMPd.append("/")
    str1 = ""
    n += 1
# print(myMPd)
dic = {
    ".-": "A", "-...": "B", "-.-.": "C", "-..": "D", ".": "E",
    "..-": "F", "--.": "G", "....": "H", "..": "I", ".---": "J",
    "-.-": "K", ".-..": "L", "--": "M", "-.": "N", "---": "O", ".--.": "P",
    "--.-": "Q", ".-.": "R", "...": "S", "-": "T", "..-": "U", "...-": "V",
    ".--": "W", "-.--": "X", "-.--": "Y", "--..": "Z",

}
for pw in myMPd:
    if pw == "":
        continue
    elif pw not in dic:
        print(".", end="")
    else:
        print(dic[pw], end="")

""" 
    now we know the "WINPAGE" is final answer!
"""
