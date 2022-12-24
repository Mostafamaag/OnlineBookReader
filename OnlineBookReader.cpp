
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

string GetTime() {

	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();

}

int ReadInt(int low, int high) {
	int num;
	cout << "Please enter number between " << low << "-" << high << ":";
	cin >> num;
	if (num >= low && num <= high) {
		return num;
	}
	cout << "Invalid number!\n";
	return ReadInt(low, high);

}


class Book {
private:
	string title;
	string author;
	string isbn;
	vector<string> pages;
public:
	Book() {
	}
	Book(string title, string author, vector<string> pages) {

		this->title = title;
		this->author = author;
		this->pages = pages;

	}
	void ReadBook() {
		string s;
		cout << "Enter your book Isbn :";
		cin >> s;
		setIsbn(s);
		cout << "Enter your book title :";
		cin >> s;
		setTitle(s);

		cout << "Enter your book author :";
		cin >> s;
		setAuthor(s);

		cout << "Enter your book number of pages :";
		//while ()
		int num;
		cin >> num;

		cout << "Enter your book pages\n";
		for (int i = 1; i <= num; i++) {
			cout << "Page #" << i << endl;
			cin >> s;
			pages.push_back(s);

		}
	}
	void PrintBookInformation() {
		cout << "Book title : " << getTitle() << endl;
		cout << "Book author : " << getAuthor() << endl;
		cout << "Number of pages : " << getPages().size() << endl;

	}

	const string& getTitle() const {
		return title;
	}
	const string& getAuthor() const {
		return author;
	}
	const vector<string>& getPages() const {
		return pages;
	}

	void setTitle(const string& name) {
		this->title = name;
	}
	void setAuthor(const string& author) {
		this->author = author;
	}
	void setPages(const vector<string>& pages) {
		this->pages = pages;
	}

	const string& getIsbn() const {
		return isbn;
	}
	void setIsbn(const string& isbn) {
		this->isbn = isbn;
	}

};

class Session {
private:
	int last_reading_page;
	string last_reading_time;
	Book* book;

public:
	Session(Book* book) :
		book(book), last_reading_page(0), last_reading_time(GetTime()) {
	}
	Session():Session(nullptr){
	}

	void print_session_information() {
		cout << "Book title : " << book->getTitle() << endl;
		cout << "Last reading page : " << getLastReadingPage() << endl;
		cout << "Last reading time : " << getLastReadingTime() << endl;
	}

	const string& getCurrentPageContent() {
		return book->getPages()[last_reading_page];
	}

	void NextPage() {
		if (last_reading_page < (int)book->getPages().size() - 1) {
			last_reading_page++;
		}

	}
	void PreviousPage() {
		if (last_reading_page > 0) {
			last_reading_page--;
		}
	}
	void RestLastReadingTime() {
		last_reading_time = GetTime();
	}

	int getLastReadingPage() const {
		return last_reading_page;
	}

	const string& getLastReadingTime() const {
		return last_reading_time;
	}

	void setLastReadingPage(int lastReadingPage) {
		last_reading_page = lastReadingPage;
	}

	void setLastReadingTime(const string& lastReadingTime) {
		last_reading_time = lastReadingTime;
	}

	const Book* getBook() const {
		return book;
	}

};

class User {
private:
	string name;
	string email;
	string username;
	string password;
	bool admin;
	vector<Session*> sessions;

public:

	//prevent copy constructor
	User(const User&) = delete;
	void operator=(const User&) = delete;

	User() {
		admin = false;
	}

	~User() {
		for (auto& session : sessions) {
			delete session;
		}
		sessions.clear();
	}

	string ViewProfile() const {
		ostringstream oss;
		oss << "Name: " << getName();
		if (isAdmin())
			oss << "| Admin";
		oss << endl;
		oss << "Username : " << getUsername() << endl;
		oss << "Email : " << getEmail() << endl << endl;

		return oss.str();
	}

	void ViewCurrentSessions() {
		for (int i = 1; i < (int)getSessions().size(); i++) {
			cout << "Session#" << i << endl;
			cout << "Last reading page : "
				<< getSessions()[i]->getLastReadingPage() << endl;
			cout << "Last reading time : "
				<< getSessions()[i]->getLastReadingTime() << endl;
		}
	}

	void ReadUser(const string& user) {

		setUsername(user);

		string s;

		cout << "Enter Name : ";
		cin >> s;
		if (s == "") cout << "\nNULLL\n";
		setName(s);

		cout << "Enter Email : ";
		cin >> s;
		setEmail(s);

		cout << "Enter Password : ";
		cin >> s;
		setPassword(s);

		setAdmin(false);

	}

	const string& getName() const {
		return name;
	}

	const string& getEmail() const {
		return email;
	}

	const string& getUsername() const {
		return username;
	}

	const string& getPassword() const {
		return password;
	}

	void setName(const string& name) {
		this->name = name;
	}

	void setEmail(const string& email) {
		this->email = email;
	}

	void setUsername(const string& username) {
		this->username = username;
	}

	void setPassword(const string& password) {
		this->password = password;
	}

	const vector<Session*>& getSessions() const {
		return sessions;
	}

	Session* AddSession(Book* book) {
		Session* session = new Session(book);
		sessions.push_back(session);
		return session;
	}

	void setAdmin(bool admin) {
		this->admin = admin;
	}

	bool isAdmin() const {
		return admin;
	}

};

class UsersManger {
private:

	User* current_user = nullptr;
	map<string, User*> usersMap;

	void FreeLoadedData() {
		for (auto i : usersMap) {
			delete i.second;
		}
		// delete current_user;
		current_user = nullptr;
		usersMap.clear();
	}

public:

	//prevent copy constructor
	UsersManger(const UsersManger &) = delete;
	void operator=(const UsersManger &) = delete;

	UsersManger() {

	}

	~UsersManger() {
		cout << "Destructor: CustomerManager\n";
		FreeLoadedData();
	}

	const User* getCurrentUser() const {
		return current_user;
	}

	//dummy data
	void LoadDatabase() {
	//	cout << "UsersManager : Loading Database ... " << endl;
		FreeLoadedData();

		User* c1 = new User();
		c1->setName("Ahmed");
		c1->setUsername("ahmedxx");
		c1->setEmail("ahmed@gmail.com");
		c1->setPassword("12345");
		c1->setAdmin(false);
		usersMap[c1->getUsername()] = c1;

		User* c2 = new User();
		c2->setName("Mostafa");
		c2->setUsername("mostafaxx");
		c2->setEmail("mostafa@gmail.com");
		c2->setPassword("123456");
		c2->setAdmin(true);
		usersMap[c2->getUsername()] = c2;

		User* c3 = new User();
		c3->setName("mohamed");
		c3->setUsername("mohamedxx");
		c3->setEmail("mohamed@gmail.com");
		c3->setPassword("123");
		c3->setAdmin(false);
		usersMap[c3->getUsername()] = c3;

	}


	void AccessSystem() {

		cout << "1.Login \n2.SignUp\n";
		int in = ReadInt(1, 2);
		//cin >> in;
		if (in == 1)
			Login();
		else if (in == 2)
			SignUp();
	}

	void Login() {
		//LoadDatabase();
		while (true) {
			string user, pass;
			cout << "Enter your username: ";
			cin >> user;
			cout << "Enter your password: ";
			cin >> pass;

			if (!usersMap.count(user)) {
				cout << "Enter valid username" << endl;
				continue;
			}
			User* u = usersMap.find(user)->second;
			if (u->getPassword() != pass) {
				cout << "Wrong password, please try again" << endl;
				continue;
			}
			current_user = u;
			// cout << current_cust->ViewProfile();
			break;

		}
	}

	void SignUp() {
		string usr;
		while (true) {

			cout << "Enter your username:";
			cin >> usr;

			if (usersMap.count(usr)) {
				cout << "User already exist,try another" << endl;
			}
			else
				break;

		}

		User *u = new User();
		u->ReadUser(usr);
		current_user = u;
		usersMap[current_user->getUsername()] = current_user;
		//Login();
	}

	Session* AddSession(Book* book) {
		return current_user->AddSession(book);
	}

};

class BooksManager {
private:
	map <string, Book*>bookMap;

public:
	BooksManager() {

	}
	~BooksManager() {
		cout << "Destuctor: BookManager\n";
		for (auto book : bookMap) {
			delete book.second;
		}
		bookMap.clear();
	}

	//prevent copy constructor
	BooksManager(const BooksManager&) = delete;
	void operator=(const BooksManager&) = delete;

	void LoadDatabase() {
		//cout << "BooksManager : LoadDatabase ... \n";
		Book* book1 = new Book();
		book1->setIsbn("00001");
		book1->setAuthor("Mostafa");
		book1->setTitle("C++ how to program");
		vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
		book1->setPages(pages1);
		addBook(book1);

		Book* book2 = new Book();
		book2->setIsbn("00002");
		book2->setAuthor("Morad");
		book2->setTitle("Intro to algo");
		vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
		book2->setPages(pages2);
		addBook(book2);

		Book* book3 = new Book();
		book3->setIsbn("00003");
		book3->setAuthor("Morad");
		book3->setTitle("Data Structures in C++");
		vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
		book3->setPages(pages3);
		addBook(book3);
	}

	void addBook(Book* book) {
		bookMap[book->getIsbn()] = book;
	}

	void DeleteBook(const string& isbn) {
		bookMap[isbn] = nullptr;
		bookMap.erase(isbn);
	}

	void setBookMap(const map<string, Book*>& bookMap) {
		this->bookMap = bookMap;
	}

	const map<string, Book*>& getBookMap() const {
		return bookMap;
	}

};

class UserView {
private:
	BooksManager& bm;
	UsersManger& um;
public:
	UserView(BooksManager& bm, UsersManger& cm) : bm(bm), um(cm) {
	}

	void Display() {
		const User* customer = um.getCurrentUser();
		cout << " \n\nHello " << customer->getName() << "\n";
		while (true) {

			cout << "1.View Profile" << endl;
			cout << "2.List & Select from My Reading History" << endl;
			cout << "3.List & Select from Available Books" << endl;
			cout << "4.Logout" << endl;


			int in = ReadInt(1, 4);
			//  cin >> in;
			if (in == 1) {
				cout << customer->ViewProfile();

			}
			else if (in == 2) {
				ListReadingHistory();

			}
			else if (in == 3) {
				ListAvailableBooks();

			}
			else if (in == 4) break;

		}
	}
	void DisplaySession(Session* session) {


		string pcn;
		while (pcn != "Close" || pcn != "close") {
			cout << "Current Page: " << session->getLastReadingPage()+1 << "\n";
			cout << "\n" << session->getCurrentPageContent() << "\n";
			cout << "\n Previous - Close - Next " << endl;
			cout << "Type your choice : ";
			cin >> pcn;
			if (pcn == "previous" || pcn == "Previous") {

				session->PreviousPage();

			}
			else if (pcn == "Next" || pcn == "next") {
				session->NextPage();

			}
			else break;


		}
		session->RestLastReadingTime();

	}
	void ListReadingHistory() {
		int i = 0;
		const auto& sessions = um.getCurrentUser()->getSessions();

		for (auto& session : sessions) {
			cout << "\n -----Session" << ++i << "-----\n";
			session->print_session_information();
		}
		if (i == 0) {
			cout << "\nNo history. List books and start having fun\n";
			ListAvailableBooks();
		}
		else {
			cout << "Which session want to open? ";
			int ch = ReadInt(1, i);

			DisplaySession(sessions[ch - 1]);
		}

	}
	void ListAvailableBooks() {
		const map<string, Book*> books = bm.getBookMap();
		int num = 0;
		for (auto b : books) {

			cout << "-----Book" << ++num << "-----\n";
			b.second->PrintBookInformation();
			cout << endl;

		}
		cout << "Which book want to read? ";
		int ch = ReadInt(1, books.size());
		// cin >> ch;
		int i = 0;
		for (auto b : books) {
			if (ch == ++i) {
				Session* session = um.AddSession(b.second);
				DisplaySession(session);
			}

		}
	}
};


class AdminView {
private:
	UsersManger& cm;
	BooksManager& bm;


public:
	AdminView(UsersManger& cm, BooksManager& bm) :cm(cm), bm(bm) {
	}


	void Display() {
		const User* current_admin = cm.getCurrentUser();

		while (true) {

			cout << "\nHello ," << current_admin->getName() << " Admin View\n";
			cout << "1.View profile\n";
			cout << "2.Add Book\n";
			cout << "3.Logout\n";
			int input = ReadInt(1, 3);
			//cin >> input;
			if (input == 1) {
				cout << current_admin->ViewProfile();
			}
			else if (input == 2) {
				Book* book = new Book();
				book->ReadBook();
				bm.addBook(book);
			}
			else if (input == 3) {
				break;
			}

		}

	}
};


class OnlineSystemReader {
private:
	UsersManger* cm;
	BooksManager* bm;
	void LoadDatabase() {
		cm->LoadDatabase();
		bm->LoadDatabase();
	}
public:
	OnlineSystemReader() :
		cm(new UsersManger()), bm(new BooksManager()) {
	}
	~OnlineSystemReader() {
		cout << "Destuctor: OnlineReaderSystem\n";
		if (cm != nullptr) {
			delete cm;
			cm = nullptr;
		}
		if (bm != nullptr) {
			delete bm;
			bm = nullptr;
		}
	}
	void Run() {
		LoadDatabase();
		while (true) {
			cm->AccessSystem();
			if (cm->getCurrentUser()->isAdmin()) {
				AdminView view(*cm, *bm);
				view.Display();
			}
			else {
				UserView view(*bm, *cm);
				view.Display();
			}

		}
	}
};


int main() {

	OnlineSystemReader site;
	site.Run();

	return 0;
}
