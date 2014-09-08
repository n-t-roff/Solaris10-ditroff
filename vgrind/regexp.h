#ifndef __REGEXP_H__
#define __REGEXP_H__
int STRNCMP(register char *s1, register char *s2, register int len);
char *expmatch (char *s, char *re, char *mstring);
char *convexp(char *re);
#endif
