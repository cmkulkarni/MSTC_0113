#include <Windows.h>

#include "StringVector.h"

PSTRINGVECTOR CreateStringVector(void){
    PSTRINGVECTOR pStrVec = NULL;

    pStrVec = (PSTRINGVECTOR)Xcalloc(1, sizeof(STRINGVECTOR));
    return(pStrVec);
}

int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString){
    pStrVec->iVectorSize += 1;
    pStrVec->ppString = (CHAR**)realloc(pStrVec->ppString, pStrVec->iVectorSize*sizeof(PCHAR));
    pStrVec->ppString[pStrVec->iVectorSize-1] = pNewString;
    return(SUCCESS);
}

int DestroyStringVector(PSTRINGVECTOR pStrVec){
    int iCnt;
    for(iCnt = 0; iCnt < pStrVec->iVectorSize; iCnt++){
        free(pStrVec->ppString[iCnt]);
    }
    free(pStrVec->ppString);
    free(pStrVec);
    return(SUCCESS);
}

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement){
    LPVOID pNewObject = NULL;

    pNewObject = (LPVOID*)calloc(cbSize, cbSizePerElement);
    FAIL_EXIT_IF(pNewObject == NULL, "Out of virtual mempry", "calloc");

    return(pNewObject);
}