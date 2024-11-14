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


	int operator - (/*const Fraction* this, */ Date& right) {
		// this-> это как left. в глобальной функции
		int JDN, JDN2, jdn_result;
		// JDN = this->date
		JDN = (1461 * (year + 4800 + (month - 14) / 12)) / 4 + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075;
		JDN2 = (1461 * (right.year + 4800 + (right.month - 14) / 12)) / 4 + (367 * (right.month - 2 - 12 * ((right.month - 14) / 12))) / 12 - (3 * ((right.year + 4900 + (right.month - 14) / 12) / 100)) / 4 + right.day - 32075;
		jdn_result = JDN - JDN2;
		return jdn_result;
	}

	/// <summary>
	/// Returns date in JDN format.
	/// </summary>
	explicit operator int(/*const Fraction* this*/)
	{
		// Returns date in JDN format.
		// cout << "Casting from Fraction to int\n";
		int JDN = (1461 * (this->year + 4800 + (this->month - 14) / 12)) / 4 + (367 * (this->month - 2 - 12 * ((this->month - 14) / 12))) / 12 - (3 * ((this->year + 4900 + (this->month - 14) / 12) / 100)) / 4 + this->day - 32075;
		return JDN;
	}

	/// <summary>
	/// Returns date as string. Format: DD.MM.YYYY
	/// </summary>
	explicit operator string()
	{
		// cout << "Casting from Fraction to string\n";
		return to_string(day) + "." + to_string(month) + "." + to_string(year);
	}

	/// <summary>
	/// Returns Day, Month, Year variables. 0 - Day, 1 - Month, >1 - Year.
	/// </summary>
	/// <param name="index">Index value to return Day, Month, Year (0, 1, >1).</param>
	/// <returns>Day, Month, Year variable.</returns>
	int operator [] (unsigned int index)
	{
		// cout << "Operator []\n";
		if (index == 0) return GetDay();
		else if (index == 1) return GetMonth();
		else return GetYear();
	}

	/// <summary>
	/// Setting day, month, year variables.
	/// </summary>
	/// <param name="day">Type: unsigned short day</param>
	/// <param name="month">Type: unsigned short month</param>
	/// <param name="year">Type: int year</param>
	void operator () (unsigned short day, unsigned short month, int year) {
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

ostream& operator << (ostream& os, const Date& date);
istream& operator >> (istream& is, Date& date);

ostream& operator << (ostream& os, const Date& date)
{
	date.PrintDate();
	return os;
}

istream& operator >> (istream& is, Date& date)
{
	int day, month, year;

	cout << "Enter day: ";
	is >> day;
	cout << "Enter month: ";
	is >> month;
	cout << "Enter year: ";
	is >> year;

	date.SetDay(day);
	date.SetMonth(month);
	date.SetYear(year);

	return is;
}

class Microwave {
private:
	static int microwave_count;
	bool has_power = true;
	string item_inside;
	unsigned short timer_seconds = 0; // Seconds. Min: 10 Max: 1000
	bool button_start = false; // False - regular button position. True - Microwave checks for closed door, starts working until timer is 0.
	// bool door_status = false; // False - closed door. True - opened door.
public:
	Microwave() : Microwave(false, "empty", 10, false) { }

	explicit Microwave(string item_inside) : Microwave(false, item_inside, 10, false) { }

	// false, "empty", 10, false
	Microwave(bool has_power, string item_inside, unsigned short timer_seconds, bool button_start) {
		SetHasPower(has_power);
		SetItems(item_inside);
		// timer_seconds = 0;
		// SetTimer(timer_seconds);
		// SetButtonStart(button_start);
		
		if (has_power == true) SetTimer(timer_seconds);
		else timer_seconds = 0;
		if (button_start == true) SetButtonStart(button_start);
		else button_start = false;
		microwave_count++;
	}


	static int GetMicrowaveCount() {
		return microwave_count;
	}

	~Microwave() {
		microwave_count--;
	}

	explicit operator string()
	{
		// cout << "Casting from Fraction to string\n";
		return "has_power: " + to_string(has_power) + " " + "button_start: " + to_string(button_start) + " " + "timer_seconds: " + to_string(timer_seconds) + " " + "item_inside: " + item_inside;
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

	void PrintMicrowave() const {
		printf("\nMicrowave has power: %s\n", has_power ? "true" : "false");
		// printf("Item inside: %s\n", item_inside); // Doesn't work
		cout << "Item inside: " << item_inside << "\n";
		printf("Timer in seconds: %i\n", timer_seconds);
		printf("Microwave started: %s\n\n", button_start ? "true" : "false");
	}

};
int Microwave::microwave_count = 0;

ostream& operator << (ostream& os, const Microwave& microwave);
istream& operator >> (istream& is, Microwave& microwave);

ostream& operator << (ostream& os, const Microwave& microwave)
{
	microwave.PrintMicrowave();
	return os;
}

istream& operator >> (istream& is, Microwave& microwave)
{
	bool has_power;
	string item_inside;

	cout << "Enter has_power: ";
	is >> has_power;

	cin.ignore();
	cout << "Enter item_inside: ";
	// is >> item_inside;
	getline(cin, item_inside);
	cin.ignore();

	microwave.SetHasPower(has_power);
	microwave.SetItems(item_inside);

	return is;
}

class Student {
private:
	static int students_count;
	int* rates = nullptr;
	unsigned int rates_count = 0;
	int* balance = 0;
	int balance_count = 0;
	Student* leader = nullptr;
	bool is_member = true;
	string student_name;
	string learning_program;
	unsigned int student_balance = 0;
	unsigned int cost_per_month = 0;

	// TODO: Add average number variables.
	int total_rates = 0; // All rates added together
	int average_rate = 0; // Take total_rates and divide by rates_count. Result - averate_rate variable.
	// Each time rate is added - re-calculate the rates.
	// total_rates += rate;
	// averate_rate = total_rates / rates_count
	

	Date date_join;
	Date date_leave;
public:
	
	// //////////// //////////// //////////// ////////////
	// Constructors / Destructors / Operator overload

	Student() : Student(nullptr, true, "none", "none", 0, 0) { }

	explicit Student(string name) : Student(nullptr, true, name, "none", 0, 0) { }

	explicit Student(string name, string learning_program) : Student(nullptr, true, name, learning_program, 0, 0) { }
	
	// Main c-tor
	Student(Student* leader, bool is_member, string student_name, string learning_program, unsigned int student_balance, unsigned int cost_per_month) {
		if (leader != nullptr) SetLeader(leader);
		else leader = nullptr;
		SetIsMember(is_member);
		SetStudentName(student_name);
		SetLearningProgram(learning_program);
		SetStudentBalance(student_balance);
		SetCostPerMonth(cost_per_month);
		students_count++;
	}
	

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
		students_count--;
	}

	Student(const Student& original) {
		for (int rate : original.GetRates()) {
			/*this->*/AddRate(rate);
		}
		// TODO: Uncomment once balance dynamic array is used.
		//for (int balance_entry : original.GetBalance()) {
		//	/*this->*/AddBalanceEntry(balance_entry);
		//}
		this->rates_count = original.rates_count;
		this->balance_count = original.balance_count;
		this->is_member = original.is_member;
		this->student_name = original.student_name;
		this->learning_program = original.learning_program;
		this->student_balance = original.student_balance;
		this->cost_per_month = original.cost_per_month;
		students_count++;
	}

	Student& operator = (/*const Student* this, */const Student& original) {
		if (this == &original) {
			return *this;
		}
		Student::~Student();
		Student::Student(original);
	}

	bool operator > (/*const Fraction* this, */const Student& right) {
		// this-> это как left. в глобальной функции
		return (this->average_rate > right.average_rate);
	}

	bool operator < (/*const Fraction* this, */const Student& right) {
		// this-> это как left. в глобальной функции
		return !(this->average_rate > right.average_rate);
	}

	bool operator == (/*const Fraction* this, */const Student& right) {
		// this-> это как left. в глобальной функции
		return (this->average_rate == right.average_rate);
	}

	bool operator != (/*const Fraction* this, */const Student& right) {
		// this-> это как left. в глобальной функции
		return !(this->average_rate == right.average_rate);
	}

	explicit operator string()
	{
		/*
		name
		is_member
		balance
		program
		group leader
		*/
		return "student_name: " + student_name + " " + "is_member: " + to_string(is_member) + " " + "student_balance: " + to_string(student_balance) + " " + "learning_program: " + learning_program;
	}


	// Constructors / Destructors / Operator overload
	// /////// /////// /////// /////// /////// ///////
	// Setters

	void SetDateJoin(const Date& date_join) {
		this->date_join = date_join;
	}

	void SetDateLeave(const Date& date_leave) {
		this->date_leave = date_leave;
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

	void SetIsMember(bool is_member) {
		if (is_member == 1 || is_member == 0) {
			this->is_member = is_member;
		}
		else {
			throw "Было переданно неверное значение в параметр is_member_input. Ожидается 1 (true) / 0 (false).";
		}
	}

	void SetStudentName(string student_name) {
		if (!student_name.empty()) {
			this->student_name = student_name; // TODO - Add more checks to setter.
		}
		else {
			throw "Было переданно неверное значение в параметр student_name. Ожидается непустая строка.";
		}
	}

	void SetLearningProgram(string learning_program) {
		if (!learning_program.empty()) {
			this->learning_program = learning_program; // TODO - Add more checks to setter.
		}
		else {
			throw "Было переданно неверное значение в параметр learning_program. Ожидается непустая строка.";
		}
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

	// Setters
	// /////// /////// ///////
	// Getters / Adders / Print

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

		// TODO: Test average rate counter
		total_rates += rate;
		average_rate = total_rates / rates_count;
		

	}


	vector<int> GetRates() const {
		vector<int> temp;
		for (int i = 0; i < rates_count; i++)
		{
			temp.push_back(rates[i]);
		}
		return temp;
	}


	static int GetStudentsCount() {
		return students_count;
	}


	Date GetDateJoin() const {
		return date_join;
	}


	Date GetDateLeave() const {
		return date_leave;
	}


	int GetRateByIndex(unsigned int index) {
		if (index >= rates_count) throw "Incorrect index!\n";
		return rates[index];
	}
	

	int GetStudentAverateRate() const {
		return average_rate;
	}
	

	Student* GetLeader() const {
		return leader;
	}
	

	bool GetIsMember() const {
		return is_member;
	}


	string GetStudentName() const {
		return student_name;
	}
	

	string GetLearningProgram() const {
		return learning_program;
	}
	

	/// <summary>
	/// Getter for student_balance variable.
	/// </summary>
	/// <returns>Copy of student_balance variable.</returns>
	unsigned int GetStudentBalance() const {
		return student_balance;
	}


	/*
	void AddBalanceEntry(int balance_entry) {
		// if (balance_entry < 1 || rate > balance_entry) throw "Incorrect value (1-12 expected).";
		if (balance_entry_count == 0) {
			balance_entry = new int[1];
			balance[0] = balance_entry;
		}
		else {
			int* temp = new int[balance_entry_count + 1];
			for (int i = 0; i < balance_entry_count; i++)
				temp[i] = balance[i];
			temp[balance_entry_count] = rate;
			delete[] balance;
			balance = temp;
		}
		balance_entry_count++;
	}

	vector<int> GetBalance() const {
		vector<int> temp;
		for (int i = 0; i < balance_entry_count; i++)
		{
			temp.push_back(balance[i]);
		}
		return temp;
	}

	int GetBalanceEntryByIndex(unsigned int index) {
		if (index >= balance_entry_count) throw "Incorrect index!\n";
		return balance[index];
	}
	*/
	

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
		if (!(leader == nullptr)) cout << "Student's group leader: " << leader->GetStudentName() << "\n";
		else cout << "Student's group leader: none" << "\n";
		cout << "}" << "\n";
		cout << noboolalpha; // Printing 1 / 0
	}
};
int Student::students_count = 0;

ostream& operator << (ostream& os, const Student& student);
istream& operator >> (istream& is, Student& student);

ostream& operator << (ostream& os, const Student& student)
{
	student.PrintStudent();
	return os;
}

istream& operator >> (istream& is, Student& student)
{
	bool is_member = true;
	string student_name;
	string learning_program;
	unsigned int student_balance = 0;
	unsigned int cost_per_month = 0;
	cout << "Enter is_member: ";
	cin >> is_member;
	cout << "\n" << "Enter student name: ";
	cin >> student_name;
	cout << "\n" << "Enter learning program: ";
	cin >> learning_program;
	cout << "\n" << "Enter student balance: ";
	cin >> student_balance;
	cout << "\n" << "Enter student cost_per_month: ";
	cin >> cost_per_month;
	student.SetIsMember(is_member);
	student.SetStudentName(student_name);
	student.SetLearningProgram(learning_program);
	student.SetStudentBalance(student_balance);
	student.SetCostPerMonth(cost_per_month);
	return is;
}


int main()
{
	setlocale(0, "");
	Date today;
	today.PrintDate();
	today.SetDate(21, 10, 2024);
	today.PrintDate();
	
	/*
	cout << "\n" << today << "\n";
	cin >> today;
	cout << today;

	cout << "\n";
	*/
	

	Date today1;
	Date today2;

	today1.SetDate(11, 4, 2024);
	today2.SetDate(10, 4, 2024);

	int result = today1 - today2;
	cout << "\n\n";
	cout << result;
	cout << "\n\n";

	cout << today1;

	Student test;
	Student test2;
	test2 = test;
	// Student testleader;
	// testleader.SetStudentName("Vlad");
	// Student* ptrleader = &testleader;
	// test.SetLeader(ptrleader);
	// test.PrintStudent();
	
	test.AddRate(11);
	int res = test.GetStudentAverateRate();
	cout << "\n" << res << "\n";

	test2.AddRate(12);
	int res2 = test.GetStudentAverateRate();
	cout << res2 << "\n";

	if (test > test2) {
		cout << "test > test2";
	}
	/*
	else {
		cout << "test < test2";
	}
	*/
	if (test < test2) {
		cout << "test < test2";
	}

	/*
	Student copy = test;
	copy.PrintStudent();
	*/
	
	/*
	Student* test_ptr = &test;
	test.SetStudentName("Oleg olegivich");
	test.SetLeader(test_ptr);
	test.PrintStudent();
	*/
	

	Microwave test3;
	test3.SetHasPower(true);
	test3.PrintMicrowave();
	cout << test3;

	Microwave test4;

	string result5 = (string)test4;
	cout << result5;
	/*
	cout << "\n" << test4 << "\n";
	cin >> test4;
	cout << "\n" << test4 << "\n";
	*/
	

	/*
	test2.SetHasPower(true);
	test2.SetTimer(10);
	test2.SetItems("Tasty meal");
	test2.SetButtonStart(true);
	*/
}