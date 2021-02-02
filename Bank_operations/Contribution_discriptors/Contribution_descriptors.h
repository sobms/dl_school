#pragma once
#include <string.h>
#include <string>
#include <iostream>
namespace Bank_operations {
	typedef struct Date {
		int year;
		int month;
		int day;
		Date() : year(0), month(0), day(0) {};
		friend std::ostream& operator << (std::ostream& out, const Date& date) {
			out << date.day << "." << date.month << "." << date.year << std::endl;
			return out;
		}
		friend std::istream& operator >> (std::istream& in, Date& date) {
			in >> date.day >> date.month>> date.year;
			return in;
		}
	};

	class Standard_deposit {
	private:
		double sum;
		int charge_percent;
		Date date_info[2];
	protected:
		virtual std::ostream& show_info(std::ostream& out) const;
		virtual std::istream& get(std::istream& in);
		int get_charge_percent() const{
			return charge_percent;
		}
		void set_term(int days) {
			date_info[1].day = days;
		}
		Date get_second_date() const {
			return date_info[1];
		}
	public:
		Standard_deposit() : sum(0), charge_percent(0) {
			for (int i = 0; i < 2; i++) {
				date_info[i] = Date();
			}
		}
		Standard_deposit(Date date[2], double deposit_sum = 0, int percent = 0) : sum(deposit_sum), charge_percent(percent) {
			for (int i = 0; i < 2; i++) {
				date_info[i] = date[i];
			}
		}
		// ����������, ������������ � ������������ �� ��������� � � ��� ��������� ������
		double get_sum() const; // ������� sum // ok?
		double count_percents(Date current_date) const; // ����� get_last_date (�� ��������� �������� �� �������) //ok
		Date get_opening_date() const;// ������� date_info[0] // ok
		virtual Date get_last_date() const; // ��� �������� ���� ��������,  ��� ��������/��������� date_info[1];
		virtual void change_last_date(Date new_date); //�������� ���� ��� �������� ��� ��� ���������/��� �������� ������� ������
		virtual void charge_sum(Date current_data, double new_sum); //�������� ���� ��������� �������� + ��������� �������� �� ������� ���� ��� ������� ������ ��� ��������
		friend std::istream& operator >> (std::istream& in, Standard_deposit& deposit) {
			deposit.get(in);
			if (deposit.date_info[1].day == 0) {
				deposit.date_info[1] = deposit.date_info[0];
			}
			return in;
		}
		friend std::ostream& operator << (std::ostream& out, Standard_deposit& deposit) {
			deposit.show_info(out);
			return out;
		}
		virtual Standard_deposit* copy() const {
			return new Standard_deposit(*this);
		};
	};


	class Term_deposit : public Standard_deposit {
	protected:
		virtual std::ostream& show_info(std::ostream& out) const;
		virtual std::istream& get(std::istream& in);
	public:
		Term_deposit() : Standard_deposit() {}
		Term_deposit(Date date[2], double deposit_sum = 0, int percent = 0) : Standard_deposit(date, deposit_sum, percent) {}

		virtual Date get_last_date() const; // ��� �������� ���� ��������,  ��� ��������/��������� date_info[1];
		virtual void change_last_date(Date new_date); //�������� ���� ��� �������� ��� ��� ���������/��� �������� ������� ������
		virtual void charge_sum(Date current_data, double new_sum); //�������� ���� ��������� �������� + ��������� �������� �� ������� ���� ��� ������� ������ ��� ��������
		virtual Term_deposit* copy() const {
			return new Term_deposit(*this);
		};
	};


	class Currency_deposit : public Standard_deposit {
	private:
		double exchange_rate;
		std::string currency_name;
	protected:
		virtual std::ostream& show_info(std::ostream& out) const;
		virtual std::istream& get(std::istream& in);
	public:
		Currency_deposit() : Standard_deposit(), exchange_rate(0) {}
		Currency_deposit(Date date[2], double deposit_sum = 0, int percent = 0, double rate = 0, std::string currency = "euro") : Standard_deposit(date, deposit_sum = 0, percent = 0), exchange_rate(rate), currency_name(currency) {}
		
		virtual Date get_last_date() const;
		virtual void change_last_date(Date new_date);
		virtual void charge_sum(Date current_data, double new_sum);
		virtual Currency_deposit* copy() const {
			return new Currency_deposit(*this);
		};
		double make_conversion() const;
	};
}