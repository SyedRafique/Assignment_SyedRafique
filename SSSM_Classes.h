/*This module contains the class definations*/
#include "data.h"

/*Trade and Stock class definations and declarations of their member methods and variables*/
class Trade{
public:
	Trade();
	~Trade();
	void destroy();
	void  set_time(const time_t in_time);
	void  set_quantity(const double_type in_quant);
	void  set_BuySell(const char_type *in_BuySell);
	void  set_price(const double_type in_price);
	void  Calculate_share_idx();
	void  Calculate_VWSP();
	void  record_trade();
	double_type get_price()const;
	double_type get_quantity()const;
	Trade *next;
	Trade *prev;

private:
	time_t       timestamp;
	char_type    stock_symbol[4];
	double_type  quantity;
	char_type    BuySell[5];
	double_type  price;
};

class Stock{
public:
	Stock();
	~Stock();
	void destroy();
	double_type get_VWSP()const;
	double_type get_sum()const;
	double_type get_quant()const;
	double_type get_fixed_dividend()const;
	double_type get_par_value()const;
	double_type get_last_div()const;
	double_type get_div_yield()const;
	double_type get_P_E_ratio()const;
	void        get_stock_name()const;
	void        set_VWSP(const double_type in_VWSP);
	void        set_fixed_dividend(const double_type in_fix_div);
	void        set_par_value(const double_type in_par);
	void        set_last_div(const double_type in_last_div);
	void        set_price(const double_type price);
	void        set_stock_name(const char_type *name);
	void        set_stock_type(const char_type *type);
	void        div_yld_PE_ratio();
	void        reset_sum();
	void        reset_quant();
	void        incr_sum(const double_type in_sum);
	void        incr_quant(const double_type in_quant);

	Trade* move;
	Trade* tail;
	Trade* head;

private:
	double_type  VWSP;
	double_type  sum;
	double_type  quant;
	double_type  last_dividend;
	double_type  fixed_dividend;
	double_type  par_value;
	double_type  price;
	char_type    stock_name[4];
	char_type    stock_type[10];
};