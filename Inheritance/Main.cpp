#include <iostream>    // ��� �����-������ � �������
#include <iomanip>     // ��� �������������� ������
#include <string>	   // ��� ������ �� ��������
#include <memory>	   // ��� ���������� (unique_ptr)
#include <vector>      // ��� ������������� �������

using namespace std; // ������������� ������������ ������������ ����

// ������� ����� ��������
class Animal
{
// ���������� ���� �������� ������ ������ ������ � ������� �����������
protected:
	string name;    // ���
	string species; // ��� ���������
	int age;		// �������
	string habitat; //����� ��������

public:
	// ����������� �������� ������ � ��������� ��������
	Animal(const string& n, const string& sp, int a, const string& h) :name(n), species(sp), age(a), habitat(h) 
	{
		if (age < 0)
		{
			throw invalid_argument("������� �� ����� ���� �������������");
		}
	}
	// ����������� ���������� 
	// ��������� ��������� ������� ������� ����������� ������� ����� ��������� �� ������� ����� 
	virtual ~Animal() = default;

	// ����������� ����� ��� ������� ����������� ���������� �� �������
	// virtual ��������� �������������� ���� ����� � ����������� �������
	// const ��������, ��� ����� �� �������� ��������� �������
	// ����� ������ ���������� � ��������
	virtual void display() const
	{
		cout << "-------------------------------\n";
		cout << "���: " << name << "\n";
		cout << "���: " << species << "\n";
		cout << "�������: " << age << "\n";
		cout << "����� ��������: " << habitat << "\n";
	}

	// ����������� ����� ��� �������� ������ ����������
	virtual void shortDisplay() const 
	{
		cout << left << setw(15) << name
			<< setw(20) << species
			<< setw(6) << age
			<< setw(15) << getType() << "\n";
	}

	// ����������� ����� ��� ��������� ���� ��������� 
	// ����� ������������� � ����������� ������� ��� �������� ����
	virtual string getType() const
	{
		return "��������"; // ���������� ����� ��� "��������" ��� �������� ������
	}

	// ������ ��� ����� ��������
	// const ��������, ��� ����� �� �������� ��������� �������
	const string& getHabitat() const
	{
		return habitat;
	}
};

// ����� ������������� (����������� �� Animal)
class Mammals :public Animal
{
	string color; // ���� ������
	bool predator; // ����, �������� �� �������� ��������

public:
	// ����������� � ������� ������������� ������������ Animal
	Mammals(const string& n, const string& sp, int a, const string& h, const string& color, bool predator)
		: Animal(n, sp, a, h), color(color), predator(predator) {}

	// ��������������� ������ display() �� �������� ������
	// override ���������, ��� ��� ��������������� ������������ ������
	void display() const override
	{
		Animal::display(); // ����� �������� ������
		cout << "���� ������: " << color << "\n";
		cout << "������? " << (predator ? "��" : "���") << endl;
	}

	// ��������������� ������ getType()
	string getType() const override
	{
		return "�������������";
	}
};

// ����� ����� (����������� �� Animal)
class Bird:public Animal
{
	double wingspan; // ������ ������� � ������
	bool fly;	// ����������� ������

public:
	// ����������� � ������� ������������� ������������ Animal � ��������� �� ������ �������
	Bird(const string& n, const string& sp, int a, const string& h, double span, bool fly)
		: Animal(n, sp, a, h), wingspan(span), fly(fly) 
	{
		if (wingspan <= 0)
		{
			throw invalid_argument("������ ������� ������ ���� �������������");
		}
	}

	// ��������������� ������ display()
	// ����� ���������� � �����
	void display() const override
	{
		Animal::display();
		cout << "������ �������: " << wingspan << " �\n";
		cout << "����� ������? " << (fly ? "��" : "���");
	}

	// ��������������� ������ getType()
	string getType() const override
	{
		return "�����"; // ���������� ���������� ���
	}
};

// ������� ����� ���������
class Employee
{
protected:
	string name, position; // ��� � ���������
	int age; // �������

public:
	// �����������
	Employee(const string& n, int a, const string& pos) : name(n), age(a), position(pos) {}

	// ����������� ���������� 
	// ��������� ��������� ������� ������� ����������� ������� ����� ��������� �� ������� ����� 
	virtual ~Employee() = default;

	// ����������� ����� ����� ������ ���������� � ����������
	virtual void display() const
	{
		cout << "-------------------------------\n";
		cout << "���: " << name << "\n";
		cout << "�������: " << age << "\n";
		cout << "���������: " << position << "\n";
	}
	// ����������� ����� �������� ������ ����������
	virtual void shortDisplay() const
	{
		// ������������ ������ �� ������ ����
		cout << left << setw(15) << name // ������������� ������ ���� � 15 �������� ��� �����
			<< setw(6) << age // ������������� ������ ���� � 6 �������� ��� ��������
			<< setw(20) << position // ������������� ������ ���� � 20 �������� ��� ���������
			<< setw(15) << getType() << "\n"; // ������������� ������ ���� � 15 �������� ��� ����
	}

	// ����������� ����� ��������� ���� ����������
	virtual string getType() const
	{
		return "����������";
	}
};

// ����� ��������� (����������� �� Employee)
class Veterinarian :public Employee
{
	string specialization; // �������������
	bool workExperience; // ���� ������ ����� 5 ���

public:
	// ����������� � ��������� �������������
	Veterinarian(const string& n, int a, const string& pos, const string& spec, bool work)
		: Employee(n, a, pos), specialization(spec), workExperience(work)
	{
		if (spec.empty())
		{
			throw invalid_argument("������������� �� ����� ���� ������!");
		}
	}

	// ����� ���������� � ����������
	void display() const override
	{
		Employee::display();
		cout << "�������������: " << specialization << "\n";
		cout << "���� ������ ����� 5 ���? " << (workExperience ? "��" : "���");
	}

	// ���������� ��� ����������
	string getType() const override
	{
		return "���������";
	}
};

// ����� ���������� (����������� �� Employee)
class Zookeeper :public Employee
{
	string section;  // ������������ �������
	int yearWork;  // ���� ������ � �����

public:
	// �����������
	Zookeeper(const string& n, int a, const string& pos, const string& section, int exp) : Employee(n, a, pos), section(section), yearWork(exp)
	{
		if (section.empty())
		{
			throw invalid_argument("������� �� ����� ���� ������");
		}
		if (exp < 0)
		{
			throw invalid_argument("���� ������ �� ����� ���� �������������");
		}
	}

	// ��������������� ������ ������ ����������
	void display() const override
	{
		Employee::display();
		cout << "������������ �������: " << section << "\n";
		cout << "���� ������: " << yearWork << " ���\n";
	}

	// ���������� ��� ����������
	string getType() const override
	{
		return "����������";
	}
};

// �������� ����� �������
// ��������� ���������� �������� � �����������
class Zoo
{
	// ������ ����� ���������� (unique_ptr) �� ������� ����� Animal � Employee
	// unique_ptr �����������, ��� ������ ����� ������������� �����������, ����� ������ ������ �� ������� ���������
	vector<unique_ptr<Animal>> animals; // ��������� ��������
	vector<unique_ptr<Employee>> employees; // ��������� �����������
	string name; // �������� ��������

public:
	// ����������� �������� � �������������� ��������
	Zoo(const string& n) :name(n) {}

	// ���������� ���������
	// ����������� ������� animal � ��������� animals 
	// �������� �������� unique_ptr
	void addAnimal(unique_ptr<Animal> animal)
	{
		// move ����������� animal, ��� ��������� push_back ������� ����������� ����������� ������ �����������
		animals.push_back(move(animal)); 
	}

	// ���������� ����������
	// �������� �������� unique_ptr
	void addEmployee(unique_ptr<Employee> employee)
	{
		employees.push_back(move(employee));
	}

	// ����� ���� ��������
	void showAllAnimals() const
	{		
		cout << "\n=== �������� �������� \"" << name << "\"===\n";
		if (animals.empty()) // ��������, ���� ������ �������� ����
		{
			cout << "� �������� ��� ��������\n";
			return; // ����� �� ������
		}

		// ��������� �������
		// ������������ �� ������ ����
		// ������������� ������ ���� � 15 �������� ��� ����� � �.�.
		cout << left << setw(15) << "���" << setw(17) << "���"
			<< setw(17) << "�������" << setw(15) << "���" << endl;

		// ������� ���� �������� � ����� ������� ���������� � ������ �� ���
		for (const auto& animal : animals) 
		{
			if (animal) 
			{
				animal->shortDisplay();
			}
		}
	}

	// ����� ���� �����������
	void showAllEmployees() const 
	{
		cout << "\n=== ���������� �������� \"" << name << "\"===\n";
		if (employees.empty())
		{
			cout << "� �������� ��� �����������\n";
			return;
		}

		// ��������� �������
		// ������������ �� ������ ����
		// ������������� ������ ���� � 15 �������� ��� ����� � �.�.
		cout << left << setw(15) << "���" << setw(10) << "�������"
			<< setw(20) << "���������" << setw(15) << "���" << endl;

		// ������� ���� ����������� � ����� ������� ���������� � ������ �� ���
		for (const auto& emp : employees) 
		{
			if (emp)
			{
				emp->shortDisplay(); // ����� �������� �����������
			} 
		}
	}

	// ����� �������� �� ����
	void showAnimalsByHabitat(const string& habitat) const 
	{
		bool found = false; // ���� ��� ������������, ������� �� ��������
		cout << "\n�������� � ����� ��������: " << habitat << "\n";

		for (const auto& animal : animals)
		{
			// �������� ��������� �� ����� �������� � ������� ���������
			if (animal && animal->getHabitat() == habitat)
			{
				animal->display(); // ������� ������ ����������
				found = true; // ������������� ����, ���� �������� ������� 
			}
		}
		// ��������, ���� ������ �� �����
		if (!found) 
		{
			cout << "�������� � ������ ����� �������� �� �������.\n";
		}
	}
};

// ������� ������ ������
void clearInput() 
{
	cin.clear(); //����� ������ ������
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ��� �� ����� ������
}

// ����� ����
void showMenu()
{
	cout << "\n====== ���� �������� ======\n"
		<< "1. �������� ���� ��������\n"
		<< "2. �������� ���� �����������\n"
		<< "3. �������� �������� �� ����� ��������\n"
		<< "4. �����\n"
		<< "�����: ";
}

// ������� ������� ���������
int main()
{
	system("chcp 1251>null"); // ��������� �������� �����
	try // ��������� ����������
	{
		Zoo zoo("����� ���");

		// make_unique ������ ���������� ��������� �� ������. 
		// ��� �������� ������ ��� ������� � ���������� ��������� unique_ptr, ������� ��������� ���� �������
		// ���������� ��������
		zoo.addAnimal(make_unique<Mammals>("�����", "���", 5, "�������", "����������", true));
		zoo.addAnimal(make_unique<Bird>("����", "�������", 3, "�������", 0.5, true));
		zoo.addAnimal(make_unique<Mammals>("�����", "����", 4, "�������", "��������� � ���������", true));
		zoo.addAnimal(make_unique<Bird>("������", "������", 7, "�������", 2.0, false));
		zoo.addAnimal(make_unique<Mammals>("����", "�����", 2, "�������", "�������-�����", false));

		// ���������� �����������
		zoo.addEmployee(make_unique<Veterinarian>("���� ������", 35, "������� ���������", "�������", true));
		zoo.addEmployee(make_unique<Zookeeper>("���� ��������", 28, "����������", "�����", 10)); 

		int choice; // ���������� ��� �������� ������ �� ����
		string input; // ���������� ��� �������� �������� ����� (��������, ��� � ����� ��������)

		while (true) // ����, ������� ����������� ���������� �� ��� ���, ���� �� ������� "�����" (0)
		{
			showMenu(); // ����� ������� ��� ����������� ����
			cin >> choice; // ��������� ����� ������������
			clearInput(); // ������� �����

			try
			{
				switch (choice) // �������� switch ��� ���������� �������� � ����������� �� ������ ������������
				{
				case 1:
					zoo.showAllAnimals(); // ���������� ���� ��������
					break; // ����� �� switch
				case 2:
					zoo.showAllEmployees(); // ���������� ���� �����������
					break; // ����� �� switch
				case 3:
					cout << "������� ����� �������� (��������: �������, �������, �������, �������): "; // ������ ������������ ������ ����� ��������
					getline(cin, input); // ��������� ������ �����
					zoo.showAnimalsByHabitat(input); // ���� �� ���������� ���������
					break; 
				case 4:
					cout << "����� �� ���������...\n";
					exit(0); // ����������� ���������� ���������
					break; 
				default: cout << "������ �����. ����������, �������� �������� �� 1 �� 4\n"; // ��������� �� ������
					break; 
				}
			}
			catch (const exception& e)
			{
				cerr << "������: " << e.what() << endl;
			}
		}
	}
	catch (const exception& e)
	{
		cerr << "������: " << e.what() << endl;
		return 1; // ���������� ��������� � ����� ������
	}
	return 0; // ���������� ���������
}