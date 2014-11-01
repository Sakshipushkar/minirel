#include<string.h>

#include "../include/defs.h"
#include "../include/error.h"

/*
 * Contains helper functions used throughout the project
 *
 *  Created on: 29-Oct-2014
 *      Author: nithin
 */

//FIXME Move to another folder?
void readStringFromByteArray(char * string, const char *byteArray, const int offset, const int size) {
    if (byteArray == NULL || string == NULL) {
        ErrorMsgs(NULL_POINTER_EXCEPTION);
        return;
    }
    strncpy(string, (byteArray + offset), size);
}

int readIntFromByteArray(const char *byteArray, const int offset) {
    if (byteArray == NULL) {
        ErrorMsgs(NULL_POINTER_EXCEPTION);
        return 0;
    } else {
        const char *offsetedByteArray = byteArray + offset;

        return ((offsetedByteArray[0]<<24) & 0xFF000000) | ((offsetedByteArray[1]<<16) & 0x00FF0000) | 
        ((offsetedByteArray[2]<<8) & 0x0000FF00) | (offsetedByteArray[3] & 0x000000FF);
    }
}

//FIXME Float conversion
float readFloatFromByteArray(const char* byteArray, const int offset) {

    return 1.0;

}

void convertIntToByteArray(int value, char *byteArray){
    byteArray[0] = (value>>24) & 0xFF;
    byteArray[1] = (value>>16) & 0xFF;
    byteArray[2] = (value>>8) & 0xFF;
    byteArray[3] = value & 0xFF;
}
/*************************************************************
 COMPARISONS
 *************************************************************/

bool compareNum(float val1, float val2, int compOp) {
    switch (compOp) {
            case EQ:
                return val1 == val2 ? TRUE : FALSE;
            case NEQ:
                return val1 != val2 ? TRUE : FALSE;
            case GEQ:
                return val1 >= val2 ? TRUE : FALSE;
            case LEQ:
                return val1 <= val2 ? TRUE : FALSE;
            case GT:
                return val1 > val2 ? TRUE : FALSE;
            case LT:
                return val1 < val2 ? TRUE : FALSE;
            default:
                ErrorMsgs(INVALID_COMP_OP);
                break;
        }
        return FALSE;
}

//TODO Ask about supported string comparison
bool compareStrings(char *s1, char *s2, int compOp) {
    switch (compOp) {
                case EQ:
                    return strcmp(s1,s2)==0 ? TRUE : FALSE;
                case NEQ:
                    return strcmp(s1,s2) ? TRUE : FALSE;
                case GEQ:
                    return (strcmp(s1,s2)>=0) ? TRUE : FALSE;
                case LEQ:
                    return (strcmp(s1,s2)<=0) ? TRUE : FALSE;
                case GT:
                    return (strcmp(s1,s2)>0) ? TRUE : FALSE;
                case LT:
                    return (strcmp(s1,s2)<0) ? TRUE : FALSE;
                default:
                    ErrorMsgs(INVALID_COMP_OP);
                    break;
            }
            return FALSE;
}
