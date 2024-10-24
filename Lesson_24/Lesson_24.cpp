#include <iostream>
using namespace std;

// Инкапсуляция собрала воедино 3 переменных и 2 метода
// Инкапсуляция разграничила реализацию и интерфейс

class Date {
private: // Закрываем поля, так как если они будут публичными, то клиент (пользователь класса (другой программист)) сможет передать неверные значения
	unsigned int day = 1; // Правила: Значения в диапазоне от 1-31
	unsigned int month = 1; // 1-12
	int year = 2024;
public:
	void SetDay(unsigned int d) {
		if (d >= 1 && d <= 31) {
			day = d;
		}
		else {
			throw "Было переданно неверное значение в параметр d. Ожидается целое число в диапазоне от 1 до 31 включительно";
		}
	}
	// Все поля будут считаться константными
	unsigned int GetDay() const {
		return day;
	}


	void SetMonth(unsigned int m) {
		if (m >= 1 && m <= 12) {
			month = m;
			// TODO: Add option for user to input 13 as a month number (or anything in custom range), then calculate how many months is that (input - 12)
			// Then set new year - year++; or calculate amount of years - years + years_calculated and set that
			// if input == 13 - set year++; and then month = 1;
			// On top of that optionally ask user for pointer to his month to set it to 1 aswell (or ask for link)
			// Probably should NOT ask user for pointer or link, because user will change Date variable, the one he will send he will probably change later
			// Or already consider it useless because he needs to change Date variable anyway
		}
		else {
			throw "Было переданно неверное значение в параметр m. Ожидается целое число в диапазоне от 1 до 12 включительно";
		}
	}

	unsigned int GetMonth() const {
		return month;
	}


	void SetYear(int y) {
		year = y;
	}

	int GetYear() const {
		return year;
	}


	// Temp function
	void SetDate(unsigned int d, unsigned int m, int y) {
		SetDay(d);
		SetMonth(m);
		SetYear(y);
	}

	void PrintDate() const {
		cout << day << "." << month << "." << year << "\n";
	}

};


class Microwave {
private:
	bool has_power = true;
	string item_inside;
	unsigned short timer_seconds; // Seconds. Min: 10 Max: 1000
	bool button_start = false; // False - regular button position. True - Microwave checks for closed door, starts working until timer is 0.
	// bool door_status = false; // False - closed door. True - opened door.
public:

	void SetHasPower(bool has_power_input) {
		if (has_power_input == true) {
			has_power = true;
		}
		else if (has_power_input == false) {
			has_power = false;
		}
		else {
			throw "Было переданно неверное значение в параметр button_start_input. Ожидается true/false.";
		}
	}

	bool GetHasPower() const {
		return has_power;
	}


	void SetTimer(unsigned short timer_input) {
		if (has_power == true && timer_input >= 10 && timer_input <= 1000) {
			timer_seconds = timer_input;
		}
		else {
			throw "Было переданно неверное значение в параметр timer_input. Ожидается целое число в диапазоне от 10 до 1000 включительно";
		}
	}

	unsigned int GetTimer() const {
		return timer_seconds;
	}


	void SetItems(string item_input) {
		if (item_input != "fork") { // Later on can check if item_input properties doesn't have "metal" in it.
			item_inside = item_input;
		}
		else {
			throw "Было переданно неверное значение в параметр item_input. Ожидается не-металличский предмет.";
		}
	}

	string GetItems() const {
		return item_inside;
	}


	void SetButtonStart(bool button_start_input) {
		if (has_power == true && button_start_input == true) {
			button_start = true;
			// Microwave starts working function call here.
			// After that, button_start = false; automatically
		}
		/*else if (button_start_input == false) {
			button_start = false;
		}*/
		else {
			throw "Было переданно неверное значение в параметр button_start_input. Ожидается true.";
		}
	}

	bool GetButtonStart() const {
		return button_start;
	}


	// TODO: MicrowaveWorking function with return error_code;
};


class Student {
private:
	Student* leader = nullptr;
	bool is_member = true;
	string student_name;
	string learning_program;
	unsigned int student_balance = 0;
	unsigned int cost_per_month = 0;
	Date date_join;
public:
	// Date date_join;

	void SetLeader(Student* leader) {
		if (leader != nullptr) {
			// TODO: Add more ptr checks.
			this->leader = leader;
		}
		else {
			throw "Было переданно неверное значение в параметр leader_input. Ожидается корректный, непустой указатель.";
		}
	}

	Student* GetLeader() const {
		return leader;
	}

	void SetIsMember(bool is_member) {
		if (is_member == 1 || is_member == 0) {
			this->is_member = is_member;
		}
		else {
			throw "Было переданно неверное значение в параметр is_member_input. Ожидается 1 (true) / 0 (false).";
		}
	}

	bool GetIsMember() const {
		return is_member;
	}

	void SetStudentName(string student_name) {
		this->student_name = student_name; // TODO - Add more checks to setter.
	}

	string GetStudentName() const {
		return student_name;
	}

	void SetLearningProgram(string learning_program) {
		this->learning_program = learning_program; // TODO - Add more checks to setter.
	}

	string GetLearningProgram() const {
		return learning_program;
	}

	/// <summary>
	/// Setter for student_balance variable. Generates exception if is_member == false / input value is not >= 0.
	/// </summary>
	/// <param name="student_balance">Student's current balance.</param>
	void SetStudentBalance(unsigned int student_balance) {
		if (this->is_member == true && student_balance >= 0) {
			this->student_balance = student_balance;
		}
		else {
			throw "Было переданно неверное значение в параметр student_input_balance. Ожидается целое число от 0.";
		}
	}

	/// <summary>
	/// Getter for student_balance variable.
	/// </summary>
	/// <returns>Copy of student_balance variable.</returns>
	unsigned int GetStudentBalance() const {
		return student_balance;
	}

	/// <summary>
	/// Setter for cost_per_month variable. Generates exception if is_member == false / input value is not >= 0.
	/// </summary>
	/// <param name="cost_per_month">Learning program cost per month of studying.</param>
	void SetCostPerMonth(unsigned int cost_per_month) {
		if (this->is_member == true && cost_per_month >= 0) {
			this->cost_per_month = cost_per_month;
		}
		else {
			throw "Было переданно неверное значение в параметр cost_per_month_input. Ожидается целое число от 0 включительно.";
		}
	}

	/// <summary>
	/// Getter for cost_per_month variable.
	/// </summary>
	/// <returns>Copy of cost_per_month variable.</returns>
	unsigned int GetCostPerMonth() const {
		return cost_per_month;
	}

	void PrintStudent() const {
		cout << boolalpha; // Printing true / false
		cout << "\n" << "\"" << student_name << "\"" << " student information" << "\n";
		cout << "{" << "\n";
		cout << "Is member: " << is_member << "\n";
		cout << "Student balance: " << student_balance << "\t" << "Cost per-month: " << cost_per_month << "\n";
		cout << "Student's learning program: " << learning_program << "\n";
		cout << "Student's group leader: " << leader->GetStudentName() << "\n";
		cout << "}" << "\n";
		cout << noboolalpha; // Printing 1 / 0
	}

	// TODO: Add setter/getter from Date class. SetDate and Print functions.

};


int main()
{
	setlocale(0, "");
	Date today;
	today.SetDate(21, 10, 2024);
	today.PrintDate();
	
	Student test;
	Student* test_ptr = &test;
	test.SetStudentName("Oleg olegivich dada");
	test.SetLeader(test_ptr);
	test.PrintStudent();


	// test.date_join.
	// В таком случае пользователь может сам выставить параметры даты.
	// А нам это может быть НЕ НУЖНО. Вдруг он выставит другую дату, ниже предыдущей?
	// С другой стороны пользователь это программист и он сам должен продумать взаимодействие с классом и кто может его менять
}