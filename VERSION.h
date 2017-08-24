#ifndef __VERSION_H__
#define __VERSION_H__


#define FW_VERSION_LEN           4

/* Version definition*/
#define BUILD_MONTH              6
#define BUILD_DAY                20
#define BUILD_VERSION            0
#define BUILD_SUBVERSION         0

#define CODE_VERSION            (BUILD_VERSION << 8)|BUILD_SUBVERSION

#endif  /* __VERSION_H__ */