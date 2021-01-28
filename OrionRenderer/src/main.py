from pathlib import Path
import glob
import os

filePaths = []
path = "./"

for root, dirs, files in os.walk(path):
	for file in files:
		if(file.endswith(".cpp") or file.endswith(".h")):
			filePaths.append(os.path.join(root,file))

count = 0

for filePath in filePaths:
	print(filePath)
	for line in open(filePath): count += 1

print("Total line count: " + str(count))