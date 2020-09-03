from sys import argv, exit
import csv
import re

# check correct usage of arguments
if not len(argv) == 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open db and store in dict 
db = open(argv[1], "r")
db_dict = csv.DictReader(db)

# store names of STRs on top of CSV db
str_names = db_dict.fieldnames

# open seq to be identified
inptr = open(argv[2], "r")
identify = inptr.read()

# remove the extra next line char at end of file
identify = identify.strip('\n')

# close sequence file
inptr.close()

# list to store found STR lensgths in seq to be identified
found_str = []

# loop over STR and file their longest lengths in seq to be identified
for i in range(1, len(str_names)):
    str = str_names[i]
    
    # RE
    repeats = rf'({str})+'
    max = int(0)
    
    # find longest occurence
    for match in re.finditer(repeats, identify):
        if len(match.group()) > max:
            max = len(match.group())
            
    # add the longest occurence to list
    found_str.append(int(max/len(str)))

# check if match exist in DB
for row in db_dict:
    chk = int(0)
    
    # loop over each row to check if match exists
    for x in range(1, len(str_names)):
        if int(row[str_names[x]]) == int(found_str[x - 1]):
            chk += 1
    
    # if matched seq match exactly in DB then match found
    if chk == len(found_str):
        # print match name and close file and exit
        print(row['name'])
        db.close()
        exit(1)

#no match found and close file
print("No match")
db.close()