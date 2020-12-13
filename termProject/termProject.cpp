#include <iostream>
#include <fstream>
#include <vector>
#include<sstream>

using namespace std;

#define MAXBUFFSIZE 75

class Book {
    private :
		vector<string> words;
		vector<vector<int> > pages;
    public :
		vector<string> cmd;
		int currentPage = 0;
		int index = 0;
		void addPage(vector<int> page) {
			if(currentPage < pages.size()) pages.at(currentPage) = page;
			else pages.push_back(page);
		}
		vector<vector<int> > *getPage() {
			return &pages;
		}
		vector<string> *getWords() {
			return &words;
		}

};

class Command {
    public :
        virtual ~Command(){}
        virtual void excute() = 0;
};

vector<int> showPage(Book *book, int *i) {
	int count = 0;
	int index = *i;
	int strLength = 0;
	vector<int> page;
	
	page.push_back(index); //페이지 한줄의 첫번째 단어 index삽입
	cout << setw(2) << count+1 << "|";
	while (count < 20) {
		string word = book->getWords()->at(index);
		strLength += word.length();
		if (strLength <= MAXBUFFSIZE) {
			cout << word << " ";
			strLength += 1;
		} else {
			count++;
			if(count >= 20) break;
			page.push_back(index);
			strLength = word.length() + 1;
			cout << endl << setw(2) << count+1 <<"|" << word << " ";
		}
		index++;
	}
	cout << "\n---------------------------------------------------------------------------" << endl;
	cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" <<endl;
	cout << "---------------------------------------------------------------------------" << endl;
	*i = index;
	return page;
}

class next_command : public Command {
	Book *book;

    public :
		next_command(Book *book) : book(book){};
        virtual void excute() {
			if(book->index>0) book->currentPage++;//페이지 증가
			vector<int> page = showPage(book,&book->index);
			book->addPage(page); //완성된 20줄 페이지를 book에 삽입
			cout << "Page : " << book->currentPage+1 << endl;
		}
};

class before_command : public Command {
    Book *book;
    public :
		before_command(Book *book) : book(book){};
        virtual void excute() {
			int beforePage = book->currentPage - 1;
			if(beforePage < 0)
				cout << "This is the first Page!!" << "  "<< beforePage << endl;
			else {
				book->index = book->getPage()->at(beforePage).at(0);
				cout << book->index << endl;
				vector<int> page = showPage(book,&book->index);
				book->getPage()->at(beforePage) = page;
				book->currentPage = beforePage;
				cout << "Page : " << book->currentPage+1 << endl;
			}
		}
};

class insert_command : public Command {
    Book *book;
    public :
		insert_command(Book *book) : book(book){};
        virtual void excute() {
			if(book->cmd.size() != 3 || book->cmd[2].length() > 75) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "Doesn't fit the format! Try again!" << endl;
				return ;
			}
			int line = stoi(book->cmd[0])-1;
			int word = stoi(book->cmd[1])-1;
			vector<int> page = book->getPage()->at(book->currentPage);
			//page[line]+word;n번째 줄 m번째 단어
			if(line >= 20 || page[line]+word >= page[line+1] || page[line]+word > book->getPage()->at(book->currentPage)[0]) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "It doesn`t exist!! Try again!!" << endl;
				return ;
			}
			cout << book->getWords()->at(page[line]+word)<< endl;
			book->getWords()->insert(book->getWords()->begin()+page[line]+word+1,book->cmd[2]);
			book->index = book->getPage()->at(book->currentPage).at(0);
			book->getPage()->at(book->currentPage) = showPage(book,&book->index);
			cout << "Insert Success!! ";
			cout << "Page : " << book->currentPage+1 << endl;
		};
};

class delete_command : public Command {
    Book *book;
    public :
		delete_command(Book *book) : book(book){};
        virtual void excute() {
			if(book->cmd.size() != 2) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "Doesn't fit the format! Try again!" << endl;
				return ;
			}
			int line = stoi(book->cmd[0])-1;
			int word = stoi(book->cmd[1])-1;
			vector<int> page = book->getPage()->at(book->currentPage);
			//page[line]+word;n번째 줄 m번째 단어
			if(line >= 20 || page[line]+word >= page[line+1] || page[line]+word > book->getPage()->at(book->currentPage)[0]) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "It doesn`t exist!! Try again!!" << endl;
				return ;
			}
			cout << book->getWords()->at(page[line]+word)<< endl;
			book->getWords()->erase(book->getWords()->begin()+page[line]+word);
			book->index = book->getPage()->at(book->currentPage).at(0);
			book->getPage()->at(book->currentPage) = showPage(book,&book->index);
			cout << "Delete Success!! ";
			cout << "Page : " << book->currentPage+1 << endl;
			
		};
};

class change_command : public Command {
    Book *book;
    public :
		change_command(Book *book) : book(book){};
        virtual void excute() {
			if(book->cmd.size() != 2 || book->cmd[0].length() > 75 || book->cmd[1].length() > 75) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "Doesn't fit the format! Try again!" << endl;
				return ;
			}
			vector<string> *str = book->getWords();
			for(int i=0; i<str->size(); i++) {
				if(str->at(i).compare(book->cmd[0]) == 0)
					str->at(i) = book->cmd[1];
			}
			book->index = book->getPage()->at(book->currentPage).at(0);
			vector<int> page = showPage(book,&book->index);
			book->getPage()->at(book->currentPage) = page;
			cout << "Change Success!" <<endl;
		};
};

class search_command : public Command {
    Book *book;
    public :
		search_command(Book *book) : book(book){};
        virtual void excute() {
			if(book->cmd.size() != 1 || book->cmd[0].length() > 75) {
				cout << "---------------------------------------------------------------------------" << endl;
				cout << "Doesn't fit the format! Try again!" << endl;
				return ;
			}
			vector<string> str = *book->getWords();
			int i = 0;
			while(str[i].compare(book->cmd[0]) != 0 && i<str.size()) {
				i++;
			}
			if(i<str.size()) {
				showPage(book,&i);
				cout << "search Page!" << endl;
			}
			else {cout << "NOT FOUND" << endl;}
		};
};

class save_command : public Command {
	 Book *book;
    public :
		save_command(Book *book) : book(book){};
        virtual void excute() {
			ofstream fout;
			fout.open("test.txt");
			vector<string> str = *book->getWords();
			for(int i=0; i<str.size();i++) {
				fout << str[i];
				fout << " ";
			}
            cout << "Save Success!" << endl;
        };
};

class textEdit {
    int i = 0;
    public :
        Command *edit[7];
        void setCommand(Command* command) {
            this->edit[i] = command;
            i++;
        }
        void commandInput(int k) {
            edit[k]->excute();
        }
};

void getAllWord(ifstream& file, vector<string> *pages) {
	while(!file.eof()) {
		string str;
		getline(file, str, ' ');
		pages->push_back(str);

	}cout << "finish" << endl;
	//단어를 전부 받은뒤 75자 20줄이 되도록 출력
	//그후 삽입은 vector의 index접근으로 단어 삽입
	//다음페이지 이전페이지 단어수 글자수로 조작
}

vector<string> inputSelect(char *in) {
	char input;
	string commend;
	string a;
	vector<string> cmd;
	cout << a << endl;
	while(1) {
		cin >> commend;
		input = commend.at(0);
		if (input == 'n' || input == 'p' || input == 't')
			break;
		if (commend.length() <= 1 || commend.at(1) != '(' || commend.at(commend.length() - 1) != ')') {
			cout << "Doesn't fit the format! Try again!" << endl;
			continue;
		}
		if(commend.length()>=2) commend.erase(0,2);
		commend.erase(commend.length() - 1);
		istringstream ss(commend);
		while(getline(ss,a,',')) {
			cmd.push_back(a);
		}
		break;
	}
	*in = input;
	return cmd;
}

int main() {
    static	string	buf;
	char			input = 'n';
    int				count = 0;
	string			commend;

    ifstream file("test.txt");
    if(!file.fail()) {
		Book *book = new Book();
        textEdit *edit = new textEdit();
        edit->setCommand(new next_command(book));
        edit->setCommand(new before_command(book));
        edit->setCommand(new insert_command(book));
        edit->setCommand(new delete_command(book));
        edit->setCommand(new change_command(book));
        edit->setCommand(new search_command(book));
        edit->setCommand(new save_command(book));
		getAllWord(file, book->getWords());
        while(input != 'e') {
            if(input == 'n') edit->commandInput(0);
            else if(input == 'p') edit->commandInput(1);
            else if(input == 'i') edit->commandInput(2);
            else if(input == 'd') edit->commandInput(3);
            else if(input == 'c') edit->commandInput(4);
            else if(input == 's') edit->commandInput(5);
            else if(input == 't')  {
				edit->commandInput(6);
				break;
			}
			else cout << "Doesn't fit the format! Try again!" << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			book->cmd = inputSelect(&input);
        }
    }

}