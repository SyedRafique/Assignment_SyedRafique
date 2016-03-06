/*This module contains the method definations of
the classes Trade and Stock*/
#include "iostream"
#include  "math.h"
#include "SSSM_Classes.h"
#include "string.h"

/*array of pointers to Stock objects*/
static Stock *stock_trade[5];

/*get methods for accessing private members of the classes (encapsulation)*/
double_type Stock::get_quant()const{
	return quant;
}
double_type Stock::get_sum()const{
	return sum;
}
double_type Stock::get_par_value()const{
	return par_value;
}
double_type Stock::get_fixed_dividend()const{
	return fixed_dividend;
}
double_type Stock::get_last_div()const{
	return last_dividend;
}
double_type Stock::get_div_yield()const{

	if (strcmp(this->stock_type, "common") == 0) {
		return ((price != 0) ? (last_dividend / price) : 0);
	}
	else {
		return ((price != 0) ? ((fixed_dividend * par_value) / price) : 0);
	}
}
void Stock::get_stock_name()const{
	std::cout <<stock_name;
}
double_type Stock::get_P_E_ratio()const{
	return ((get_div_yield() != 0) ? (price / get_div_yield()) : 0);
}

/*This function traverses the linked list for each stock, taking the most recent trade events first.
It collects trade information recorded in the last 5 minutes for a particular stock and computes the VWSP*/
void Trade::Calculate_VWSP(){
	time_t timer;
	std::cout << "Calculating Volume weighted stock price" << std::endl;

	for (int_type i = 0; i < NUM_OF_STOCKS; i++){
		if (stock_trade[i] == NULL) {
			std::cout << "Stock unavailable. Trying next available stock";
			continue;
		}
		stock_trade[i]->reset_sum();
		stock_trade[i]->reset_quant();
		/*keep moving towards the start of the list*/
		while (stock_trade[i]->move != NULL){
			time(&timer);
			/*check if the trade was done within the last 5 minutes*/
			if ((timer - stock_trade[i]->move->timestamp) < SEC_IN_5_MINS){
				stock_trade[i]->incr_sum((stock_trade[i]->move->get_price() * stock_trade[i]->move->get_quantity()));
				stock_trade[i]->incr_quant(stock_trade[i]->move->get_quantity());
			}
			else {
				/*stop searching the list once we move outside the 5 minute window*/
				break;
			}
			stock_trade[i]->move = stock_trade[i]->move->prev;
		}
		stock_trade[i]->move  = stock_trade[i]->tail;
		stock_trade[i]->set_VWSP(stock_trade[i]->get_sum() / stock_trade[i]->get_quant());
		stock_trade[i]->reset_sum();
		stock_trade[i]->reset_quant();
		stock_trade[i]->get_stock_name();
		std::cout << " volume weighted stock price: "<< " "<<  stock_trade[i]->get_VWSP()<<"p"<<std:: endl;
	}
}
double_type Stock::get_VWSP()const{
	return VWSP;
}
double_type Trade::get_price()const {
	return price;
}
double_type Trade::get_quantity()const {
	return quantity;
}

/*set methods for assigning values to private members of the classes (encapsulation)*/
void Stock::set_VWSP(const double_type in_VWSP) {
	VWSP = in_VWSP;
}
void Trade::set_time(const time_t in_time){
	timestamp = in_time;
}
void Trade::set_quantity(const double_type in_quant) {
	quantity = in_quant;
}
void Trade::set_BuySell(const char_type *in_BuySell){
	strcpy_s(BuySell, in_BuySell);
}
void Trade::set_price(const double_type in_price){
	price = in_price;
}
void Stock::reset_sum(){
	sum   = 0;
}
void Stock::reset_quant(){
	quant = 0;
}
void Stock::incr_sum(const double_type in_sum){
	sum  += in_sum;
}
void Stock::incr_quant(const double_type in_quant){
	quant += in_quant;
}
void Stock::set_par_value(const double_type in_par){
	par_value = in_par;
}
void Stock::set_fixed_dividend(const double_type in_fix_div){
	fixed_dividend = in_fix_div;
}
void Stock::set_last_div(const double_type in_last_div){
	last_dividend = in_last_div;
}
void Stock::set_price(const double_type input_price){
	price = input_price;
}
void Stock::set_stock_name(const char_type* name){
	strcpy_s(stock_name, name);
}
void Stock::set_stock_type(const char_type* type){
	strcpy_s(stock_type, type);
}

/*Compute Dividend yield and P/E ratio for all stocks */
void Stock::div_yld_PE_ratio(){
	for (int_type i = 0; i < NUM_OF_STOCKS; i++){
		set_stock_name(all_stocks[i].stock_sym);
		set_stock_type(all_stocks[i].type);
		set_last_div(all_stocks[i].last_div);
		set_fixed_dividend(all_stocks[i].fixed_div);
		set_par_value(all_stocks[i].par_val);
		set_price(all_stocks[i].price);
		set_stock_name(all_stocks[i].stock_sym);
		get_stock_name();
		std::cout << std::endl<<"Dividend Yield:" << get_div_yield() << std::endl << "P/E Ratio:" << get_P_E_ratio() << std::endl;
	}
}

/*This function makes a seperate linked list of the trading data for each stock*/
void Trade::record_trade(){
	time_t timer;
	double_type price = 0 , quantity = 0;
	stock_trade[5] = {NULL};
	std::cout << std::endl<<"Recording trades" << std::endl << std::endl;
	for (int_type i = 0; i < NUM_OF_TRADES; i++) {
		time(&timer);
		if (stock_trade[all_trades[i].stock_sym] == NULL) {
			stock_trade[all_trades[i].stock_sym]             = new Stock;
			stock_trade[all_trades[i].stock_sym]->set_stock_name(all_trades[i].stock);
			stock_trade[all_trades[i].stock_sym]->head       = new Trade;
			stock_trade[all_trades[i].stock_sym]->head->prev = NULL;
			stock_trade[all_trades[i].stock_sym]->move       = stock_trade[all_trades[i].stock_sym]->head;
			stock_trade[all_trades[i].stock_sym]->tail       = stock_trade[all_trades[i].stock_sym]->head;
			stock_trade[all_trades[i].stock_sym]->head->next = NULL;
			stock_trade[all_trades[i].stock_sym]->head->set_time(timer);
			stock_trade[all_trades[i].stock_sym]->head->set_quantity(all_trades[i].quantity);
			stock_trade[all_trades[i].stock_sym]->head->set_BuySell(all_trades[i].BuySell);
			stock_trade[all_trades[i].stock_sym]->head->set_price(all_trades[i].price);
		}
		else{
			stock_trade[all_trades[i].stock_sym]->move->next       = new Trade;
			stock_trade[all_trades[i].stock_sym]->move->next->prev = stock_trade[all_trades[i].stock_sym]->move;
			stock_trade[all_trades[i].stock_sym]->move             = stock_trade[all_trades[i].stock_sym]->move->next;
			stock_trade[all_trades[i].stock_sym]->tail			   = stock_trade[all_trades[i].stock_sym]->move;
			stock_trade[all_trades[i].stock_sym]->move->set_time(timer);
			stock_trade[all_trades[i].stock_sym]->move->set_quantity(all_trades[i].quantity);
			stock_trade[all_trades[i].stock_sym]->move->set_BuySell(all_trades[i].BuySell);
			stock_trade[all_trades[i].stock_sym]->move->set_price(all_trades[i].price);
		}
	}
}
void Trade::Calculate_share_idx(){
	double_type product     = 1;
	double_type share_index = 0;
	int num_stocks = 0;
	for (int_type i = 0; i < NUM_OF_STOCKS; i++){
		if (stock_trade[i] == NULL)
			continue;
		if (stock_trade[i]->get_VWSP() != 0){
			product *= stock_trade[i]->get_VWSP();
			num_stocks++;
		}
	}
	share_index = pow(product, ((double_type)1 / num_stocks));
	std::cout << "Share Index:" << share_index;
}

/*Functions used to destroy dynamically allocated memory*/
void Trade::destroy() {
	Trade *del = NULL;
	for (int_type i = 0; i < NUM_OF_STOCKS; i++) {
		del = stock_trade[i]->head;
		while (del != stock_trade[i]->tail) {
			del = del->next;
			delete(del->prev);
		}
		delete(stock_trade[i]->tail);
	}
}
void Stock::destroy() {
	for (int_type i = 0; i < NUM_OF_STOCKS; i++) {
		delete(stock_trade[i]);
	}
}

/*Destructors*/
Trade::~Trade(){

}
Stock::~Stock() {

}

/*Constructors*/
Trade::Trade() {

}

Stock::Stock() {

}