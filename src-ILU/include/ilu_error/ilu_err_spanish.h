//-----------------------------------------------------------------------------
//
// ImageLib Utility Sources
// Copyright (C) 2000-2008 by Denton Woods
// Last modified: 10/12/2008
//
// Filename: src-ILU/include/ilu_err_spanish.h
//
// Description: Error functions in Spanish, translated by Carlos Aragon�s.
//
//-----------------------------------------------------------------------------


#ifndef ILU_ERR_SPANISH_H
#define ILU_ERR_SPANISH_H

#include "ilu_internal.h"

ILconst_string iluErrorStringsSpanish[IL_FILE_READ_ERROR - IL_INVALID_ENUM + 1] = {
	L"enumerador incorrecto",
    L"no queda memoria disponible",
	L"formato no soportado todav�a",
	L"error interno",
	L"valor incorrecto",
    L"operaci�n ilegal",
	L"valor de fichero ilegal",
	L"cabecera incorrecta",
	L"par�metro incorrecto",
	L"no se puede abrir el fichero",
	L"extensi�n desconocida",
	L"el fichero ya existe",
	L"formato de salida equivalente",
	L"desbordamiento superior de pila",
    L"desbordamiento inferior de pila",
	L"conversi�n incorrecta",
	L"n�mero de dimensiones incorrecto",
	L"error de lectura en el fichero"
};

ILconst_string iluLibErrorStringsSpanish[IL_LIB_MNG_ERROR - IL_LIB_GIF_ERROR + 1] = {
	L"error en la librer�a gif",  // the correct translation will be 'error en la biblioteca gif' but nobody in spain uses the word 'biblioteca' for translate the word 'library'. Almost all spanish programmers translates incorrectly library to 'librer�a'.
	L"error en la librer�a jpeg",
	L"error en la librer�a png",
	L"error en la librer�a tiff",
	L"error en la librer�a mng"
};

ILconst_string iluMiscErrorSpanish[2] = {
	L"no error",
	L"unknown error"
};

#endif//ILU_ERR_SPANISH_H