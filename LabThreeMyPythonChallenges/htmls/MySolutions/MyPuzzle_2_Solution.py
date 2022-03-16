# This is solution of my second puzzle:

"""
By the image we can see there are lots of grey grids, whose R-G-B values are equal each other.
So we can use the PILLOW library to process it.
"""
import os
import requests
"""
Attention please, I just use the requests to save a short-term image from url 
and the os to delete it after finish this code~
"""
imageFile = "D://GreyBuffer.png"
url = "https://guanghanwu.github.io/CCI_CodingTwo_4Labs/LabThreeMyPythonChallenges/htmls/Grey.png"
r = requests.get(url)
r.status_code
with open(imageFile, "wb") as file:
    file.write(r.content)

from PIL import Image

image = Image.open(imageFile)
width, height = image.size  # get size of the image
pic = image.load()
lastValue=0

# look through it and transform values
# for x in range(width):
#    for y in range(height):
#        # print(pic[x, y])
#         r, g, b = pic[x, y]
#         if r != g or g != b or b != r:
#             continue
#         if lastValue != r:
#             print(chr(r), end='')
#         saveValue=r
""" if just this code, there will be a lot of chaos
    further, A's ascii 65 and z's ascii 122 so must be in 65~122
    and can see there are many letter come up 9 times
    so reduce them
"""
string = ""
for x in range(width):
   for y in range(height):
        r, g, b = pic[x, y]
        if r != g or g != b or b != r:
            continue
        if lastValue != r and (65 <= r <= 122):
            string += chr(r)
        saveValue=r
for i in range(len(string)):
    if i+8 >= len(string):
        break
    if string[i] == string[i+4] == string[i+8]:
        i = i+8 #skip the middle 8 repeated items
        print(string[i], end='')
image.close()#close the image file, then I can remove it in my computer
os.remove(imageFile)
