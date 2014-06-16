#ifndef ACCESS_FLAG
#define ACCESS_FLAG

#ifndef cplusplus

#include <stdbool.h>

#endif

#include "definition.hpp"

bool isPublic(u2);
bool isPrivate(u2);
bool isProtected(u2);
bool isStatic(u2);
bool isFinal(u2);
bool isSuper(u2);
bool isBridge(u2);
bool isVoratile(u2);
bool isVarargs(u2);
bool isNative(u2);
bool isInterface(u2);
bool isAbstract(u2);
bool isSrict(u2);
bool isSynthetic(u2);
bool isEnum(u2);

#endif
