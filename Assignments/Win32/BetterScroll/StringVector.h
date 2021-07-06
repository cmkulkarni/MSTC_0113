#pragma once

#include <Windows.h>

#define SUCCESS 1
#define BUFFER_SIZE 128

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
    CHAR** pArrayOfStrings;
    UINT uNumberOfLines;
}VECTOR_OF_STRINGS, *P_VECTOR_OF_STRINGS, *NP_VECTOR_OF_STRINGS;

P_VECTOR_OF_STRINGS CreateVectorOfStrings(void);
ATOM PushBackInVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfString, CHAR* szString);
ATOM DestroyVectorOfStrings(P_VECTOR_OF_STRINGS pVectorOfStrings);

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement);

