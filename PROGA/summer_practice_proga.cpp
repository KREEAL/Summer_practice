
// summer_practice_proga.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream NamesIn; ifstream PhonesIn; ifstream EmailsIn; ifstream GlobalIn; ifstream LoginsIn; ifstream PasswordsIn; ifstream BufferIn;
ofstream NamesOut; ofstream PhonesOut; ofstream EmailsOut; ofstream GlobalOut; ofstream LoginsOut; ofstream PasswordsOut; ofstream BufferOut;

string longtostring(long x)
{
	string str="";
	str = to_string(x);
	return str;
}

long hash37(string str) 
{
	long hash = 2139062143;
	for(int i=0;i<str.length();i++)
	{
		hash = 37 * hash + (long)str[i];
	}
	return hash;
}

//приведение телефона к требуемому виду
void phoneFormat(string& s)
{
	
	//+7-(222)-222-22-22
	
		s = "+7-(" + s;
		s.insert(7, ")-");
		s.insert(12, "-");
		s.insert(15, "-");
	
}

//поиск номера строки с указанным именем. При ненаходе получаем -1
int findByName(string fio){
	NamesIn.open("Names.txt");
	int k = 1;
	string str;
	while(!NamesIn.eof())
	{
		getline(NamesIn,str);
		
		if(fio==str)
		{
			NamesIn.close();
			return k;
		}
		k++;
	}
	NamesIn.close();
	return -1;
}

//поиск номера строки с указанным логином. При ненаходе получаем -1
int findByLogin(string login)
{
	LoginsIn.open("Logins.txt");
	int k = 1;
	string str;
	while(!LoginsIn.eof())
	{
		getline(LoginsIn, str);
		if (login == str)
		{
			LoginsIn.close();
			return k;
		}
		k++;
	}
	LoginsIn.close();
	return -1;
}

//поиск номера строки с указанным телефоном. При ненаходе получаем -1
int findByNumber(string number)
{
	phoneFormat(number);
	PhonesIn.open("Phones.txt");
	int k = 1;
	string str;
	while(!PhonesIn.eof())
	{
		getline(PhonesIn, str);
		if(number==str)
		{
			PhonesIn.close();
			return k;
		}
		k++;
	}
	PhonesIn.close();
	return -1;
}

//поиск номера строки с указанным e-mal. При ненаходе получаем -1
int findByEmail(string mail)
{
	EmailsIn.open("Emails.txt");
	int k = 1;
	string str;

	while(!EmailsIn.eof())
	{
		
		getline(EmailsIn, str);
		if(mail==str)
		{
			EmailsIn.close();
			return k;
		}
		k++;
	}
	EmailsIn.close();
	return -1;
}
//вывод данных с найденной строки в Global
void coutFromChosenNumberString(int n)
{
	GlobalIn.open("Global.txt");
	int k = 1; string str;
	while(!GlobalIn.eof())
	{
		getline(GlobalIn,str);
		if (k == n) {
			GlobalIn.close();
			cout << endl <<"Найден пользователь: " +str << endl;
			return;
		}
		k++;
	}
	
}

//проверка корректности
int correctionCheck(string str,regex fio,regex phone)
{
	if(regex_match(str,fio))
	{
		return 1;
	}
	if(regex_match(str,phone))
	{
		return 2;
	}
	if(findByLogin(str)!=-1)
	{
		return 3;
	}
	return 0;
}

//получить пароль по номеру строки(пользователя)
string findPasswordByNumber(int n)
{
	PasswordsIn.open("Passwords.txt");
	int k = 1; string str;
	while (!PasswordsIn.eof())
	{
		getline(PasswordsIn, str);
		if (k == n)
		{
			PasswordsIn.close();
			return str;
		}
		k++;
	}

	PasswordsIn.close();
}
string findLoginByNumber(int n)
{
	LoginsIn.open("Logins.txt");
	int k = 1; string str;
	while (!LoginsIn.eof())
	{
		getline(LoginsIn, str);
		if (k == n)
		{
			LoginsIn.close();
			return str;
		}
		k++;
	}

	LoginsIn.close();
	//я в любом случае найду пароль на указанной строке
}
string findNameByNumber(int n)
{
	NamesIn.open("Names.txt");
	int k = 1; string str;
	while (!NamesIn.eof())
	{
		getline(NamesIn, str);
		if (k == n)
		{
			NamesIn.close();
			return str;
		}
		k++;
	}

	NamesIn.close();
}
string findPhoneByNumber(int n)
{
	PhonesIn.open("Phones.txt");
	int k = 1; string str;
	while (!PhonesIn.eof())
	{
		getline(PhonesIn, str);
		if (k == n)
		{
			PhonesIn.close();
			return str;
		}
		k++;
	}

	PhonesIn.close();
}
string findMailByNumber(int n)
{
	EmailsIn.open("Emails.txt");
	int k = 1; string str;
	while (!EmailsIn.eof())
	{
		getline(EmailsIn, str);
		if (k == n)
		{
			EmailsIn.close();
			return str;
		}
		k++;
	}

	EmailsIn.close();
}

void deleteUser(int n)
{
	
	cin.ignore();
	//Имена
	NamesIn.open("Names.txt"); BufferOut.open("Buffer.txt");
	string str; int k = 1;
	while (!NamesIn.eof())
	{
		getline(NamesIn, str);
		if (k != n && str.size() > 1)
		{	
			BufferOut << str << endl;
		}
		k++;
	}
	NamesIn.close(); BufferOut.close(); NamesOut.open("Names.txt"); BufferIn.open("Buffer.txt");
	str = "";
	while(!BufferIn.eof())
	{
		getline(BufferIn, str);
		if (str.size() > 1) {
			NamesOut << str << endl;
		}
	}
	NamesOut.close(); BufferIn.close();
	
	//Почты
	EmailsIn.open("Emails.txt"); BufferOut.open("Buffer.txt");
	k = 1;
	while (!EmailsIn.eof())
	{
		getline(EmailsIn, str);
		if (k != n&&str.size()>1)
			BufferOut << str << endl;
		k++;
	}
	EmailsIn.close(); BufferOut.close(); EmailsOut.open("Emails.txt"); BufferIn.open("Buffer.txt");
	while (!BufferIn.eof())
	{
		getline(BufferIn, str);
	if (str.size() > 1)
		EmailsOut << str << endl;
	}
	EmailsOut.close(); BufferIn.close();

	//Телефоны
	PhonesIn.open("Phones.txt"); BufferOut.open("Buffer.txt");
	k = 1;
	while (!PhonesIn.eof())
	{
		getline(PhonesIn, str);
		if (k != n&&str.size()>1)
			BufferOut << str << endl;
		k++;
	}
	PhonesIn.close(); BufferOut.close(); PhonesOut.open("Phones.txt"); BufferIn.open("Buffer.txt");
	while (!BufferIn.eof())
	{
		getline(BufferIn, str);
		if (str.size() > 1)
		PhonesOut << str << endl;
	}
	PhonesOut.close(); BufferIn.close();

	//Логины
	LoginsIn.open("Logins.txt"); BufferOut.open("Buffer.txt");
	k = 1;
	while (!LoginsIn.eof())
	{
		getline(LoginsIn, str);
		if (k != n&&str.size()>1)
			BufferOut << str << endl;
		k++;
	}
	LoginsIn.close(); BufferOut.close(); LoginsOut.open("Logins.txt"); BufferIn.open("Buffer.txt");
	while (!BufferIn.eof())
	{
		getline(BufferIn, str);
			if (str.size() > 1)
		LoginsOut << str << endl;
	}
	LoginsOut.close(); BufferIn.close();

	//Пароли
	PasswordsIn.open("Passwords.txt"); BufferOut.open("Buffer.txt");
	k = 1;
	while (!PasswordsIn.eof())
	{
		getline(PasswordsIn, str);
		if (k != n&&str.size()>1)
			BufferOut << str << endl;
		k++;
	}
	PasswordsIn.close(); BufferOut.close(); PasswordsOut.open("Passwords.txt"); BufferIn.open("Buffer.txt");
	while (!BufferIn.eof())
	{
		getline(BufferIn, str);
				if (str.size() > 1)
		PasswordsOut << str << endl;
	}
	PasswordsOut.close(); BufferIn.close();

	//Глобально
	GlobalIn.open("Global.txt"); BufferOut.open("Buffer.txt");
	k = 1;
	while (!GlobalIn.eof())
	{
		getline(GlobalIn, str);
		if (k != n&&str.size()>1)
			BufferOut << str << endl;
		k++;
	}
	GlobalIn.close(); BufferOut.close(); GlobalOut.open("Global.txt"); BufferIn.open("Buffer.txt");
	while (!BufferIn.eof())
	{
		getline(BufferIn, str);
					if (str.size() > 1)
		GlobalOut << str << endl;
	}
	GlobalOut.close(); BufferIn.close();

	cout << endl << "Пользователь успешно удален" << endl;
}
//собирает данные из файликов, перезаписывает конкретного юзера в global
void changeUser(int n)
{
	string newUser; int counter = 1;
	newUser = findNameByNumber(n) + " " + findPhoneByNumber(n) + " " + findMailByNumber(n) + " " + findLoginByNumber(n);
	GlobalIn.open("Global.txt"); BufferOut.open("Buffer.txt");
	string s;
	while(!GlobalIn.eof())
	{
		getline(GlobalIn, s);
		if (counter != n) {
			if (s.size() > 1)
			{
				BufferOut << s << endl;
			}
		}
		else
		{
			BufferOut << newUser << endl;
		}
		counter++; 
	}
	GlobalIn.close(); BufferOut.close(); GlobalOut.open("Global.txt"); BufferIn.open("Buffer.txt");
	while(!BufferIn.eof())
	{
		getline(BufferIn, s);
		if(s.size()>1)
		{
			GlobalOut << s << endl;
		}
	}
	GlobalOut.close(); BufferIn.close();

}
int main()
{
	setlocale(LC_ALL,"RU");
	//const regex mailRegex(R"(\w+@\w+\.(?:com|ru|in|info))");//там, где мэил, то допустимо MAIL
	const regex mailRegex(R"([\w|-]+\w+@\w+\.(?:com|ru|in|info))");
	const regex fioRegex(R"([A-Z][a-z]+\s[A-Z][a-z]+\s[A-Z][a-z]+)");
	const regex telephoneRegex(R"(\d{10})");
	const regex passwordRegex(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$)");
	//"^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$"
	int k = -1;
	
	

	while(k!=0)
	{
		cout << endl << "Выберите необходимую опцию: " << endl << "1.Посмотреть список все пользователей" << endl << "2.Добавить пользователя" << endl << "3.Удалить пользователя" << endl <<
			"4.Изменить пользователя"<<endl<<"5.Отправить сообщение"<<endl<<"6.Сортировка по выбранному полю"<<endl<<"0.Выход"<<endl;

		cin >> k;
		
		//просмотреть пользователей
		if (k == 1) {
			GlobalIn.open("Global.txt");
			
			string str;
			while (!GlobalIn.eof())
			{
				getline(GlobalIn, str);
				cout <<str << endl;
				
			}
			GlobalIn.close();
		}

		//добавить пользователя
		if(k==2)
		{
			string f; string i; string o; int counter = 0;
			do {
				if (counter > 0)cout << endl << "Некорректный ввод или такой пользователь уже существует, повторите попытку ";//в первый раз не сработает, но все последующие разы должно
				
				cout << endl << "Введите ФИО ";
				cin >> f; cin >> i; cin >> o; f = f + " " +i+" " +o;
				
				counter++;
			} while (!regex_match(f,fioRegex)||findByName(f)!=-1);


			string phone; int counter1 = 0;
			do {
				if (counter1 > 0)cout << endl << "Некорректный ввод или пользователь с таким номером уже существует, повтрите попытку";

				cout << endl << "Введите номер телефона(без +7 или 8)";
				cin >> phone;
				counter1++;
			} while (!regex_match(phone, telephoneRegex)||findByNumber(phone)!=-1);


			string mail; int counter2 = 0;
			do{
				if (counter2 > 0)cout << endl << "Некорректный ввод или пользователь с такой почтой уже существует, повторите попытку ";//в первый раз не сработает, но все последующие разы должно

				cout << endl << "Введите e-mail ";
				cin >> mail;
				counter2++;
			} while (!regex_match(mail, mailRegex)||findByEmail(mail)!=-1);
			
			cout << endl << "Логин должен содержат, как минимум, 2 символа и не совпадать с номером телефона" << endl;
			string login; int counter3 = 0;
			do {
				if (counter3 > 0)cout << endl << "Некорректный ввод или пользователь с таким логином уже существуеты, повторите попытку ";
				cout << endl << "Введите логин ";
				cin >> login;
				counter3++;
			} while ((login.size() < 2) || (findByLogin(login)!=-1));
			

			string password; int counter4 = 0;
			cout<< endl <<"Пароль должен состоять, как минимум, из 8 символов, содержать одну заглавную,"<< " одну строчную буквы, одну цифру и один специальный символ" << endl;
			do {
				if (counter4 > 0)cout << endl << "Некорректный ввод, повторите попытку ";
				cout << endl << "Введите пароль ";
				cin >> password;
				counter4++;
			} while (!regex_match(password, passwordRegex));

			phoneFormat(phone);
			string globalStr = f + " "+ phone+ " " + mail + " "+login;
			GlobalOut.open("Global.txt", ios::app);
			GlobalOut << globalStr << endl;
			GlobalOut.close();

			NamesOut.open("Names.txt", ios::app);
			NamesOut << f << endl;
			NamesOut.close();


			PhonesOut.open("Phones.txt", ios::app);
			PhonesOut << phone << endl;
			PhonesOut.close();

			EmailsOut.open("Emails.txt", ios::app);
			EmailsOut << mail << endl;
			EmailsOut.close();

			LoginsOut.open("Logins.txt", ios::app);
			LoginsOut << login << endl;
			LoginsOut.close();

			PasswordsOut.open("Passwords.txt", ios::app);
			PasswordsOut << hash37(password) << endl;
			PasswordsOut.close();

			cout << endl << "Пользователь успешно добавлен!" << endl;
		}

		//удалить пользователя
		if(k==3)
		{
			cout << "Для удаления пользователя нужно найти его в системе. Для поиска введите ФИО, номер телефона или логин"<<endl;
			string str; bool isLogin = false; int nomer = -1;
			int count = 0;
			cin.ignore();
			getline(cin, str);
			while(correctionCheck(str, fioRegex, telephoneRegex) == 0)
			{
				cout << endl << "По указанным данным не удалось найти пользователя. Повторите ввод";
				getline(cin, str);
			}
			//cout << "ИЗ ДУВАЙЛА Я ВЫШЕЛ С:" << str;

			//нашлось, все круто, теперь
			if (findByLogin(str)!=-1)
			{
				nomer = findByLogin(str);
				//coutFromChosenNumberString(nomer);
			}
			if(regex_match(str,fioRegex))
			{
				nomer = findByName(str);
				//coutFromChosenNumberString(nomer);
			}
			if(regex_match(str,telephoneRegex))
			{
				nomer = findByNumber(str);
				
				//coutFromChosenNumberString(nomer);
				
			}

			if(nomer==-1)
			{
				cout<<"Пользователь с указанными данными не найден, повторите попытку позже"<<endl;
			}
			else {
				coutFromChosenNumberString(nomer);

				//Пользователя вывыели, теперь нужна проверка на пароль
				cout << "Для подтверждения удаления пользователя введите пароль или otmena для отмены";
				//cin.ignore();
				//getline(cin, str);
				cin >> str;
				if (str == "otmena")
				{
					cout << "Удаление пользователя отменено";
				}
				else
				{
					//string currentPassword = findPasswordByNumber(nomer);
					string currentPassword = findPasswordByNumber(nomer);

					//cout << "ПАРОЛЬ:" << currentPassword;
					cout << "ПАРОЛЬ:" << currentPassword;
					if (longtostring(hash37(str)) != currentPassword)
					{
						cout << "Неверный пароль. Осталось 2 попытки. Введите пароль:" << endl;
						/*cin.ignore();
						*/
						//getline(cin, str1);
						string str1;
						cin >> str1;
						if (longtostring(hash37(str1)) != currentPassword)
						{
							cout << "Неверный пароль. Осталось 1 попытка. Введите пароль:" << endl;
							/*cin.ignore();

							getline(cin, str2);*/
							string str2;
							cin >> str2;
							if (longtostring(hash37(str2)) != currentPassword)
							{
								cout << "Неверный пароль. Повторите попытку удаления позже" << endl;
							}
							else
							{
								deleteUser(nomer);
							}
						}
						else
						{
							deleteUser(nomer);
						}
					}
					else
					{
						deleteUser(nomer);
					}
				}
			}
			//str = "";
		}
		
		//изменить пользователя
		if (k == 4)
		{
			cout << "Вы находитесь в меню изменения данных пользователей. Чтобы изменить данные, нужно найти пользователя" << endl <<
				"Для поиска введите ФИО, номер телефона или логин" << endl;
			int nomer = -1;
			cin.ignore();
			string str; getline(cin, str);
			while (correctionCheck(str, fioRegex, telephoneRegex) == 0)
			{
				cout << endl << "По указанным данным не удалось найти пользователя. Повторите ввод";
				getline(cin, str);
			}
			if (findByLogin(str) != -1)
			{
				nomer = findByLogin(str);
				//coutFromChosenNumberString(nomer);
			}
			if (regex_match(str, fioRegex))
			{
				nomer = findByName(str);
				//coutFromChosenNumberString(nomer);
			}
			if (regex_match(str, telephoneRegex))
			{
				nomer = findByNumber(str);

				//coutFromChosenNumberString(nomer);
			}

			if (nomer == -1)
			{
				cout << "Пользователь с указанными данными не найден, повторите попытку позже" << endl;
			}
			else
			{
				coutFromChosenNumberString(nomer);
				cout << endl << "Для продолжения введите пароль: " << endl;
				string currentPassword = findPasswordByNumber(nomer);
				cout << "ПАРОЛЬ:" << currentPassword;
				int q = 0;
				while (q < 3) {
					cout << "Осталось " << 3 - q << " попытки, введите пароль: " << endl;
					cin >> str;
					if (longtostring(hash37(str)) == currentPassword)q = 11;
					q++;
				}
				//Нашли юзера, ввели пароль, теперь надо изменять!!!
				if (q >= 10) {
					cout << "Выберите поле для изменения:" << endl << "1.ФИО" << endl << "2.E-Mail" << endl << "3.Номер телефона" << endl << "4.Логин" << endl << "5.Пароль" << endl;
					int k = 0; cin >> k;
					while(k<1||k>5)
					{
						cout << endl << "Нет такого пункта, повторите ввод" << endl;
						cin >> k;
					}
					//Изменяем ФИО
					cin.ignore();
					string newGlobal;
					//изменяем имя
					if(k==1)
					{
						//получение нового ФИО
						cout << endl<<"Введите новое ФИО" << endl;
						string newName;
						getline(cin, newName);
						while(!regex_match(newName,fioRegex)||findByName(newName)!=-1)
						{
							cout << endl << "Некорректный ввод или такое ФИО уже существует, повторите попытку" << endl;
							getline(cin, newName);
						}

						//записываем в буфер текущие ФИО. На строке nomer записываем новое имя
						string newS; int schetchick = 1;
						NamesIn.open("Names.txt"); BufferOut.open("Buffer.txt");
						while(!NamesIn.eof())
						{
							//проверка на строку nomer
							if(schetchick!=nomer)
							{
								
								getline(NamesIn, newS);
								if (newS.size() > 1)
									BufferOut << newS << endl;
							}
							else 
							{

								getline(NamesIn, newS);
								
								if (newS.size() > 1) {
									newS = newName;
									BufferOut << newS << endl;
								}
							}
							schetchick++;
						}
						//переоткрыли файлы
						NamesIn.close(); BufferOut.close(); NamesOut.open("Names.txt"); BufferIn.open("Buffer.txt");
						newS = "";
						//просто запись из буфера в Names, с уже измененным именем
						while (!BufferIn.eof())
						{
							getline(BufferIn, newS);
							if (newS.size() > 1) {
								NamesOut << newS << endl;
							}
						}
						NamesOut.close(); BufferIn.close();
						//перезапись в глобальном файле
						changeUser(nomer);
					}
					//Изменяем почту
					if(k==2)
					{
						cout << endl << "Введите новую почту" << endl;
						string newMail;
						getline(cin, newMail);
						while (!regex_match(newMail, mailRegex)||findByEmail(newMail)!=-1)
						{
							cout << endl << "Некорректный ввод или такая почта уже существует, повторите попытку" << endl;
							getline(cin, newMail);
						}
						string newS; int schetchick = 1;
						EmailsIn.open("Emails.txt"); BufferOut.open("Buffer.txt");
						while (!EmailsIn.eof())
						{
							if (schetchick != nomer)
							{

								getline(EmailsIn, newS);
								if (newS.size() > 1)
									BufferOut << newS << endl;
							}
							else
							{

								getline(EmailsIn, newS);

								if (newS.size() > 1) {
									newS = newMail;
									BufferOut << newS << endl;
								}
							}
							schetchick++;
						}
						EmailsIn.close(); BufferOut.close(); EmailsOut.open("Emails.txt"); BufferIn.open("Buffer.txt");
						newS = "";
						while (!BufferIn.eof())
						{
							getline(BufferIn, newS);
							if (newS.size() > 1) {
								EmailsOut << newS << endl;
							}
						}
						EmailsOut.close(); BufferIn.close();

						changeUser(nomer);
					}
					//Изменяем номер
					if(k==3)
					{
						cout << endl << "Введите новый телефон" << endl;
						string newPhone;
						getline(cin, newPhone);
						while (!regex_match(newPhone, telephoneRegex)||findByNumber(newPhone)!=-1)
						{
							cout << endl << "Некорректный ввод или такой номер уже существует, повторите попытку" << endl;
							getline(cin, newPhone);
						}
						//приведение к требуемому формату
						phoneFormat(newPhone);
						string newS; int schetchick = 1;
						PhonesIn.open("Phones.txt"); BufferOut.open("Buffer.txt");
						while (!PhonesIn.eof())
						{
							if (schetchick != nomer)
							{

								getline(PhonesIn, newS);
								if (newS.size() > 1)
									BufferOut << newS << endl;
							}
							else
							{

								getline(PhonesIn, newS);

								if (newS.size() > 1) {
									newS = newPhone;
									BufferOut << newS << endl;
								}
							}
							schetchick++;
						}
						PhonesIn.close(); BufferOut.close(); PhonesOut.open("Phones.txt"); BufferIn.open("Buffer.txt");
						newS = "";
						while (!BufferIn.eof())
						{
							getline(BufferIn, newS);
							if (newS.size() > 1) {
								PhonesOut << newS << endl;
							}
						}
						PhonesOut.close(); BufferIn.close();

						changeUser(nomer);
					}
					//изменяем логин
					if(k==4)
					{
						cout << endl << "Введите новый логин" << endl;
						string newLogin;
						getline(cin, newLogin);
						while ((newLogin.size() < 2)||(findByLogin(newLogin)!=-1))
						{							
							cout << endl << "Некорректный ввод или такой логин уже существует, повторите попытку" << endl;
							getline(cin, newLogin);
						}

						//записываем в буфер текущие ФИО. На строке nomer записываем новое имя
						string newS; int schetchick = 1;
						LoginsIn.open("Logins.txt"); BufferOut.open("Buffer.txt");
						while (!LoginsIn.eof())
						{
							//проверка на строку nomer
							if (schetchick != nomer)
							{

								getline(LoginsIn, newS);
								if (newS.size() > 1)
									BufferOut << newS << endl;
							}
							else
							{

								getline(LoginsIn, newS);

								if (newS.size() > 1) {
									newS = newLogin;
									BufferOut << newS << endl;
								}
							}
							schetchick++;
						}
						//переоткрыли файлы
						LoginsIn.close(); BufferOut.close(); LoginsOut.open("Logins.txt"); BufferIn.open("Buffer.txt");
						newS = "";
						//просто запись из буфера в Names, с уже измененным именем
						while (!BufferIn.eof())
						{
							getline(BufferIn, newS);
							if (newS.size() > 1) {
								LoginsOut << newS << endl;
							}
						}
						LoginsOut.close(); BufferIn.close();
						//перезапись в глобальном файле
						changeUser(nomer);
					}
					//изменяем пароль	
					if(k==5)
					{
						cout << endl << "Введите новый пароль" << endl;
						string newPassword;
						getline(cin, newPassword);
						while (!regex_match(newPassword, passwordRegex))
						{
							cout << endl << "Некорректный ввод, повторите попытку" << endl;
							getline(cin, newPassword);
						}
						
						//записываем в буфер текущие пароли. На строке nomer записываем новый пароль
						string newS; int schetchick = 1;
						PasswordsIn.open("Passwords.txt"); BufferOut.open("Buffer.txt");
						while (!PasswordsIn.eof())
						{
							//проверка на строку nomer
							if (schetchick != nomer)
							{

								getline(PasswordsIn, newS);
								if (newS.size() > 1)
									BufferOut << newS << endl;
							}
							else
							{

								getline(PasswordsIn, newS);

								if (newS.size() > 1) {
									newS = longtostring(hash37(newPassword));
									BufferOut << newS << endl;
								}
							}
							schetchick++;
						}
						//переоткрыли файлы
						PasswordsIn.close(); BufferOut.close(); PasswordsOut.open("Passwords.txt"); BufferIn.open("Buffer.txt");
						newS = "";
						//просто запись из буфера в Names, с уже измененным именем
						while (!BufferIn.eof())
						{
							getline(BufferIn, newS);
							if (newS.size() > 1) {
								PasswordsOut << newS << endl;
							}
						}
						PasswordsOut.close(); BufferIn.close();
												
					}
					cout << endl << "Изменения внесены успешно!"<<endl;
				}
				else {
					cout << endl << "Ошибка ввода пароля, повторите позже";
				}

			}
		}
		//отправить сообщение
		if (k == 5)
		{
			cout << endl << "Добро пожаловать в меню отправки сообщений" << endl << "Чтобы отправить сообщение пользователю, нужно сначала его найти" << endl <<
				"Поиск происходит по ФИО, логину, номеру телефона";

			string str; int nomer = -1;
			int count = 0;

			cin.ignore();
			getline(cin, str);
			while (correctionCheck(str, fioRegex, telephoneRegex) == 0)
			{
				cout << endl << "По указанным данным не удалось найти пользователя. Повторите ввод";
				getline(cin, str);
			}
			cout << "ИЗ ДУВАЙЛА Я ВЫШЕЛ С:" << str;

			//нашлось, все круто, теперь
			if (findByLogin(str) != -1)
			{
				nomer = findByLogin(str);
				//coutFromChosenNumberString(nomer);
			}
			if (regex_match(str, fioRegex))
			{
				nomer = findByName(str);
				//coutFromChosenNumberString(nomer);
			}
			if (regex_match(str, telephoneRegex))
			{
				nomer = findByNumber(str);

				//coutFromChosenNumberString(nomer);

			}

			if (nomer == -1)
			{
				cout << "Пользователь с указанными данными не найден, повторите попытку позже" << endl;
			}
			else {
				cout << "Введите сообщение для этого пользователя: " << endl;
				getline(cin, str);
				cout << endl << "Сообщение успешно отправлено!!!!" << endl;
			}
		}
		//сортировка по выбранному полю
		if(k==6)
		{
			cout << endl << "Вы можете отсортировать пользователей по следующим категориям: " << endl << "1.ФИО" << endl << "2.E-mail"<<endl<<"3.Логин";
			int choose = -1;
			cin >> choose;
			while(choose>3||choose<1)
			{
				cout << endl << "Нет такого пункта, повторите ввод" << endl;
				cin >> choose;
			}
			
			//по фио
			if(choose==1)
			{
				vector<string> names;
				NamesIn.open("Names.txt");
				string str; cin.ignore();
				while(!NamesIn.eof())
				{
					getline(NamesIn, str);
					if (str.size() > 1)
						names.push_back(str);
				}
				NamesIn.close();
				sort(names.begin(), names.end());

				for(int i=0;i<names.size();i++)
				{
					int x = findByName(names[i]);

					if(x!=-1)
					coutFromChosenNumberString(x);
				}
			}

			//по мэилу
			if(choose==2)
			{
				vector<string> mails;
				EmailsIn.open("Emails.txt");
				string str; cin.ignore();
				while(!EmailsIn.eof())
				{
					getline(EmailsIn, str);
					if (str.size() > 1)
						mails.push_back(str);
				}
				EmailsIn.close();
				sort(mails.begin(), mails.end());

				for(int i=0;i<mails.size();i++)
				{
					int x = findByEmail(mails[i]);

					if (x != -1)
						coutFromChosenNumberString(x);
				}
			}

			//по логину
			if (choose == 3) {
				vector<string> logins;
				LoginsIn.open("Logins.txt");
				string str; cin.ignore();
				while (!LoginsIn.eof())
				{
					getline(LoginsIn, str);
					if(str.size()>1)
					logins.push_back(str);
					
				}
				LoginsIn.close();
				sort(logins.begin(), logins.end());
				
				for(int i=0;i<logins.size();i++)
				{
					
					int x = findByLogin(logins[i]);
				
					if(x!=-1)
					coutFromChosenNumberString(x);
				}


			}
		}
		
	}

	cout << endl << "Спасибо за использование программы!!!";
	
}

