#pragma once

#include <Windows.h>

#define SUCCESS 1

void ReleaseAll(void);

#ifndef FAIL_EXIT_IF
#define FAIL_EXIT_IF(COND, MSG, CAPTION)    do\
                                            {\
                                                if((COND) == TRUE)\
                                                {\
                                                    MessageBox(NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
                                                    ReleaseAll();\
                                                    ExitProcess(EXIT_FAILURE);\
                                                }\
                                            }while(0)
#endif 

typedef struct tagStringVector
{
    CHAR** ppString;
    int iVectorSize;
}STRINGVECTOR, *PSTRINGVECTOR, *NPSTRINGVECTOR, *LPSTRINGVECTOR;

PSTRINGVECTOR CreateStringVector(void);
int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString);
int DestroyStringVector(PSTRINGVECTOR pStrVec);

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement);

