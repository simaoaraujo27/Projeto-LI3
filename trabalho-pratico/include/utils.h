#ifndef _USERS_H_
#define _USERS_H_

void remove_quotes(char *str);

//int primeiraOcorr(char *line, char carac);

//char *calculate_age(char *birth_date);

typedef struct ageRange AgeRange;
AgeRange createStruct (int minAge, int maxAge);

#endif