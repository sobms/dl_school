#pragma once
#include "../Contribution_discriptors/Contribution_descriptors.h";
#include "../MyMap/MyMap.h"
#include <iostream>

namespace Bank_operations {
	class Contribution_table {
	private:
		My_Map<int, Standard_deposit*> Table;
	public:
		Contribution_table() {};
		Contribution_table(const Contribution_table& new_tab);
		Contribution_table(Contribution_table&& tab2);
		Contribution_table& operator = (const Contribution_table& tab2);
		Contribution_table& operator = (Contribution_table&& tab2);
		~Contribution_table();
		int add (int account_number, Standard_deposit* new_deposit);
		int replace(int account_number, Standard_deposit* new_deposit);
		Standard_deposit* find(int account_number) const;
		void remove(int account_number);
		friend std::ostream& operator <<(std::ostream& out, const Contribution_table& table);
		My_Map<int, Standard_deposit*>::Iterator it_begin() {
			return Table.begin();
		}
		My_Map<int, Standard_deposit*>::Iterator it_end() {
			return Table.end();
		}
	};
}