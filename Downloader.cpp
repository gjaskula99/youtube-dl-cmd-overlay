#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

enum video_type{null, MP3, MP4, PLAYLIST};

class element
{
	private:
	string url;
	video_type type;
	
	public:
	element() {url = ""; type=null;}
	element(video_type type_, string url_) : url(url_), type(type_) {};
	~element() {};
	
	friend class video_list;
};

class video_list
{
	private:
	vector<element> list;
	
	public:
	video_list() {};
	~video_list() {};
	
	vector<element> get_list() {return list;}
	void add(video_type type, string url) {list.push_back( element(type, url) );}
	void remove(int index) {list.erase( list.begin() + index);}
	void clear() {list.clear();}
	void show();
	void download();
};

void video_list::show()
{
	if(list.empty())
	{
		cout << "No elements\n";
		return;
	}
	for(int i = 0; i < list.size(); i++)
	{
		cout << i << ". " << list[i].url << " ";
		if(list[i].type == MP4) cout << "MP4\n";
		else if(list[i].type == MP3) cout << "MP3\n";
		else if(list[i].type == PLAYLIST) cout << "PLAYLIST\n";
	}
}

void video_list::download()
{
	if(list.empty())
	{
		cout << "Nothing to download\n";
		return;
	}
	for(int i = 0; i < list.size(); i++)
	{
		if(list[i].type == MP4)
		{
			string cmd = "youtube-dl -f mp4 ";
			cmd += list[i].url;
			char cmd_c[cmd.size() + 1];
    		strcpy(cmd_c, cmd.c_str());
			system(cmd_c);
		}
		else if(list[i].type == MP3)
		{
			string cmd = "youtube-dl --extract-audio --audio-format mp3 ";
			cmd += list[i].url;
			char cmd_c[cmd.size() + 1];
    		strcpy(cmd_c, cmd.c_str());
			system(cmd_c);
		}
		else if(list[i].type == PLAYLIST)
		{
			string cmd = "youtube-dl -i -f mp4 --yes-playlist ";
			cmd += list[i].url;
			char cmd_c[cmd.size() + 1];
    		strcpy(cmd_c, cmd.c_str());
			system(cmd_c);
		}
	}
}

int main()
{
	int choice = 0;
	bool running = true;
	video_list my_list;
	while(running)
	{
		cout << "1. Add MP4\n2. Add MP3\n3. Add Playlist\n4. Remove element\n5. Print list\n6. Start download\n7. Read list from file\n8. Force update\n0. Exit\n\nYour choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1 :
				{
					string url = "";
					cout << "Enter URL: ";
					cin >> url;
					my_list.add(MP4, url);
				}
				break;
			case 2 :
				{
					string url = "";
					cout << "Enter URL: ";
					cin >> url;
					my_list.add(MP3, url);
				}
				break;
			case 3 :
				{
					string url = "";
					cout << "Enter URL: ";
					cin >> url;
					my_list.add(PLAYLIST, url);
				}
				break;
			case 4 :
				{
					if(my_list.get_list().empty()) break;
					else
					{
						int index = -1;
						my_list.show();
						cout << "Enter index (subzero to cancel): ";
						cin >> index;
						while( !cin.good() )
						{
							cin.clear();
							cin.ignore();
							cout << "Invalid input - enter number: ";
							cin >> index;
						}
						if(index < 0 || index > my_list.get_list().size()) break;
						else my_list.remove(index);
					}
				}
				break;
			case 5 :
				{
					my_list.show();
				}
				break;
			case 6 :
				{
					if(my_list.get_list().empty()) break;
					cout << "Starting download...\n";
					my_list.download();
					cout << "\nAccomplished. Clearing list...\n";
					my_list.clear();
					system("mkdir MP4");
					system("mkdir MP3");
					system("move *.mp4 MP4");
					system("move *.mp3 MP3");
					system("start .");
				}
				break;
			case 7 :
				{
					string name = "";
					cout << "Enter filename (file must be .txt): ";
					cin >> name;
					fstream source;
					name += ".txt";
					source.open(name, ios::in);
					if( !source.is_open() )
					{
						cout << "Error opening file\nInput terminated\n";
						break;
					}
					else
					{
						while( !source.eof() )
						{
							string url = "", type = "";
							video_type type_ = null;
							source >> url;
							source >> type;
							if(type == "MP3" || type == "mp3" || type == "Mp3" || type == "Mp3") type_ = MP3;
							else if(type == "Playlist" || type == "PLAYLIST" || type == "playlist") type_ = PLAYLIST;
							else type_ = MP4;
							my_list.add(type_, url);
							cout << "Added " << type << " " << url << " to download list\n";
						}
						cout << "Closing file...";
						source.close();
						cout << " File closed\n";
					}
				}
				break;
			case 8 :
				{
					string cmd = "youtube-dl --update";
					char cmd_c[cmd.size() + 1];
		    		strcpy(cmd_c, cmd.c_str());
					system(cmd_c);
				}
				break;
			case 0 :
				{
					running = false;
				}
				break;
			default:
				{
					cout << "Invalid option\n";
				}
				break;
		}
		system("pause");
		system("cls");
	}
	cout << "Exiting...";
	return 0;
}
