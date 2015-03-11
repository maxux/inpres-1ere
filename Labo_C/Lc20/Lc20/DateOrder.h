#define ORDER_BY_DAY		0
#define ORDER_BY_MONTH		1
#define ORDER_BY_YEAR		2

void affect_x_data(short *pdest, short *psource, short count);
void order_date(short *date, short tsize, short *targ, short order_by);
void order_date_by(short *date, short tsize, short order_by);
void order_date_all(short *date, short tsize);