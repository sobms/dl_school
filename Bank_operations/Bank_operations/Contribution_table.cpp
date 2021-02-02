#include "pch.h"
#include "../Contribution_discriptors/Contribution_descriptors.h"
#include "Contribution_table.h"
#include <map>
#include <iostream>

namespace Bank_operations {
	Contribution_table::Contribution_table(const Contribution_table& new_tab) {
		if (!new_tab.Table.empty()) {
			Table = new_tab.Table;
		}
	}

	Contribution_table::Contribution_table(Contribution_table&& tab2) : Table(tab2.Table) {}

	Contribution_table& Contribution_table::operator = (const Contribution_table& tab2) {
		if (tab2.Table != Table) {
			//очистка объекта слева от присваивания
			std::map <int, Standard_deposit*>::const_iterator it;
			for (it = Table.begin(); it != Table.end(); it++) {
				delete (*it).second;
			}
			Table.clear();
			// копирование
			Table = tab2.Table;
		}
		return *this;
	}
	Contribution_table& Contribution_table::operator = (Contribution_table&& tab2) {//?
		if (tab2.Table != Table) {
			//очистка объекта слева от присваивания
			std::map <int, Standard_deposit*>::const_iterator it;
			for (it = Table.begin(); it != Table.end(); it++) {
				delete (*it).second;
			}
			Table.clear();
			// копирование
			Table = tab2.Table;
		}
		return *this;
	}

	Contribution_table::~Contribution_table() {
		std::map <int, Standard_deposit*>::const_iterator it;
		for (it = Table.begin(); it != Table.end(); it++) {
			delete (*it).second;
		}
		Table.clear();
	}

	int Contribution_table::add(int account_number, Standard_deposit* new_deposit) {
		std::pair<std::map<int, Standard_deposit*>::iterator, bool> ret = Table.insert(std::pair<int, Standard_deposit*>(account_number, new_deposit));
		return ret.second;
	}
	Standard_deposit* Contribution_table::find(int account_number) const {
		std::map<int, Standard_deposit*>::const_iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return 0;
		}
		return (*res).second->copy();
	}
	void Contribution_table::remove(int account_number) {
		std::map<int, Standard_deposit*>::const_iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return;
		} 
		else {
			Table.erase(account_number);
		}
	}
	int Contribution_table::replace(int account_number, Standard_deposit* new_deposit) {
		std::map<int, Standard_deposit*>::const_iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return 0;
		}
		else {
			Table.erase(account_number);
			Table.insert(std::pair<int, Standard_deposit*>(account_number, new_deposit));
		}
	}
	std::ostream& operator <<(std::ostream& out, const Contribution_table& table) {
		std::map<int, Standard_deposit*>::const_iterator it;
		out << "Countribution table: " << std::endl;
		for (it = table.Table.begin(); it != table.Table.end(); it++) {
			out << (*it).first << " " << (*it).second;
		}
		return out;
	}

}