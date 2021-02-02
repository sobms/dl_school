#include "pch.h"
#include <iostream>
#include <string.h>
#include <string>
#include "Contribution_descriptors.h"
#include <typeinfo>

namespace Bank_operations {

	std::ostream& Standard_deposit::show_info(std::ostream& out) const {
		out << "Deposit type: " << "Standard_deposit" << std::endl;
		out << "Deposit sum = " << sum << std::endl;
		out << "Charge percent = " << charge_percent << std::endl;
		out << "Opening date: " << date_info[0] << std::endl;
		out << "Last_operation_date: " << date_info[1] << std::endl;
		return out;
	}
	std::istream& Standard_deposit::get(std::istream& in) {
		std::cout << "Enter deposit sum: " << std::endl;
		in >> sum;
		std::cout << "Enter Charge_percent: " << std::endl;
		in >> charge_percent;
		std::cout << "Enter opening date" << std::endl;
		in >> date_info[0];
		return in;
	}
	double Standard_deposit::get_sum() const {
		return sum;
	}
	double Standard_deposit::count_percents(Date current_date) const { // текуща€ дата - дата последней операции
		Date last_date = get_last_date();
		int delta = (current_date.year * 372 + current_date.month * 31 + current_date.day) - (last_date.year * 372 + last_date.month * 31 + last_date.day);
		if (typeid(*this) == typeid(Term_deposit)) {
			delta = ((delta < this->date_info[1].day) ? delta : this->date_info[1].day);
		}
		if (delta < 0) {
			throw std::exception("Incorrect current_date");
			return 0;
		}
		return delta / 31.0 * (charge_percent/100.0) * sum; // мес€чный процент
	}
	Date Standard_deposit::get_opening_date() const {
		return date_info[0];
	}
	Date Standard_deposit::get_last_date() const {
		return date_info[1];
	}
	void Standard_deposit::change_last_date(Date new_date) {
		date_info[1] = new_date;
	}
	void Standard_deposit::charge_sum(Date current_data, double new_sum) {//?
		change_last_date(current_data);
		sum = new_sum;
	}
	std::ostream& Term_deposit::show_info(std::ostream& out) const {
		out << "Deposit type: " << "Term_deposit" << std::endl;
		out << "Deposit sum = " << get_sum() << std::endl;
		out << "Charge percent = " << get_charge_percent() << std::endl;
		out << "Opening date: " << get_opening_date() << std::endl;
		out << "Term of deposit: " << get_second_date().day << " days" << std::endl;
		return out;
	}
	std::istream& Term_deposit::get(std::istream& in) {
		Standard_deposit::get(in);
		std::cout << "Enter term of deposit in days :" << std::endl;
		
		int days = 0;
		do {
			in >> days;
		} while (days<=0);
		set_term(days);
		return in;
	}
	Date Term_deposit::get_last_date() const {
		return get_opening_date();
	}
	void Term_deposit::change_last_date(Date new_date) {
		throw std::exception("Impossible to change date of last operation. Please close deposit");
	}
	void Term_deposit::charge_sum(Date current_data, double new_sum) {
		throw std::exception("Impossible to change sum of term deposit before the deadline");
	}

	std::ostream& Currency_deposit::show_info(std::ostream& out) const {
		out << "Deposit type: " << "Currency_deposit" << std::endl;
		out << "Deposit sum = " << get_sum() << std::endl;
		out << "Charge percent = " << get_charge_percent() << std::endl;
		out << "Opening date: " << get_opening_date() << std::endl;
		out << "Last_operation_date: " << get_last_date() << std::endl;
		out << "Currency name: " << currency_name << std::endl;
		out << "Exchange rate = " << exchange_rate << std::endl;
		return out;
	}
	std::istream& Currency_deposit::get(std::istream& in) {
		Standard_deposit::get(in);
		std::cout << "Enter currency name: " << std::endl;
		in >> currency_name;
		std::cout << "Enter exchange rate: " << std::endl;
		in >> exchange_rate;
		return in;
	}
	Date Currency_deposit::get_last_date() const {
		return Standard_deposit::get_last_date();
	}
	void Currency_deposit::change_last_date(Date new_date) {
		Standard_deposit::change_last_date(new_date);
	}
	void Currency_deposit::charge_sum(Date current_data, double new_sum) {//?
		Standard_deposit::charge_sum(current_data, new_sum);
	}
	double Currency_deposit::make_conversion() const{
		return (get_sum() * exchange_rate);
	}
}
