#include "pch.h"
#include "../Contribution_discriptors/Contribution_descriptors.h"
#include "Contribution_table.h"
#include "../MyMap/MyMap.h"
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
			My_Map <int, Standard_deposit*>::Iterator it(Table.begin());
			for (; it != Table.end(); it++) {
				delete (*it)->second;
			}
			//Table.clear();
			// копирование
			Table = tab2.Table;
		}
		return *this;
	}
	Contribution_table& Contribution_table::operator = (Contribution_table&& tab2) {//?
		if (tab2.Table != Table) {
			//очистка объекта слева от присваивания
			My_Map <int, Standard_deposit*>::Iterator it(Table.begin());
			for (; it != Table.end(); it++) {
				delete (*it)->second;
			}
			//Table.clear();
			// копирование
			Table = tab2.Table;
		}
		return *this;
	}

	Contribution_table::~Contribution_table() {
		My_Map <int, Standard_deposit*>::Iterator it(Table.begin());
		for (; it != Table.end(); it++) {
			delete (*it)->second;
		}
		//Table.clear();
	}

	int Contribution_table::add(int account_number, Standard_deposit* new_deposit) {
		int res = Table.insert(MyPair<int, Standard_deposit*>(account_number, new_deposit).copy());
		return res;
	}
	Standard_deposit* Contribution_table::find(int account_number) const {
		My_Map<int, Standard_deposit*>::Iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return 0;
		}
		return (*res)->second->copy();
	}
	void Contribution_table::remove(int account_number) {
		My_Map<int, Standard_deposit*>::Iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return;
		} 
		else {
			Table.erase(account_number);
		}
	}
	int Contribution_table::replace(int account_number, Standard_deposit* new_deposit) {
		My_Map<int, Standard_deposit*>::Iterator res = Table.find(account_number);
		if (res == Table.end()) {
			throw std::exception("Account don't exist!");
			return 0;
		}
		else {
			Table.erase(account_number);
			Table.insert(MyPair<int, Standard_deposit*>(account_number, new_deposit).copy());
		}
	}
	std::ostream& operator <<(std::ostream& out, const Contribution_table& table) {
		My_Map<int, Standard_deposit*>::Iterator it(table.Table.begin());
		out << "Countribution table: " << std::endl;
		for (; it != table.Table.end(); it++) {
			out << (*it)->first << " " << (*it)->second;
		}
		return out;
	}

}