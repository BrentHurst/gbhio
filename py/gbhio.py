#!/usr/bin/env python3


# readInExcelCSV(filein)
# writeOutExcelCSV(fileout,csv)
# getCellIndexWithColHeader(header,val)



replacestrcomma = "€hello!χαιρεηηηδεξ€€€"



def strLineToList(line):
    line = line.strip()
    realCommaIndexList = []
    replaceCommaIndexList = []
    seenQuote = False

    for i,c in enumerate(line):
        if c == '"':
            seenQuote = not seenQuote
        elif c == ',':
            if not seenQuote:
                realCommaIndexList.append(i)
            else:
                replaceCommaIndexList.append(i)

    for i in reversed(replaceCommaIndexList):
        line = line[:i] + replacestrcomma + line[i+1:]

    l = line.split(',')

    for i,word in enumerate(l):
        if replacestrcomma in l[i]:
            l[i] = l[i].replace(replacestrcomma,',')
        if '"' in l[i]:
            if l[i][0] is not '"' or l[i][-1] is not '"':
                print(l[i] + ' doesn\'t start and end with a " somehow?')
                exit(1)
            else:
                l[i] = l[i][1:-1]

            l[i] = l[i].replace('""','"')

    return l



def readInExcelCSV(filein):
    csv = []
    with open(filein) as fin:
        lines = fin.readlines()
    for line in lines:
        csv.append(strLineToList(line))
    return csv


def getCellIndexWithColHeader(header,val):
    return header.index(val)


def listLineToStr(line):
    for i,cell in enumerate(line):
        if '"' in line[i] or ',' in line[i]:
            line[i] = '"' + line[i].replace('"','""') + '"'
    return ','.join(line)


def writeOutExcelCSV(fileout,csv):
    with open(fileout, 'w') as fout:
        for line in csv:
            fout.write(listLineToStr(line))
            fout.write('\n')


filein = 'students.csv'
csv = readInExcelCSV(filein)
