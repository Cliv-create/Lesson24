#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

// Инкапсуляция собрала воедино 3 переменных и 2 метода
// Инкапсуляция разграничила реализацию и интерфейс

class Date {
private: // Закрываем поля, так как если они будут публичными, то клиент (пользователь класса (другой программист)) сможет передать неверные значения
	unsigned short day = 1; // Правила: Значения в диапазоне от 1-31
	unsigned short month = 1; // 1-12
	int year = 2024;
public:
	/// <summary>
	/// Empty constructor. Uses Windows API to get current day, month, year to initialize the variable.
	/// </summary>
	Date() {
		SYSTEMTIME st;
		GetSystemTime(&st);
		day = st.wDay;
		month = st.wMonth;
		year = st.wYear;
	}

	/// <summary>
	/// Main constructor. Uses Setters to set day, month and year.
	/// </summary>
	/// <param name="day">Value between 1 and 31</param>
	/// <param name="month">Value between 1 and 12</param>
	/// <param name="year">Any given INT value</param>
	Date(unsigned short day, unsigned short month, int year) {
		SetDay(day);
		SetMonth(month);
		SetYear(year);
	}

	void SetDay(unsigned short d) {
		if (d >= 1 && d <= 31) {
			day = d;
		}
		else {
			throw "Было переданно неверное значение в параметр d. Ожидается целое число в диапазоне от 1 до 31 включительно";
		}
	}
	// Все поля будут считаться константными
	unsigned short GetDay() const {
		return day;
	}


	void SetMonth(unsigned short m) {
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

	unsigned short GetMonth() const {
		return month;
	}


	void SetYear(int y) {
		year = y;
	}

	int GetYear() const {
		return year;
	}


	// Temp function
	
	/// <summary>
	/// Setter for day, month, year. Uses 3 Setters for values.
	/// </summary>
	/// <param name="day">Value between 1 and 31</param>
	/// <param name="month">Value between 1 and 12</param>
	/// <param name="year">Any given INT value</param>
	void SetDate(unsigned short day, unsigned short month, int year) {
		SetDay(day);
		SetMonth(month);
		SetYear(year);
	}

	void PrintDate() const {
		cout << day << "." << month << "." << year << "\n";
	}

};


class Microwave {
private:
	bool has_power = true;
	string item_inside;
	unsigned short timer_seconds = 0; // Seconds. Min: 10 Max: 1000
	bool button_start = false; // False - regular button position. True - Microwave checks for closed door, starts working until timer is 0.
	// bool door_status = false; // False - closed door. True - opened door.
public:

	/*
	Microwave() {
		SetHasPower(false);
		SetItems("");
		SetTimer(10);
		SetButtonStart(false);
	}
	*/
	

	Microwave(bool has_power = false, string item_inside = "empty", unsigned short timer_seconds = 10, bool button_start = false) {
		SetHasPower(has_power);
		SetItems(item_inside);
		// timer_seconds = 0;
		// SetTimer(timer_seconds);
		// SetButtonStart(button_start);
		
		if (has_power == true) SetTimer(timer_seconds);
		else timer_seconds = 0;
		if (button_start == true) SetButtonStart(button_start);
		else button_start = false;
		
		
	}

	/// <summary>
	/// Setter for has_power (bool) value. Throws exception.
	/// </summary>
	/// <param name="has_power">bool value. Accepts true or false.</param>
	void SetHasPower(bool has_power) {
		if (has_power == true) {
			this->has_power = true;
		}
		else if (has_power == false) {
			this->has_power = false;
		}
		else {
			throw "Было переданно неверное значение в параметр button_start_input. Ожидается true/false.";
		}
	}

	bool GetHasPower() const {
		return has_power;
	}


	/// <summary>
	/// Setter for timer_seconds value. Accepts values between 10 and 1000, and if has_power == true. Throws exception.
	/// </summary>
	/// <param name="timer_seconds">unsigned short value between 10 and 1000.</param>
	void SetTimer(unsigned short timer_seconds) {
		if (has_power == true && timer_seconds >= 10 && timer_seconds <= 1000) {
			this->timer_seconds = timer_seconds;
		}
		else {
			throw "Было переданно неверное значение в параметр timer_input. Ожидается целое число в диапазоне от 10 до 1000 включительно";
		}
	}

	unsigned int GetTimer() const {
		return timer_seconds;
	}

	/// <summary>
	/// Setter for item_inside (string) value. Doesn't accept empty strings and string that are longer then 50 charachters (not including symbol with code 0).
	/// </summary>
	/// <param name="item_inside">String value.</param>
	void SetItems(string item_inside) {
		if (item_inside != "fork" && !item_inside.empty()) { // Later on can check if item_input properties doesn't have "metal" in it. Optionally can add && !(item_inside.size() > 50)
			if (item_inside.size() > 50) {
				throw "Было переданно неверное значение в параметр item_input. Ожидается строка не больше 50 символов.";
			}
			this->item_inside = item_inside;
		}
		else {
			throw "Было переданно неверное значение в параметр item_input. Ожидается не-металличский предмет / непустая строка.";
		}
	}

	string GetItems() const {
		return item_inside;
	}

	/// <summary>
	/// Function to "start" the microwave. Checks if Microwave has power and input value is 1 (exception otherwise). After Microwave finishes "working", sets button_start to 0.
	/// </summary>
	/// <param name="button_start">bool value for starting the microwave. Accepts 1, exception otherwise.</param>
	void SetButtonStart(bool button_start) {
		if (has_power == true && button_start == 1) {
			this->button_start = true;
			// Microwave starts working function call here.
			// After that, button_start = false; automatically
			MicrowaveWorking();
			button_start = false;
		}
		/*else if (button_start_input == false) {
			button_start = false;
		}*/
		else {
			throw "Было переданно неверное значение в параметр button_start. Ожидается 1 (true) и параметр has_power == true.";
		}
	}

	bool GetButtonStart() const {
		return button_start;
	}

	/// <summary>
	/// Function "starts" the Microwave, working for amount of seconds specified in timer_seconds value. Sets timer_seconds to 0 after finished "working".
	/// </summary>
	void MicrowaveWorking() {
		if (true) { // Set to true because of Setter not allowing empty strings. Check if item_inside string is not empty !item_inside.empty()
			cout << "Microwave starts cooking " << item_inside << "..." << "\n";
			for (short i = 0; i < timer_seconds; i++)
			{
				cout << "BZZZZ..." << "\n";
				Sleep(1000);
			}
			cout << "Microwave stops working. " << item_inside << " is finished cooking." << "\n";
		}
		else {
			throw "Было передано неверное значение в параметр item_inside. Ожидается непустая строка.";
		}
		timer_seconds = 0;
		// item_inside = ""; // Optional
	}
};


class Student {
private:
	int* rates = nullptr;
	int rates_count = 0;
	Student* leader = nullptr;
	bool is_member = true;
	string student_name;
	string learning_program;
	unsigned int student_balance = 0;
	unsigned int cost_per_month = 0;
	Date date_join;
public:
	// Date date_join;

	/*
	
	Student() : Student(nullptr, true, "none", "none", 0, 0) { }
	
	Student(Student* leader, bool is_member, string student_name, string learning_program, unsigned int student_balance, unsigned int cost_per_month) {
		if (leader != nullptr) SetLeader(leader);
		else leader = nullptr;
		SetIsMember(is_member);
		SetStudentName(student_name);
		SetLearningProgram(learning_program);
		SetStudentBalance(student_balance);
		SetCostPerMonth(cost_per_month);
	}
	*/

	Student(Student* leader = nullptr, bool is_member = true, string student_name = "none", string learning_program = "none", unsigned int student_balance = 0, unsigned int cost_per_month = 0) {
		if (leader != nullptr) SetLeader(leader);
		else leader = nullptr;
		SetIsMember(is_member);
		SetStudentName(student_name);
		SetLearningProgram(learning_program);
		SetStudentBalance(student_balance);
		SetCostPerMonth(cost_per_month);
	}


	void AddRate(int rate) {
		if (rate < 1 || rate > 12) throw "Incorrect value (1-12 expected).";
		if (rates_count == 0) {
			rates = new int[1];
			rates[0] = rate;
		}
		else {
			int* temp = new int[rates_count + 1];
			for (int i = 0; i < rates_count; i++)
				temp[i] = rates[i];
			temp[rates_count] = rate;
			delete[] rates;
			rates = temp;
		}
		rates_count++;
	}

	vector<int> GetRates() const {
		vector<int> temp;
		for (int i = 0; i < rates_count; i++)
		{
			temp.push_back(rates[i]);
		}
		return temp;
	}

	int GetRateByIndex(unsigned int index) {
		if (index >= rates_count) throw "Incorrect index!\n";
		return rates[index];
	}


	void SetLeader(Student* leader) {
		/*
		if (Student* student = dynamic_cast<Student*>(leader)) {
			cout << "студент либо его потомок";
		}
		else {
			cout << "что-то другое по типу";
		}
		*/

		this->leader = leader;
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
		if (!student_name.empty()) {
			this->student_name = student_name; // TODO - Add more checks to setter.
		}
		else {
			throw "Было переданно неверное значение в параметр student_name. Ожидается непустая строка.";
		}
	}

	string GetStudentName() const {
		return student_name;
	}


	void SetLearningProgram(string learning_program) {
		if (!learning_program.empty()) {
			this->learning_program = learning_program; // TODO - Add more checks to setter.
		}
		else {
			throw "Было переданно неверное значение в параметр learning_program. Ожидается непустая строка.";
		}
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
	
	
	~Student() {
		/*
		if (name != nullptr) {
			delete[] name;
			name = nullptr;
		}
		*/
		if (rates != nullptr) {
			delete[] rates;
			rates = nullptr;
		}
	}
	
	

};


int main()
{
	setlocale(0, "");
	Date today;
	today.PrintDate();
	today.SetDate(21, 10, 2024);
	today.PrintDate();
	
	Student test;
	/*
	Student* test_ptr = &test;
	test.SetStudentName("Oleg olegivich");
	test.SetLeader(test_ptr);
	test.PrintStudent();
	*/
	

	Microwave test2;
	/*
	test2.SetHasPower(true);
	test2.SetTimer(10);
	test2.SetItems("Tasty meal");
	test2.SetButtonStart(true);
	*/
	
	// test.date_join.
	// В таком случае пользователь может сам выставить параметры даты.
	// А нам это может быть НЕ НУЖНО. Вдруг он выставит другую дату, ниже предыдущей?
	// С другой стороны пользователь это программист и он сам должен продумать взаимодействие с классом и кто может его менять
}