// vi:nu:et:sts=4 ts=4 sw=4

//
//  file2C_Data.c
//
//  Created by bob on 9/13/22.
//

#include    <cmn_defs.h>
#include    <AStr.h>
#include    <Path.h>
#include    <u8Array.h>
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


const
char        *pProgram = "file2C_Data";
const
char        *pProgramPath = NULL;
int         fDebug = 0;             // -d or --debug or --no-debug
int         speed = 20;
int         srcFlag = 0;
FILE        *pOut = NULL;
const
char        *pOutputPathA = NULL;	

int         cOptions = 0;
const
char        **ppOptions = NULL;

int         lines = 1;



void        usage(
    char        *pMsg
)
{
    if (pMsg) {
        fprintf(stderr, "?%s - %s\n", pProgram, pMsg);
    }
    fprintf(
            stderr,
            "Usage: %s [-do] input-path; %s ? for help\n",
            pProgram,
            pProgram
    );
    fprintf( stderr, "\t-d,--[no-]debug  Set debug mode\n");
    fprintf( stderr, "\t-o,--output file-path Generate c file with name of file-path\n");
}



int         parseArgs(
    int         argc,
    const
    char        *argv[]
)
{
    int         wrkArgC = argc;
    const
    char        **ppWrkArgV = argv;
    
    // Validate some of the input.
    pProgramPath = argv[0];
    if( wrkArgC <= 1 ) {
        usage( "No arguments" );
        exit(99);
    }
    if( wrkArgC == 2 && ppWrkArgV[1][0] == '?' && ppWrkArgV[1][1] == 0) {
        usage("Generate C Data from a source file");
        exit(1);
    }
    
    // Process the switches.
    for (wrkArgC--,ppWrkArgV++; wrkArgC>0; wrkArgC--,ppWrkArgV++) {
        if (0 == strcmp(*ppWrkArgV, "--debug")) {
            ++fDebug;
        }
        else if (0 == strcmp(*ppWrkArgV, "--no-debug")) {
            --fDebug;
        }
        else if (0 == strcmp(*ppWrkArgV, "--output")) {
            if (NULL != *(ppWrkArgV+1)) {
                --wrkArgC;
                ++ppWrkArgV;
                if (NULL == pOutputPathA)
                    pOutputPathA = *ppWrkArgV;
            }
        }
        else if (0 == strcmp(*ppWrkArgV, "--")) {
            --wrkArgC;
            ++ppWrkArgV;
            break;
        }
        else if (**ppWrkArgV == '-') {
            const
            char        *pWrk = *ppWrkArgV + 1;
            while (*pWrk) {
                switch(tolower(*pWrk)) {
                    case 'd':
                        ++fDebug;
                        break;
                    case 'o':
                        if (NULL != *(ppWrkArgV+1)) {
                            --wrkArgC;
                            ++ppWrkArgV;
                            if (NULL == pOutputPathA)
                                pOutputPathA = *ppWrkArgV;
                        }
                        break;
                    default:
                        usage( "Unknown flag" );
                        exit(99);
                }
                ++pWrk;
            }
        }
        else
            break;
    }
    
    cOptions = wrkArgC;
    ppOptions = ppWrkArgV;
    
    return 0;
}




void             genCData (
    const
    char            *pPathInA
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    bool            fRc;
    PATH_DATA       *pPathIn  = OBJ_NIL;
    PATH_DATA       *pPathOut = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;

    if (NULL == pPathInA) {
        fprintf(stderr, "ERROR: file2C_Data() requires an input file path!\n\n\n");
        exit(16);
    }
    pPathIn = Path_NewA(pPathInA);
    if (OBJ_NIL == pPathIn) {
        fprintf(stderr, "ERROR: Could not create Output Path object!\n\n\n");
        exit(16);
    }
    Path_Clean(pPathIn, OBJ_NIL, NULL);

    if (NULL == pOutputPathA) {
        pOut = stdout;
    } else {
        pPathOut = Path_NewA(pOutputPathA);
        if (OBJ_NIL == pPathOut) {
            fprintf(stderr, "ERROR: Could not create Output Path object!\n\n\n");
            exit(16);
        }
        Path_Clean(pPathOut, OBJ_NIL, NULL);
        pOut = fopen(Path_getData(pPathOut), "w");
        if (NULL == pOut) {
            fprintf(stderr, "ERROR: Could not create Output file!\n\n\n");
            exit(16);
        }
    }

    pArray = u8Array_NewFromFile(pPathIn);
    if (pArray) {
        int             i;
        fprintf(pOut, "// vi:nu:et:sts=4 ts=4 sw=4\n\n");
        fprintf(pOut, "const\nuint32_t\t\tcData = %d;\n\n", u8Array_getSize(pArray));
        fprintf(pOut, "const\nuint8_t\t\tdata[%d] = {\n", u8Array_getSize(pArray));

        fprintf(pOut, " /*%08X*/\t", 0);
        for (i=0; i<u8Array_getSize(pArray); i++) {
            fprintf(pOut, "0x%02X, ", u8Array_Get(pArray, i+1));
            if ((i > 0) && (((i+1) % 16) == 0)) {
                fprintf(pOut, "\n /*%08X*/\t", i+1);
            }
        }
        fprintf(pOut, "\n};\n\n\n");

        obj_Release(pArray);
        pArray = OBJ_NIL;
        fclose(pOut);
    } else {
        fprintf(stderr, "ERROR: Could not read input file!\n\n\n");
        fclose(pOut);
        exit(16);
    }

    obj_Release(pPathOut);
    pPathOut = OBJ_NIL;
    obj_Release(pPathIn);
    pPathIn  = OBJ_NIL;
}



int         main(
    int         argc,
    const
    char        *argv[]
)
{
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             i;
    ERESULT         eRc;
    
    parseArgs(argc, argv);
    
    if (cOptions > 0) {
        genCData(ppOptions[0]);
    }
    else {
        usage("ERROR - Missing input text!");
        exit(99);
    }
        
    return 0;
}
