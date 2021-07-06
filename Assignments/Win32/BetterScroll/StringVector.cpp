#include <Windows.h>

#include "StringVector.h"


P_VECTOR_OF_STRINGS CreateVectorOfStrings(void)
{
    P_VECTOR_OF_STRINGS pStringOfVectors = NULL; 
    pStringOfVectors = (P_VECTOR_OF_STRINGS)malloc(sizeof(VECTOR_OF_STRINGS)); 
    FAIL_EXIT_IF(pStringOfVectors == NULL, "malloc", "out of virtual address space"); 
    pStringOfVectors->pArrayOfStrings = NULL; 
    pStringOfVectors->uNumberOfLines = 0; 
    return (pStringOfVectors); 
}

ATOM PushBackInVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings, CHAR* szString)
{
    pVectorOfStrings->uNumberOfLines += 1; 
    pVectorOfStrings->pArrayOfStrings = (CHAR**)realloc(pVectorOfStrings->pArrayOfStrings, 
                                                        pVectorOfStrings->uNumberOfLines * sizeof(CHAR*)); 
    FAIL_EXIT_IF(pVectorOfStrings->pArrayOfStrings == NULL, "realloc", "out of virtual address space"); 
    pVectorOfStrings->pArrayOfStrings[pVectorOfStrings->uNumberOfLines - 1] = szString; 
    return (SUCCESS); 
}

ATOM DestroyVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings)
{
    UINT uCnt; 
    for(uCnt = 0; uCnt != pVectorOfStrings->uNumberOfLines; uCnt++)
        free(pVectorOfStrings->pArrayOfStrings[uCnt]); 
    free(pVectorOfStrings->pArrayOfStrings); 
    free(pVectorOfStrings); 
    pVectorOfStrings = NULL; 
    return (SUCCESS); 
}
