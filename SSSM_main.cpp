/*Main*/
#include "SSSM_Classes.h"

int_type main(){
	Stock  this_stock;
	Trade  this_trade;
	this_stock.div_yld_PE_ratio();
	this_trade.record_trade();
	this_trade.Calculate_VWSP();
	this_trade.Calculate_share_idx();
	this_trade.destroy();
	this_stock.destroy();

	return 0;
}
