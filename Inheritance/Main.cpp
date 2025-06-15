#include <iostream>    // Для ввода-вывода в консоль
#include <iomanip>     // Для форматирования вывода
#include <string>	   // Для работы со строками
#include <memory>	   // Для указателей (unique_ptr)
#include <vector>      // Для использования вектора

using namespace std; // Использование стандартного пространства имен

// Базовый класс Животное
class Animal
{
// Защищенные поля доступны только внутри класса и классам наследникам
protected:
	string name;    // Имя
	string species; // Вид животного
	int age;		// Возраст
	string habitat; //Среда обитания

public:
	// Конструктор базового класса с проверкой возраста
	Animal(const string& n, const string& sp, int a, const string& h) :name(n), species(sp), age(a), habitat(h) 
	{
		if (age < 0)
		{
			throw invalid_argument("Возраст не может быть отрицательным");
		}
	}
	// Виртуальный диструктор 
	// Позволяет корректно удалять объекты производных классов через указатель на базовый класс 
	virtual ~Animal() = default;

	// Виртуальный метод для полного отображения информации об артисте
	// virtual позволяет переопределять этот метод в производных классах
	// const означает, что метод не изменяет состояние объекта
	// Вывод полной информации о животном
	virtual void display() const
	{
		cout << "-------------------------------\n";
		cout << "Имя: " << name << "\n";
		cout << "Вид: " << species << "\n";
		cout << "Возраст: " << age << "\n";
		cout << "Среда обитания: " << habitat << "\n";
	}

	// Виртуальный метод для краткого вывода информации
	virtual void shortDisplay() const 
	{
		cout << left << setw(15) << name
			<< setw(20) << species
			<< setw(6) << age
			<< setw(15) << getType() << "\n";
	}

	// Виртуальный метод для получения типа животного 
	// Будет переопределен в производных классах для возврата типа
	virtual string getType() const
	{
		return "Животное"; // Возвращает общий тип "Животное" для базового класса
	}

	// Геттер для среды обитания
	// const означает, что метод не изменяет состояние объекта
	const string& getHabitat() const
	{
		return habitat;
	}
};

// Класс Млекопитающие (наследуется от Animal)
class Mammals :public Animal
{
	string color; // Цвет шерсти
	bool predator; // Флаг, является ли животное хищником

public:
	// Конструктор с вызовом родительского конструктора Animal
	Mammals(const string& n, const string& sp, int a, const string& h, const string& color, bool predator)
		: Animal(n, sp, a, h), color(color), predator(predator) {}

	// Переопределение метода display() из базового класса
	// override указывает, что это переопределение виртуального метода
	void display() const override
	{
		Animal::display(); // Вызов базового класса
		cout << "Цвет шерсти: " << color << "\n";
		cout << "Хищник? " << (predator ? "Да" : "Нет") << endl;
	}

	// Переопределение метода getType()
	string getType() const override
	{
		return "Млекопитающие";
	}
};

// Класс Птицы (наследуется от Animal)
class Bird:public Animal
{
	double wingspan; // Размах крыльев в метрах
	bool fly;	// Способность летать

public:
	// Конструктор с вызовом родительского конструктора Animal с проверкой на размах крыльев
	Bird(const string& n, const string& sp, int a, const string& h, double span, bool fly)
		: Animal(n, sp, a, h), wingspan(span), fly(fly) 
	{
		if (wingspan <= 0)
		{
			throw invalid_argument("Размах крыльев должен быть положительным");
		}
	}

	// Переопределение метода display()
	// Вывод информации о птице
	void display() const override
	{
		Animal::display();
		cout << "Размах крыльев: " << wingspan << " м\n";
		cout << "Умеет летать? " << (fly ? "Да" : "Нет");
	}

	// Переопределение метода getType()
	string getType() const override
	{
		return "Птицы"; // Возвращаем конкретный тип
	}
};

// Базовый класс Сотрудник
class Employee
{
protected:
	string name, position; // имя и должность
	int age; // Возраст

public:
	// Конструктор
	Employee(const string& n, int a, const string& pos) : name(n), age(a), position(pos) {}

	// Виртуальный диструктор 
	// Позволяет корректно удалять объекты производных классов через указатель на базовый класс 
	virtual ~Employee() = default;

	// Виртуальный метод вывод полной информации о сотруднике
	virtual void display() const
	{
		cout << "-------------------------------\n";
		cout << "Имя: " << name << "\n";
		cout << "Возраст: " << age << "\n";
		cout << "Должность: " << position << "\n";
	}
	// Виртуальный метод краткого вывода информации
	virtual void shortDisplay() const
	{
		// Выравнивание текста по левому краю
		cout << left << setw(15) << name // Устанавливает ширину поля в 15 символов для имени
			<< setw(6) << age // Устанавливает ширину поля в 6 символов для возраста
			<< setw(20) << position // Устанавливает ширину поля в 20 символов для должности
			<< setw(15) << getType() << "\n"; // Устанавливает ширину поля в 15 символов для типа
	}

	// Виртуальный метод получения типа сотрудника
	virtual string getType() const
	{
		return "Сотрудники";
	}
};

// Класс Ветеринар (наследуется от Employee)
class Veterinarian :public Employee
{
	string specialization; // Специализация
	bool workExperience; // Опыт работы более 5 лет

public:
	// Конструктор с проверкой специализации
	Veterinarian(const string& n, int a, const string& pos, const string& spec, bool work)
		: Employee(n, a, pos), specialization(spec), workExperience(work)
	{
		if (spec.empty())
		{
			throw invalid_argument("Специализация не может быть пустой!");
		}
	}

	// Вывод информации о ветеринаре
	void display() const override
	{
		Employee::display();
		cout << "Специализация: " << specialization << "\n";
		cout << "Опыт работы более 5 лет? " << (workExperience ? "Да" : "Нет");
	}

	// Возвращает тип сотрудника
	string getType() const override
	{
		return "Ветеринар";
	}
};

// Класс Смотритель (наследуется от Employee)
class Zookeeper :public Employee
{
	string section;  // Закрепленный участок
	int yearWork;  // Опыт работы в годах

public:
	// Конструктор
	Zookeeper(const string& n, int a, const string& pos, const string& section, int exp) : Employee(n, a, pos), section(section), yearWork(exp)
	{
		if (section.empty())
		{
			throw invalid_argument("Участок не может быть пустым");
		}
		if (exp < 0)
		{
			throw invalid_argument("Опыт работы не может быть отрицательным");
		}
	}

	// Переопределение метода вывода информации
	void display() const override
	{
		Employee::display();
		cout << "Закрепленный участок: " << section << "\n";
		cout << "Опыт работы: " << yearWork << " лет\n";
	}

	// Возвращает тип сотрудника
	string getType() const override
	{
		return "Смотритель";
	}
};

// Основной класс Зоопарк
// Управляет коллекцией животных и сотрудников
class Zoo
{
	// Вектор умных указателей (unique_ptr) на базовый класс Animal и Employee
	// unique_ptr гарантирует, что память будет автоматически освобождена, когда объект выйдет из области видимости
	vector<unique_ptr<Animal>> animals; // Коллекция животных
	vector<unique_ptr<Employee>> employees; // Коллекция сотрудников
	string name; // Название зоопарка

public:
	// Конструктор Зоопарка с инициализацией названия
	Zoo(const string& n) :name(n) {}

	// Добавление животного
	// Перемещение объекта animal в контейнер animals 
	// Передача владения unique_ptr
	void addAnimal(unique_ptr<Animal> animal)
	{
		// move преобразует animal, что позволяет push_back вызвать конструктор перемещения вместо копирования
		animals.push_back(move(animal)); 
	}

	// Добавление сотрудника
	// Передача владения unique_ptr
	void addEmployee(unique_ptr<Employee> employee)
	{
		employees.push_back(move(employee));
	}

	// Вывод всех животных
	void showAllAnimals() const
	{		
		cout << "\n=== Животные зоопарка \"" << name << "\"===\n";
		if (animals.empty()) // Проверка, если список животных пуст
		{
			cout << "В зоопарке нет животных\n";
			return; // Выход из метода
		}

		// Заголовок таблицы
		// Выравнивание по левому краю
		// Устанавливает ширину поля в 15 символов для имени и т.д.
		cout << left << setw(15) << "Имя" << setw(17) << "Вид"
			<< setw(17) << "Возраст" << setw(15) << "Тип" << endl;

		// Перебор всех животных и вывод краткой информации о каждом из них
		for (const auto& animal : animals) 
		{
			if (animal) 
			{
				animal->shortDisplay();
			}
		}
	}

	// Вывод всех сотрудников
	void showAllEmployees() const 
	{
		cout << "\n=== Сотрудники зоопарка \"" << name << "\"===\n";
		if (employees.empty())
		{
			cout << "В зоопарке нет сотрудников\n";
			return;
		}

		// Заголовок таблицы
		// Выравнивание по левому краю
		// Устанавливает ширину поля в 15 символов для имени и т.д.
		cout << left << setw(15) << "Имя" << setw(10) << "Возраст"
			<< setw(20) << "Должность" << setw(15) << "Тип" << endl;

		// Перебор всех сотрудников и вывод краткой информации о каждом из них
		for (const auto& emp : employees) 
		{
			if (emp)
			{
				emp->shortDisplay(); // Вызов краткого отображения
			} 
		}
	}

	// Вывод животных по типу
	void showAnimalsByHabitat(const string& habitat) const 
	{
		bool found = false; // Флаг для отслеживания, найдены ли животные
		cout << "\nЖивотные в среде обитания: " << habitat << "\n";

		for (const auto& animal : animals)
		{
			// Проверка совпадает ли среда обитания с искомым значением
			if (animal && animal->getHabitat() == habitat)
			{
				animal->display(); // Выводим полную информацию
				found = true; // Устанавливаем флаг, если животное найдено 
			}
		}
		// Проверка, если никого не нашли
		if (!found) 
		{
			cout << "Животных в данной среде обитания не найдено.\n";
		}
	}
};

// Очситка буфера обмена
void clearInput() 
{
	cin.clear(); //Сброс флагов ошибки
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем все до конца строки
}

// Вывод меню
void showMenu()
{
	cout << "\n====== МЕНЮ ЗООПАРКА ======\n"
		<< "1. Показать всех животных\n"
		<< "2. Показать всех сотрудников\n"
		<< "3. Показать животных по среде обитания\n"
		<< "4. Выход\n"
		<< "Выбор: ";
}

// Главная функция программы
int main()
{
	system("chcp 1251>null"); // Установка русского языка
	try // Обработка исключений
	{
		Zoo zoo("Дикий рай");

		// make_unique создаёт уникальный указатель на объект. 
		// Она выделяет память для объекта и возвращает экземпляр unique_ptr, который управляет этой памятью
		// Добавление животных
		zoo.addAnimal(make_unique<Mammals>("Симба", "Лев", 5, "Саванна", "Золотистый", true));
		zoo.addAnimal(make_unique<Bird>("Кеша", "Попугай", 3, "Тропики", 0.5, true));
		zoo.addAnimal(make_unique<Mammals>("Акела", "Тигр", 4, "Джунгли", "Оранжевый с полосками", true));
		zoo.addAnimal(make_unique<Bird>("Стейси", "Страус", 7, "Пустыня", 2.0, false));
		zoo.addAnimal(make_unique<Mammals>("Аяка", "Жираф", 2, "Саванна", "Песочно-жёлтый", false));

		// Добавление сотрудников
		zoo.addEmployee(make_unique<Veterinarian>("Иван Петров", 35, "Главный ветеринар", "Хищники", true));
		zoo.addEmployee(make_unique<Zookeeper>("Анна Сидорова", 28, "Смотритель", "Птицы", 10)); 

		int choice; // Переменная для хранения выбора из меню
		string input; // Переменная для хранения строкого ввода (например, имя и среда обитания)

		while (true) // Цикл, который выполняется бесконечно до тех пор, пока не выбрано "Выход" (0)
		{
			showMenu(); // Вызов функции для отображения меню
			cin >> choice; // Считываем выбор пользователя
			clearInput(); // Очищаем буфер

			try
			{
				switch (choice) // Оператор switch для выполнения действий в зависимости от выбора пользователя
				{
				case 1:
					zoo.showAllAnimals(); // Показываем всех животных
					break; // Выход из switch
				case 2:
					zoo.showAllEmployees(); // Показываем всех сотрудников
					break; // Выход из switch
				case 3:
					cout << "Введите среду обитания (например: Саванна, Тропики, Джунгли, Пустыня): "; // Просим пользователя ввести среду обитания
					getline(cin, input); // Считываем строку ввода
					zoo.showAnimalsByHabitat(input); // Ищем по выбранному параметру
					break; 
				case 4:
					cout << "Выход из программы...\n";
					exit(0); // Немедленное завершение программы
					break; 
				default: cout << "Ошибка ввода. Пожалуйста, выберите действие от 1 до 4\n"; // Сообщение об ошибке
					break; 
				}
			}
			catch (const exception& e)
			{
				cerr << "Ошибка: " << e.what() << endl;
			}
		}
	}
	catch (const exception& e)
	{
		cerr << "Ошибка: " << e.what() << endl;
		return 1; // Завершение программы с кодом ошибки
	}
	return 0; // Завершение программы
}