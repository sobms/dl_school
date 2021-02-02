#pragma once
#include <iostream>
#include "../Contribution_discriptors/Contribution_descriptors.h"
#include "../Bank_operations/Contribution_table.h";
#include <Windows.h>
#include <typeinfo>

namespace Bank_operations {

	void Open_account(Contribution_table& tab) {
		double deposit_sum;
		int account, charge_percent, type;
		std::cout << "Enter_account_number: " << std::endl;
		std::cin >> account;
		do {
			system("cls");
			std::cout << "Enter_type_of_deposit: 1. Standard 2. Term 3. Currency" << std::endl;
			std::cin >> type;
			if (!std::cin.good()) {
				std::cout << "Input don't correct";
				std::cin.ignore(10000, '\n');
				std::cin.clear();
				Sleep(3000);
			}
		} while ((type > 3) || (type < 0));

		Standard_deposit* new_deposit = nullptr;
		Standard_deposit d1;
		Term_deposit d2;
		Currency_deposit d3;
		switch (type) {
		case 1:
			new_deposit = &d1;
			break;
		case 2:
			new_deposit = &d2;
			break;
		case 3:
			new_deposit = &d3;
			break;
		}
		std::cin >> (*new_deposit);
		if (tab.add(account, new_deposit->copy())) {
			std::cout << "Success!";
		}
		else {
			std::cout << "Account already exist!";
		}
	}

	void Show_account_status(Contribution_table& tab) {
		int account;
		Date today_date;
		std::cout << "Enter account number: " << std::endl;
		std::cin >> account;
		std::cout << "Enter today_date: " << std::endl;
		std::cin >> today_date;
		Standard_deposit* f_deposit;
		try {
			f_deposit = tab.find(account);
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			return;
		}
		std::cout << (*f_deposit);
		std::cout << "Accurals_from_percents: ";
		try {
			std::cout << f_deposit->count_percents(today_date) << std::endl;
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			return;
		}
	}
	void Close_account(Contribution_table& tab) {
		int account;
		Date today_date;
		std::cout << "Enter account number to close: " << std::endl;
		std::cin >> account;
		std::cout << "Enter today_date: " << std::endl;
		std::cin >> today_date;
		Standard_deposit* f_deposit;
		try {
			f_deposit = tab.find(account);
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			return;
		}
		std::cout << "Deposit sum: ";
		std::cout << f_deposit->get_sum() << std::endl;
		std::cout << "Accurals_from_percents: ";
		try {
			std::cout << f_deposit->count_percents(today_date) << std::endl;
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			return;
		}
		tab.remove(account);
		std::cout << "Account closed.";
	}
	void Work_with_account(Contribution_table& tab) {
		//выбираем тип операции со счЄтом
		int type;
		do {
			system("cls");
			std::cout << "Enter_number_of_function: 1. Put the money 2. Get deposit money 3. Get percents" << std::endl;
			std::cin >> type;
			if (!std::cin.good()) {
				std::cout << "Input don't correct";
				std::cin.ignore(10000, '\n');
				std::cin.clear();
				Sleep(3000);
			}
		} while ((type > 3) || (type < 0));
		//ищем счЄт дл€ изменени€
		int account;
		std::cout << "Enter_account_number: " << std::endl;
		std::cin >> account;
		Standard_deposit* f_deposit;
		try {
			f_deposit = tab.find(account);
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
			return;
		}
		//ввод сегодн€шней даты
		Date today_date;
		std::cout << "Enter today_date: " << std::endl;
		std::cin >> today_date;

		double percents, sum;
		switch (type) {
		case 1:
			std::cout << "Enter sum which you want to add to your deposit: ";
			double additional_sum;
			std::cin >> additional_sum;
			sum = f_deposit->get_sum();
			try{
			percents = f_deposit->count_percents(today_date);
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			try {
				f_deposit->charge_sum(today_date, (sum + percents + additional_sum));
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			tab.replace(account, f_deposit);
			std::cout << "You added: " << additional_sum << std::endl;
			break;
		case 2:
			std::cout << "Enter sum which you want to get: ";
			double return_sum;
			std::cin >> return_sum;
			sum = f_deposit->get_sum();
			try {
			percents = f_deposit->count_percents(today_date);
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			try {
				f_deposit->charge_sum(today_date, (sum + percents - return_sum));
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			tab.replace(account, f_deposit);
			std::cout << "You took back: " << return_sum;
			break;
		case 3:
			Date last_date = f_deposit->get_last_date();
			try {
				percents = f_deposit->count_percents(today_date);
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			std::cout << "Your sum accrued by percents from " << last_date << " = " << percents << std::endl;
			try {
				f_deposit->change_last_date(today_date);
			}
			catch (std::exception& error) {
				std::cout << error.what() << std::endl;
				return;
			}
			tab.replace(account, f_deposit);
			break;
		}
	}
	void Get_all_accounts(Contribution_table& tab) {
		My_Map<int, Standard_deposit*>::Iterator it(tab.it_begin());
		for (; it != tab.it_end(); it++) {
			std::cout << "Account number: " << (*it)->first << std::endl;
			std::cout << (*((*it)->second)) << std::endl;
		}
	}

}