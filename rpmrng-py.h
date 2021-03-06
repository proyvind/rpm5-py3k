#ifndef H_RPMRNG_PY
#define H_RPMRNG_PY

#include "rpmio_internal.h"

/** \ingroup py_c
 * \file python/rpmrng-py.h
 */

/** \name Type: _rpm.rng */
/*@{*/

typedef struct rngObject_s {
    PyObject_HEAD
    PyObject *md_dict;		/*!< to look like PyModuleObject */
    randomGeneratorContext rngc;
    mpbarrett b;
} rngObject;

extern PyTypeObject rng_Type;
#define is_rng(o)	((o)->ob_type == &rng_Type)

/*@}*/

#endif
