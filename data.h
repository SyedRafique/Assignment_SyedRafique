/*This module contains the input data*/
#include "time.h"
/*MACROS*/
#define SEC_IN_5_MINS (5UL* 60UL * 60UL)
#define NUM_OF_STOCKS 5
#define NUM_OF_TRADES 15

/*User defined aliases for data types (helps when porting code)*/
typedef int     int_type;
typedef double  double_type;
typedef char    char_type;

/*Stock names representing numbers*/
typedef enum{
	TEA,
	POP,
	ALE,
	GIN,
	JOE
}stock_names;

/*holds each trade information*/
typedef struct{
	stock_names stock_sym;
	char_type   stock[4];
	char_type   BuySell[5];
	double_type quantity;
	double_type price;
}trade_info;

/*holds each stock information*/
typedef struct{
	char_type    stock_sym[4];
	char_type    type[10];
	double_type	 last_div;
	double_type  fixed_div;
	double_type  par_val;
	double_type  price;
}stock_info;


/*Stock table*/
static stock_info all_stocks[NUM_OF_STOCKS]{
/*Stock, Type, Last divided, Fixed dividend, Par val*/
	{ "TEA", "common"  ,  0,    0, 100, 20},
	{ "POP", "common"  ,  8,    0, 100, 15},
	{ "ALE", "common"  , 23,    0,  60, 45},
	{ "GIN", "prefered",  8, 0.02, 100, 23},
	{ "JOE", "common"  , 13,    0, 250, 14} 
};

/*Trading Data*/
static trade_info all_trades[NUM_OF_TRADES]{
/*Stock, Buy or Sell, Quantity, Price*/
	{ TEA, "TEA",  "buy", 10,  15 },
	{ POP, "POP",  "buy", 102,  28 },
	{ ALE, "ALE", "sell",  60,  23 },
	{ GIN, "GIN",  "buy", 111,  18 },
	{ JOE, "JOE", "sell", 250,  13 },
	{ ALE, "ALE",  "buy",  10,  12 },
	{ POP, "POP", "sell",  67,  21 },
	{ GIN, "GIN",  "buy",  89,  4 },
	{ TEA, "TEA", "sell",  10,  5 },
	{ JOE, "JOE",  "buy",  10,  3 },
	{ GIN, "GIN", "sell",  45,  9 },
	{ TEA, "TEA",  "buy",  10,  8 },
	{ POP, "POP", "sell",  67,  3 },
	{ GIN, "GIN",  "buy",  10,  7 },
	{ JOE, "JOE",  "buy",  55,  8 }
};							   
