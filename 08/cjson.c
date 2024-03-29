#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define RELEASE_LOADS
#define RELEASE_DUMPS

char* cleanRawJSONfromSpaces(char* rawJson, Py_ssize_t rawLen)
{
    char* str2 = (char*)malloc(rawLen*sizeof(char));
    int str2Len = 0;
    int isLiteralPart = 0;
    while (*rawJson != '\0')
    {       
        if ( (*rawJson == '\"' || *rawJson == '\'') && !isLiteralPart )
        { isLiteralPart = 1; }
        else if ( (*rawJson == '\"' || *rawJson == '\'') && isLiteralPart )
        { isLiteralPart = 0; }
        if ( isLiteralPart || (!isspace(*rawJson)) )
        { *str2 = *rawJson; str2Len++; str2++; }
        rawJson++;
    }
    str2 -= str2Len;

    char* result = (char*)realloc(str2, str2Len+1);
    result[str2Len] = '\0';

    return result;
}


Py_ssize_t countTokensInClearJSON(char* clearStrJSON, Py_ssize_t strLen)
{
    Py_ssize_t counter = 0;
    for (Py_ssize_t i=0; i < strLen; ++i)
    {
        if ( clearStrJSON[i] == ':' || clearStrJSON[i] == ',')
            counter++;
    }
    counter++;

    return counter;
}


int isString(char* token)
{
    Py_ssize_t tokenLen = strlen(token);
    if ( *token == '\'' || *token == '\"' ) {
        if (*(token + tokenLen - 1) == '\'' || *(token + tokenLen - 1)== '\"'  )
        {
            return 1;
        }
    }
    return 0;
}


int isNumeric(char* token)
{
    if ( *token == '-' ) token++;

    int firstNil = 1;
    while (*token != '\0')
    {
        if ( !isdigit(*token)  ) return 0;
        if ( firstNil && *token == '0' && strlen(token) > 1 ) return 0;
        firstNil = 0;

        token++;
    }

    return 1;
}


char* rawConcat(const char* str1, const char* str2)
{
    char* dist = (char*)malloc(strlen(str1) + strlen(str2) + 1); 
    strcpy(dist, str1);
    strcat(dist, str2);
    return dist;
}


const char* int2pchar(int num)
{
#ifndef RELEASE_DUMPS
    printf("int2pchar : %d\n", num);
#endif
    int isNegative = 0;
    if ( num < 0 ) { isNegative = 1; num *= -1; }
    int numLen = ceil(log10(num));
    if ( num % 10 == 0 || num ==1 ) numLen++;

    int symCount = numLen + 1;
    char* pcharnum = (char*)malloc(sizeof(char)*(symCount + isNegative));
    
    if ( isNegative ) { *pcharnum = '-'; pcharnum++; }
    
    for (int i=symCount-2; i>-1; i--)
    {
#ifndef RELEASE_DUMPS
        printf("digits in %d is %d\n", i, num % 10);
#endif
        pcharnum[i] = num % 10 + '0';
        num /= 10;
    }
    pcharnum[symCount-1] = '\0';
    if ( isNegative ) { pcharnum--; }
    
#ifndef RELEASE_DUMPS
    for (int i=0; i < symCount + isNegative; ++i)
    {
        printf("%d) %c\n", i, pcharnum[i]);
    }
#endif

    return pcharnum;
}


PyObject* cjson_loads(PyObject* self, PyObject* args)
{
    // parsing arguments from tuple (a1, a2, a3)
    // our case is '{"key1" : value1, "key2" : value2}' as e.g
    char* argString;
    Py_ssize_t argStringLen = 0;

    if(!PyArg_ParseTuple(args, "s#", &argString, &argStringLen))
    {
        printf("ERROR: Failed to parse arguments\n");
        return NULL;
    }
#ifndef RELEASE_LOADS
    printf("Initial string : %s\n", argString);
    printf("Initial string len : %ld\n", argStringLen);
#endif

    char* argStringClean = cleanRawJSONfromSpaces(argString, argStringLen);
    Py_ssize_t argStringLenClean = strlen(argStringClean);

#ifndef RELEASE_LOADS
    printf("Cleaned string : %s\n", argStringClean);
    printf("Cleaned string len : %ld\n", argStringLenClean);
#endif
    
    // lets remove curly brackets
    argStringClean[argStringLenClean-1] = '\0';
    argStringClean += 1;
    argStringLenClean -= 2; // cause brackets is gone

#ifndef RELEASE_LOADS
    printf ("Transformed string : %s\n", argStringClean);
    printf ("Transformed string len : %ld\n", argStringLenClean);
#endif

    // tokenizing
    Py_ssize_t tokensLen = countTokensInClearJSON(argStringClean, argStringLenClean);
    char** tokens = (char**)malloc( sizeof(char*) * tokensLen );
    char delimeters[] = ":,\0";

    char* token = strtok(argStringClean, delimeters);

    Py_ssize_t tokensIdx = 0;
    while (token)
    {
#ifndef RELEASE_LOADS
        printf("token from strtok is : %s\n", token);
#endif
        tokens[tokensIdx] = token;
        token = strtok(NULL, delimeters);
        tokensIdx++;
    }
    tokens[tokensIdx] = token;

    PyObject* dict = NULL;
    if (!(dict = PyDict_New())) {
        printf("ERROR: Failed to create Dict Object\n");
        return NULL;
    }

    // lets fill the dict by tokens
    int isKey = 1, isValue = 0;
    PyObject* key = NULL;
    PyObject* value = NULL;
    PyObject* pyTempValue = NULL;

    for (Py_ssize_t i=0; i < tokensLen; ++i)
    {
        if (i % 2 == 0) { isKey = 1; isValue = 0; }
        else { isKey = 0; isValue = 1; }
#ifndef RELEASE_LOADS
        printf("token on %ld pos is %s\n", i, tokens[i]);
#endif
        if ( isString(tokens[i]) )
        {
            tokens[i]++;
            *(tokens[i] + strlen(tokens[i]) - 1) = '\0';
            pyTempValue = Py_BuildValue("s", tokens[i]);
        }
        else if ( isNumeric(tokens[i]) )
        {
            pyTempValue = Py_BuildValue("i", atoi(tokens[i]));
        }
        else 
        {
            printf("ERROR: Failed non suported type in %ld kv pair\ntoken : %s\n", i - i % 2, tokens[i]);
            return NULL;
        }

        if (isKey)
        {
            key = pyTempValue;
        }
        else if (isValue)
        {
            value = pyTempValue;

            if (PyDict_SetItem(dict, key, value) < 0) {
                printf("ERROR: Failed to set item\n");
                return NULL;
            }
        }
    }


    return dict;
}


PyObject* cjson_dumps(PyObject* self, PyObject* args)
{
    PyObject* dict = NULL;
    PyObject* key = NULL;
    PyObject* value = NULL;
    Py_ssize_t pos = 0;

    if (!PyArg_ParseTuple(args, "O", &dict))
    {
        printf("ERROR: Failed to parse arguments of dictionary\n");
        return NULL;
    }
#ifndef RELEASE_DUMPS
    printf("First steps is passed\n");
#endif
    char* accum = "{";
    int firstIter = 1;
    while (PyDict_Next(dict, &pos, &key, &value))
    {
        const char* innerStrKey = PyUnicode_AsUTF8(key);
        if (firstIter)
        {
            innerStrKey = rawConcat("\"", innerStrKey);
            firstIter = 0;
        }
        else
        {
            innerStrKey = rawConcat(", \"", innerStrKey);
        }
        
        innerStrKey = rawConcat(innerStrKey, "\": ");
        accum = rawConcat(accum, innerStrKey);
#ifndef RELEASE_DUMPS
        printf("Accum with key : %s\n", accum);
#endif

        const char* innerStrValue = NULL;
#ifndef RELEASE_DUMPS
            printf("PyLong check await\n");
#endif
        if (PyLong_Check(value))
        {
#ifndef RELEASE_DUMPS
            printf("PyLong check is passed\n");
#endif
            int temp_value = PyLong_AsLong(value);
#ifndef RELEASE_DUMPS
            printf("PyLong_AsLong passed %d\n", temp_value);
#endif
            innerStrValue = int2pchar(temp_value);
#ifndef RELEASE_DUMPS
            printf("PyLong_AsLong passed %s\n", innerStrValue);
#endif
            accum = rawConcat(accum, innerStrValue);
        }
        else
        {
            innerStrValue = PyUnicode_AsUTF8(value);
            innerStrValue = rawConcat("\"", innerStrValue);
            innerStrValue = rawConcat(innerStrValue, "\"");
            accum = rawConcat(accum, innerStrValue);
        }
    }
    accum = rawConcat(accum, "}");

    return Py_BuildValue("s", accum);
}


static PyMethodDef methods[] = {
    { "loads", cjson_loads, METH_VARARGS, "Load dict from JSON string"},
    { "dumps", cjson_dumps, METH_VARARGS, "Dict to string"},
    { NULL, NULL, 0, NULL}
};


static struct PyModuleDef cjsonmodule = {
    PyModuleDef_HEAD_INIT, "cjson",
    NULL, -1, methods
};


PyMODINIT_FUNC PyInit_cjson(void)
{
    return PyModule_Create( &cjsonmodule);
};