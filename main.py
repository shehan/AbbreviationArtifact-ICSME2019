import pandas as pd



# inputFiles = ['ICSME Artifact_ Abbreviations and Expansions - Enscript.csv',
#             'ICSME Artifact_ Abbreviations and Expansions - KDevelop.csv',
#             'ICSME Artifact_ Abbreviations and Expansions - Open Office.csv',
#             'ICSME Artifact_ Abbreviations and Expansions - Telegram.csv',
#             'ICSME Artifact_ Abbreviations and Expansions - Wycheproof.csv'
#             ]

inputFiles = ['out_enscript.csv','out_KDevelop.csv','out_OpenOffice.csv','out_Telegram.csv','out_Wycheproof.csv']

dfInput = pd.DataFrame(columns=['Abbreviation', 'Expansion'])
print('reading input...', end='', flush=True)
for inputFile in inputFiles:
    print('reading '+inputFile+'...', end='', flush=True)    
    inputData = pd.read_csv(inputFile,delimiter=':')
    dfInput = dfInput.append(inputData)
    print(len(inputData))
    print('done')
print('total rows: '+str(len(dfInput)))
print('sorting...', end='', flush=True)
dfInput.sort_values(by=["Abbreviation"], inplace=True) 
print('done')
print('removing duplicates...', end='', flush=True)
dfInput.drop_duplicates(inplace=True) 
print('done')
print('total rows: '+str(len(dfInput)))
dfInput.to_csv(r'output_onsolidated.csv')