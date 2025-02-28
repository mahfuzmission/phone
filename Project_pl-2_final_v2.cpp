#include<iostream>
#include<ctime>
#include<string>
#include<fstream>
#include<conio.h>

using namespace std;

class Abst
{
public:
    virtual float get_call_cost() = 0;

};

class phone_Call:public Abst{
private:
	string start_time = "";
	string date  ;
	float call_duration = 0.00;
	float call_cost = 0.00;
public:
	phone_Call(){}
	~phone_Call(){}
	void set_start_time(string n){ start_time = n; }
	string get_start_time(){ return start_time; }
	void set_start_date(string n){ date = n; }
	string get_start_date(){ return date; }
	void set_call_duration(float n){ call_duration = n; }
	float get_call_duration(){ return call_duration; }
	void set_call_cost(float n){ call_cost = n; }
	float get_call_cost(){ return call_cost; }
	void display_call_details();
	void missed_Call_details();
};

void phone_Call::display_call_details(){
	cout << "start time    :" << start_time << endl;
	cout << "Date          :" << date << endl;
	cout << "Call duration :" << call_duration << " seconds" << endl;
	cout << "Call cost     :" << call_cost << " BDT" << endl;
}

void phone_Call::missed_Call_details(){
	cout << "missed call time :" << start_time << endl;
	cout << "missed call date :" << date << endl;
}


class phone : public phone_Call{
private:
	string phone_number_one;
	string phone_number_two;
	float credit = 0.00;
	string call_history = "";
	string message_histoy = "";
public:
	phone(){}
	~phone(){}
	void set_phone_number_one(string n){ phone_number_one = n; }
	string get_phone_number_one(){ return phone_number_one; }
	void set_phone_number_two(string n){ phone_number_two = n; }
	string get_phone_number_two(){ return phone_number_two; }
	void set_credit(float n){ credit = n; }
	float get_credit(){ return credit; }
	void set_history(string n){ call_history = n; }
	string get_history(){ return call_history; }
	void set_msg_history(string msg){ message_histoy = msg; }
	string get_msg_history(){ return message_histoy; }
	void display_phone_details();
};
void phone::display_phone_details(){
	cout << "Phone numbers- " << endl;;
	cout << "sim1 :+0" << phone_number_one << endl;
	cout << "sim2 :+0" << phone_number_two << endl;
	cout << "credit        :" << credit << " BDT" << endl;
	cout << "call History  :" << call_history << endl;
	cout << "messages      :" << message_histoy << endl;

}


class person{
private:
	string name = "";
	float avg_call_time = 0.00;
	float total_cost = 0.00;
public:
	person(){}
	~person(){}
	int total_call = 0;
	float total_time = 0;
	phone owned_phone;    //person's phone.
	void set_name(string n){ name = n; }
	string get_name(){ return name; }
	void set_avg_call_time(float n){ avg_call_time = n; }
	float get_avg_call_time(){ return avg_call_time; }
	void set_total_cost(float n){ total_cost = n; }
	float get_total_cost(){ return total_cost; }

	void person_details();
};
void person::person_details(){
	cout << "Name                 :" << name << endl;
	cout << "avarage call time    :" << avg_call_time << " sec" << endl;
	cout << "Total call costed    :" << total_cost << " BDT" << endl;
	cout << "owned phone details-" << endl;
	owned_phone.display_phone_details();
}

class person_db {
public:
	person *db;
	int size = 1;
	int index = 0;
	person_db(){ db = new person[size]; }
	~person_db(){ delete[] db; }
	bool db_is_empty();
	int search_by_phone_number(string n);
	void resize_database();
	void add_person();
	void recharge();
	void display_all();
	void display_one();
	void display_all_name_number();
};

bool person_db::db_is_empty(){
	if (index == 0) return true;
	else return false;
}
int person_db::search_by_phone_number(string n){
	if (db_is_empty() == true)cout << "Person Database empty!" << endl;
	else{
		for (int i = 0; i < index; i++){
			if (n == db[i].owned_phone.get_phone_number_one() || n == db[i].owned_phone.get_phone_number_two()) return i;
			else continue;
		}
	}
	return -1;
}


void person_db::resize_database(){
	person *new_db = new person[++size];
	for (int i = 0; i < index; i++){
		new_db[i] = db[i];
	}
	db = new_db;
}

void person_db::add_person(){
	string msg ;
	string n = "";
	float balance = 0;
	string a;
	cout << "Enter name:";
	cin >> n;
	db[index].set_name(n);

	cout << "Enter phone number -\nFor sim1 :";
	while (1)
	{
		cin >> a;
		{
			try
			{
			    bool result = true;

			    for(int i=0;i<a.length();i++)
                {
                    if(!(a[i]<=57 && a[i]>=48)) //check string(integer)
                    {
                        result = false;
                        break;
                    }
                }
				if(result)
				{
					if (db_is_empty() == true){
						db[index].owned_phone.set_phone_number_one(a);
						break;
					}
					else{
						if (search_by_phone_number(a) > -1){
							cout << "number already exists!\n enter a new one:";
							continue;
						}
						else{
							db[index].owned_phone.set_phone_number_one(a);
							break;
						}
					}

				}
				else
				{
					throw "Invalid Input.\nTry again :";

				}
			}
			catch (const char* msg){ cout << msg << endl; }
		}

	}
	cout << "For sim2 :";
	while (1){
		cin >> a;
		if (db_is_empty() == true){
			db[index].owned_phone.set_phone_number_two(a);
			break;
		}
		else{
			if (search_by_phone_number(a) >-1){
				cout << "number already exists!\n enter a new one:";
				continue;
			}
			else{
				db[index].owned_phone.set_phone_number_two(a);
				break;
			}

		}
	}

	cout << "Enter credit(minimum 1 BDT will need to make a call) :";
	cin >> balance;
	db[index].owned_phone.set_credit(db[index].owned_phone.get_credit() + balance);

	++index;
	resize_database();
}

void person_db::recharge() {
	cout << "Enter phone number:";
	string num = "";
	cin >> num;
	int i = search_by_phone_number(num);
	if (i == -1){ cout << "number didn't match." << endl; }
	else {
		cout << "Enter amount:";
		float tk = 0;
		cin >> tk;
		db[i].owned_phone.set_credit(db[i].owned_phone.get_credit() + tk);
	}
}

void person_db::display_all(){
	if (db_is_empty() == true)cout << "no person exists to display!\nadd some person first!" << endl;
	else{
		cout << "dislaying all the persons in this programme" << endl;
		for (int i = 0; i < index; i++){
			cout << "------------------------------------" << endl;
			db[i].person_details();
		}
	}
}

void person_db::display_one(){
	if (db_is_empty() == true)cout << "no person exists to dispaly!\nadd some person first!" << endl;
	else{
		cout << "Enter number :";
		string n = "";
		cin >> n;
		int i = search_by_phone_number(n);
		if (i == -1)cout << "person doesn't exist!" << endl;
		else{
			db[i].person_details();
		}
	}
}

void person_db::display_all_name_number(){
	for (int i = 0; i < index; i++){
		cout << "--------------------------------------" << endl;
		cout << "serial no:" << i << endl;
		cout << "Name           :" << db[i].get_name() << endl;
		cout << "Phone numbers-" << endl;;
		cout << "sim1 :+0" << db[i].owned_phone.get_phone_number_one() << endl;
		cout << "sim2 :+0" << db[i].owned_phone.get_phone_number_two() << endl;
	}
	cout << endl;
}


person_db database;

float call_charge(float sec){
	return sec * .20;
}

void make_a_call(){
	if (database.db_is_empty() == true)cout << "no person exists!\nadd a person first!" << endl;
	else{
		cout << "Displaying all persons who are registerd..." << endl;
		database.display_all_name_number();
		cout << "you can also choose a number that not yet registered." << endl;

		cout << "from above list, which person are you ?" << endl;
		cout << "enter the serial no :";
		int serial = 0;

		while (1){
			cin >> serial;
			if (serial > database.index - 1 || serial < 0){
				cout << "wrong serial!\nenter correctly :";
				continue;
			}
			else break;
		}
		string caller_num = "";
		cout << "press 1 to make a call from sim1\npress 2 to make a call from sim2" << endl;
		cout << "enter :";
		int ch = 0;
		while (1){
			cin >> ch;
			switch (ch){
			case 1:{
				caller_num = database.db[serial].owned_phone.get_phone_number_one();
				break;
			}
			case 2:{
				caller_num = database.db[serial].owned_phone.get_phone_number_two();
				break;
			}
			default:{
				cout << "worng key pressed!\nEnter again :";
				continue;
			}

			}
			break;
		}

		cout << "caller selected!" << endl;
		string receiver_num = "";
		cout << "enter receiver's number :";
		cin >> receiver_num;
		cout << "receiver selected!" << endl;

		int i = database.search_by_phone_number(caller_num);
		int j = database.search_by_phone_number(receiver_num);


		struct tm nowinfo, theninfo;

		cout << "press 'enter' to make the call" << endl;
		_getch();
		cout << "calling.....\nconnecting.....\nreceived...." << endl;

		time_t now = time(NULL);
		nowinfo = *(localtime(&now));
		char now_time[20], now_date[20];
		strftime(now_time, 20, "%I:%M:%S%p", &nowinfo);
		strftime(now_date, 20, "%x", &nowinfo);

		cout << "\nongoing call....\n\npress 'enter' to end the call" << endl;
		_getch();
		cout << "\ncall ended" << endl;

		time_t then = time(NULL);
		theninfo=*(localtime(&then));
		float duration = difftime(then, now);
		float cost = call_charge(duration);

		if (duration <= 1){
			cout << "missed call!" << endl;
			phone_Call call;
			call.set_start_date(now_date);
			call.set_start_time(now_time);
			call.missed_Call_details();

			if (i > -1){

				string caller_history = "";
				caller_history += "\n--------------------------\n";
				caller_history += "Date->";
				caller_history += now_date;
				caller_history += "\nTime->";
				caller_history += now_time;
				caller_history += "\nmissed call To->+0";
				string a = receiver_num;
				caller_history += a;
				database.db[i].owned_phone.set_history(database.db[i].owned_phone.get_history() += caller_history);
			}

			if (j > -1){
				string receiver_history = "";
				receiver_history += "\n--------------------------\n";
				receiver_history += "Date->";
				receiver_history += now_date;
				receiver_history += "\nTime->";
				receiver_history += now_time;
				receiver_history += "\nmissed call From->+0";
				string a = caller_num;
				receiver_history += a;
				database.db[j].owned_phone.set_history(database.db[j].owned_phone.get_history() += receiver_history);
			}
			ofstream outfile;
			outfile.open("callhistory.txt", ios_base::app);

			outfile << "Missed call !" << endl;
			outfile << "caller num: 0" << caller_num << endl;
			outfile << "receiver num: 0" << receiver_num << endl;
			outfile << "Time : " << now_time << endl;
			outfile << "Date : " << now_date << endl;
			outfile << "Call Duration: " << duration << endl;
			outfile << "Call Cost: " << cost << "tk \n\n" << endl;

			outfile.close();
		}
		else{

			phone_Call call;
			call.set_call_cost(cost);
			call.set_call_duration(duration);
			call.set_start_time(now_time);
			call.set_start_date(now_date);
			call.display_call_details();

			if (i > -1){
				database.db[i].total_call++;
				database.db[i].set_total_cost(database.db[i].get_total_cost() + cost);
				database.db[i].owned_phone.set_credit(database.db[i].owned_phone.get_credit() - cost);
				database.db[i].total_time = database.db[i].total_time + duration;
				database.db[i].set_avg_call_time(database.db[i].total_time / database.db[i].total_call);
				string caller_history = "";
				caller_history += "\n--------------------------\n";
				caller_history += "Date->";
				caller_history += now_date;
				caller_history += "\nTime->";
				caller_history += now_time;
				caller_history += "\nTo->+0";
				string a = receiver_num;
				caller_history += a;
				database.db[i].owned_phone.set_history(database.db[i].owned_phone.get_history() += caller_history);
			}

			if (j > -1){
				string receiver_history = "";
				receiver_history += "\n--------------------------\n";
				receiver_history += "Date->";
				receiver_history += now_date;
				receiver_history += "\nTime->";
				receiver_history += now_time;
				receiver_history += "\nFrom->+0";
				string a = caller_num;
				receiver_history += a;
				database.db[j].owned_phone.set_history(database.db[j].owned_phone.get_history() += receiver_history);
			}

			ofstream outfile;
			outfile.open("callhistory.txt", ios_base::app);

			outfile << "caller num: 0" << caller_num << endl;
			outfile << "receiver num: 0" << receiver_num << endl;
			outfile << "Time : " << now_time << endl;
			outfile << "Date : " << now_date << endl;
			outfile << "Call Duration: " << duration << endl;
			outfile << "Call Cost: " << cost << "tk \n\n" << endl;

			outfile.close();
		}
	}
}

void send_a_message(){
	if (database.db_is_empty() == true)cout << "no person exists!\nadd a person first!" << endl;
	else{
		cout << "Displaying all persons who are registerd..." << endl;
		database.display_all_name_number();
		cout << "you can also choose a number that not yet registered." << endl;

		cout << "from above list, which person are you ?" << endl;
		cout << "enter the serial no :";
		int serial = 0;

		while (1){
			cin >> serial;
			if (serial > database.index - 1 || serial < 0){
				cout << "wrong serial!\nenter correctly :";
				continue;
			}
			else break;
		}
		string sender_num = "";
		cout << "press 1 to send a sms from sim1\npress 2 to send a sms from sim2" << endl;
		cout << "enter :";
		int ch = 0;
		while (1){
			cin >> ch;
			switch (ch){
			case 1:{
				sender_num = database.db[serial].owned_phone.get_phone_number_one();
				break;
			}
			case 2:{
				sender_num = database.db[serial].owned_phone.get_phone_number_two();
				break;
			}
			default:{
				cout << "worng key pressed!\nEnter again :";
				continue;
			}

			}
			break;
		}

		cout << "sender selected!" << endl;
		string receiver_num = "";
		cout << "enter receiver's number :";
		cin >> receiver_num;
		cout << "receiver selected!" << endl;

		string message = "";
		cout << "Type your message here (within 150 charecters) :";
		cin.ignore();
		getline(cin, message);

		int i = database.search_by_phone_number(sender_num);
		int j = database.search_by_phone_number(receiver_num);

		struct tm nowinfo;

		cout << "\npress 'enter' to send the message" << endl;
		_getch();


		cout << "connecting.....\nsending....\nsent!" << endl;

		if (message.length() > 150){
			cout << "cost :1.00 BDT" << endl;
			database.db[i].set_total_cost(database.db[i].get_total_cost() + 1);
			database.db[i].owned_phone.set_credit(database.db[i].owned_phone.get_credit() - 1);
		}
		else{
			cout << "cost :.30 BDT" << endl;
			database.db[i].set_total_cost(database.db[i].get_total_cost() + .30);
			database.db[i].owned_phone.set_credit(database.db[i].owned_phone.get_credit() - .30);
		}

		time_t now = time(NULL);
		nowinfo = *(localtime(&now));
		char now_time[20], now_date[20];
		strftime(now_time, 20, "%I:%M:%S%p", &nowinfo);
		strftime(now_date, 20, "%x", &nowinfo);

		string sent_message = "";
		sent_message += "\n--------------------------\n";
		sent_message += "To->+0";
		string a = receiver_num;
		sent_message += a;
		sent_message += "\nDate->";
		sent_message += now_date;
		sent_message += "\nTime->";
		sent_message += now_time;
		sent_message += "\n";
		sent_message += message;
		database.db[i].owned_phone.set_msg_history(database.db[i].owned_phone.get_msg_history() += sent_message);

		if (j > -1){
			string recieved_message = "";
			recieved_message += "\n--------------------------\n";
			recieved_message += "From->+0";
			string a = sender_num;
			recieved_message += a;
			recieved_message += "\nDate->";
			recieved_message += now_date;
			recieved_message += "\nTime->";
			recieved_message += now_time;
			recieved_message += "\n";
			recieved_message += message;
			database.db[j].owned_phone.set_msg_history(database.db[j].owned_phone.get_msg_history() += recieved_message);
		}
		ofstream outfile;
		outfile.open("callhistory.txt", ios_base::app);

		outfile << "Message sending was successful." << endl;
		outfile << "Message sender number: 0" << sender_num << endl;
		outfile << "Message receiver number: 0" << receiver_num << endl;
		outfile << "Time : " << now_time << endl;
		outfile << "Date : " << now_date << "\n\n" << endl;

		outfile.close();
	}
}

void handler(){
	char choice = '\0';
	int select = 0;

	while (choice != 'e' && choice != 'E'){
		cout << "Welcome to the 'Mobile Phone Bill' programme\n" << endl;
		cout << "********Main Menu********" << endl;
		cout << "press 1 to see all infomation of the persons" << endl;
		cout << "press 2 to see a perticuler person's details" << endl;
		cout << "press 3 to make a call" << endl;
		cout << "press 4 to send a message" << endl;
		cout << "press 5 to add a person" << endl;
		cout << "press 6 to recharge a number" << endl;
		cout << "\nEnter your choice :";
		cin >> select;
		switch (select){
		case 1:{
			database.display_all();
			break;
		}
		case 2:{
			database.display_one();
			break;
		}
		case 3:{
			make_a_call();
			break;
		}
		case 4:{
			send_a_message();
			break;
		}
		case 5:{
			database.add_person();
			break;
		}
		case 6:{
			database.recharge();
			break;
		}
		default:{
			cout << "wrong key pressed!" << endl;
			break;
		}
		}
		cout << "\nEnter e to exit or c to return to the main menu :";
		cin >> choice;
	}


}


int main()
{
	handler();


	return 0;
}









