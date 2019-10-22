#ifndef LAB11_1_DAILYQUOTATION_H
#define LAB11_1_DAILYQUOTATION_H

#define FALSE 0

typedef struct {
    int year, month, day;
} Date;                                                                                                                 // the date
typedef struct {
    float *value;
    Date key;
    int numberOfTransaction, *transaction;
} dailyQuotation;                                                                                                       // the daily quotation of a title

void ITEMfree(dailyQuotation x);
dailyQuotation ITEMnew(int length, Date data);
dailyQuotation ITEMsetvoid();
void ITEMshow(dailyQuotation x);
int KEYeq(Date x, Date y);
Date KEYget(dailyQuotation x);
int KEYgreater(Date x, Date y);
int KEYless(Date x, Date y);

#endif //LAB11_1_DAILYQUOTATION_H