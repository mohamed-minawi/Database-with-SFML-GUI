#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include "hashTable.h"
#include "binaryTree.h"
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

#define windowheight 600
#define windowwidth 600

struct Data
{
	string Position;
	int Room;
	string Mobile, OfficePhone;
};
struct datasegment
{
	string password;
	bool flag;
	Data data;
	//Other information: corresponding types
};

enum loginbool { successfulladministrator = 2, successfulluser, wrongpass, wrongusername, junk2 };
enum adminstate { insertuser = 6, deleteuser, updateuser, viewlist, viewuser, savefile, junk };
Texture logo;
Sprite logosprite;
RectangleShape inputbox[3], box, administratoroptions[6], adminbox, insertupdate[7], logout, enter,back;
string usernamestring, passwordstring , *auth, insertupdatestrings[7], *insup;
Text inputboxtext[3], success, title, username, password, adminboxtexts[6], *authtext, insertupdatetext[7], *insuptext, backtext, logouttext, entertext, save;
Font font;
bool passbool, userbool, finished, loggedin, authentication, primary, chosen;
vector<string>kt;
vector<datasegment>dt;

void loader();
bool hover(RectangleShape, const RenderWindow &);
bool filetotable(hashTable<string, datasegment>&);			// function to transfer all usernames , passwords, and flags from file to hashtable
int amount();
loginbool checker(hashTable<string, datasegment> &);
void enlarge(RectangleShape &, Text & );
void shrink(RectangleShape &, Text &);
void userinfo(int, BinaryTree< string, datasegment>& );
void inserttext();
void updateusertext();
bool finished2();

bool filetobst(BinaryTree< string, datasegment>&);
void inserttobst(BinaryTree<string, datasegment>&);
void viewuserbst(BinaryTree<string, datasegment>&);
void savebst(BinaryTree<string, datasegment>&);


void main()
{
	Clock clock;
	float time;
	RenderWindow window(VideoMode(windowwidth, windowheight), "Directory");
	loader();

	hashTable<string, datasegment> directory(amount());
	BinaryTree<string, datasegment> bst;

	filetotable(directory);
	filetobst(bst);
	loginbool temp=junk2;
	adminstate state=junk;
	auth = &usernamestring;
	authtext=&username;
	int authenpos = 0;
	int uppos=0;
	int vectorpos = 0;
	Clock clock2;
	while (window.isOpen())
	{	
		Event event;
		// Events 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (authentication)
			{
				if (inputbox[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					passbool = false;
					userbool = true;
					finished = false;
				}
				else if (inputbox[1].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					userbool = false;
					passbool = true;
					finished = false;

				}
				else if (inputbox[2].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					userbool = false;
					passbool = false;
					finished = true;
					clock.restart();
				}
				else
				{
					userbool = false;
					passbool = false;
					finished = false;
				}
			}
			else if(logout.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
			{
				userbool = false;
				passbool = false;
				finished = false;
				authentication = true;
				primary = false;
				loggedin = false;
				state = junk;
				temp = junk2;
				usernamestring = "";
				passwordstring = "";
			}
			if (loggedin && temp == successfulladministrator &&!primary)
			{
				backtext.setString("Back");
				if (administratoroptions[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = insertuser;
					inserttext();
					primary = true;
				}
				else if (administratoroptions[1].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = deleteuser;
					updateusertext();
					primary = true;
				}
				else if (administratoroptions[2].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = updateuser;
					updateusertext();
					primary = true;
				}
				else if (administratoroptions[3].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = viewuser;
					updateusertext();
					primary = true;
				}
				else if (administratoroptions[4].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = viewlist;
					
				}
				else if (administratoroptions[5].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					state = savefile;
					primary = true;
				}
				
			}
			if (loggedin && temp == successfulladministrator && state == insertuser)
			{
				if (insertupdate[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[0], insuptext = &insertupdatetext[0], uppos = 0;
					primary = true;
				}
				else if (insertupdate[1].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[1], insuptext = &insertupdatetext[1], uppos = 1;
					primary = true;
				}
				else if (insertupdate[2].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[2], insuptext = &insertupdatetext[2], uppos = 2;
					primary = true;
				}
				else if (insertupdate[3].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[3], insuptext = &insertupdatetext[3], uppos = 3;
					primary = true;
				}
				else if (insertupdate[4].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[4], insuptext = &insertupdatetext[4], uppos = 4;
					primary = true;
				}
				else if (insertupdate[5].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[5], insuptext = &insertupdatetext[5], uppos = 5;
					primary = true;
				}
				else if (insertupdate[6].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[6], insuptext = &insertupdatetext[6], uppos = 6;
					primary = true;
				}
				else if (enter.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && finished2())
				{
					inserttobst(bst);
					savebst(bst);
					primary = false;
					state = junk;
					for (int i = 0;i < 7;i++)
						insertupdatestrings[i] = "";

				}
				else if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					primary = false;
					state = junk;
					insup = NULL;
					insuptext = NULL;
				}
				
				

			}
			if (loggedin && temp == successfulladministrator && state == updateuser)
			{
				if (insertupdate[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) &&!chosen)
				{
					insup = &insertupdatestrings[0], insuptext = &insertupdatetext[0], uppos = 0;
					primary = true;
				}
				if (insertupdate[1].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[1], insuptext = &insertupdatetext[1], uppos = 1;
					primary = true;
				}
				else if (insertupdate[2].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[2], insuptext = &insertupdatetext[2], uppos = 2;
					primary = true;
				}
				else if (insertupdate[3].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[3], insuptext = &insertupdatetext[3], uppos = 3;
					primary = true;
				}
				else if (insertupdate[4].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[4], insuptext = &insertupdatetext[4], uppos = 4;
					primary = true;
				}
				else if (insertupdate[5].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[5], insuptext = &insertupdatetext[5], uppos = 5;
					primary = true;
				}
				else if (insertupdate[6].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[6], insuptext = &insertupdatetext[6], uppos = 6;
					primary = true;
				}
				else if (enter.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && finished2())
				{
					inserttobst(bst);
					savebst(bst);
					primary = false;
					chosen = false;
					state = junk;
					for (int i = 0;i < 7;i++)
						insertupdatestrings[i] = "";
					insup = NULL;
					insuptext = NULL;

				}
				else if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					primary = false;
					state = junk;
					chosen = false;
					insup = NULL;
					insuptext = NULL;
				}
				if (chosen && insup == &insertupdatestrings[0])
				{
					insup = NULL;
					insuptext = NULL;
				}

			}
			if (loggedin && temp == successfulladministrator && state == deleteuser)
			{
				if (insertupdate[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					insup = &insertupdatestrings[0], insuptext = &insertupdatetext[0], uppos = 0;
					primary = true;
				}
				else if (enter.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					bst.remove(insertupdatestrings[0]);
					savebst(bst);
					primary = false;
					state = junk;
					for (int i = 0;i < 7;i++)
						insertupdatestrings[i] = "";

				}
				else if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					primary = false;
					state = junk;
					insup = NULL;
					insuptext = NULL;
				}

				if (insertupdatestrings[0] == "")
					insertupdatetext[0].setString("Enter Username");
			}
			if (loggedin && temp == successfulladministrator && state == savefile)
			{
				savebst(bst);
				clock2.restart();
				primary = true;
			}
			if (loggedin && temp == successfulladministrator && state == viewuser)
			{
				if (insertupdate[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && !chosen)
				{
					insup = &insertupdatestrings[0], insuptext = &insertupdatetext[0], uppos = 0;
					primary = true;
				}
				else if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					primary = false;
					state = junk;
					chosen = false;
					insup = NULL;
					insuptext = NULL;
				}
				if (chosen && insup == &insertupdatestrings[0])
				{
					insup = NULL;
					insuptext = NULL;
				}

				if (insertupdatestrings[0] == "")
					insertupdatetext[0].setString("Enter Username");
			}
			if (loggedin && temp == successfulladministrator && state == viewlist)
			{
				if(!primary)
				bst.traverse(kt, dt);
				primary = true;
				userinfo(vectorpos, bst);
				 if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					primary = false;
					state = junk;
					vectorpos = 0;
					insup = NULL;
					insuptext = NULL;
					kt.clear();
					dt.clear();
				}
			}
			
			if (loggedin&&temp == successfulluser)
			{	
				
				if (insertupdate[0].getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) )
				{
					insup = &insertupdatestrings[0], insuptext = &insertupdatetext[0], uppos = 0;
					
				}
				else if (back.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
				{
					updateusertext();
					chosen = false;
				}
				if (chosen&&insup == &insertupdatestrings[0])
				{
					insup = NULL;
					insuptext = NULL;
				}


			}
		}
		
		if (userbool)
			auth = &usernamestring, authtext = &username, authenpos = 0;
		else if(passbool)
			auth = &passwordstring, authtext = &password, authenpos = 1;

	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					window.close();
				if (event.key.code == Keyboard::Tab && !chosen &&(state==updateuser|| state == viewuser||temp==successfulluser))
				{
					viewuserbst(bst);
					chosen = true;
				}
				if (state == viewlist)
				{
					if (event.key.code == Keyboard::Left && vectorpos > 0)
					{
						vectorpos -= 1;
						userinfo(vectorpos, bst);
					}
					if (event.key.code == Keyboard::Right && vectorpos < kt.size()-1)
					{
						vectorpos += 1;
						userinfo(vectorpos, bst);
					}
				}
			}
			
			
			if (event.type == Event::TextEntered)
			{
				if (authentication)
				{
				
						if (event.text.unicode == 8 && auth->size() != 0)
						{
							auth->erase(auth->size() - 1);
							authtext->setString(*auth);
						}
						else if (event.text.unicode < 128 && event.text.unicode > 32)
						{
							*auth += static_cast<char> (event.text.unicode);
							authtext->setString(*auth);
							inputboxtext[authenpos].setString("");
						}
						else if (auth->size() == 0)
						{
							inputboxtext[authenpos].setString("Enter Username");
							authtext->setString("");
						}
					}
				if(loggedin)
				if (temp == successfulladministrator && (state == insertuser || state == updateuser|| state == deleteuser|| state == viewlist))
				{
					if (event.text.unicode == 8 && insup->size() != 0 &&insup!=NULL)
					{
						insup->erase(insup->size() - 1);
						insuptext->setString(*insup);
					}
					else if (event.text.unicode < 128 && event.text.unicode > 32 && insup != NULL)
					{
						*insup += static_cast<char> (event.text.unicode);
						insuptext->setString(*insup);
						insertupdatetext[uppos].setString(*insup);
					}
					else if (insup != NULL && insup->size()==0)
					{
					insuptext->setString("");
					}
				}
				else if (temp == successfulladministrator && !chosen&&(state == viewuser))
				{
					if (event.text.unicode == 8 && insup->size() != 0 && insup!=NULL)
					{
						insup->erase(insup->size() - 1);
						insuptext->setString(*insup);
					}
					else if (event.text.unicode < 128 && event.text.unicode > 32&&insup != NULL)
					{
						*insup += static_cast<char> (event.text.unicode);
						insuptext->setString(*insup);
						insertupdatetext[uppos].setString(*insup);
					}
					else if (insup != NULL&&insup->size() == 0)
					{
						insuptext->setString("");
					}
				}
				else
					if (temp == successfulluser)
					{
						if (event.text.unicode == 8 && insup->size() != 0 && !chosen&&insup!=NULL)
						{
							insup->erase(insup->size() - 1);
							insuptext->setString(*insup);
						}
						else if (event.text.unicode < 128 && event.text.unicode > 32 && !chosen&&insup != NULL)
						{
							*insup += static_cast<char> (event.text.unicode);
							insuptext->setString(*insup);
							insertupdatetext[uppos].setString(*insup);
						}
						else if (insup!=NULL && chosen && insup->size() == 0)
						{
							insuptext->setString("");
						}
					}
		
			}

		}
	
		// Validation
		if (authentication)
		{
			if (hover(inputbox[2], window))
			{
				enlarge(inputbox[2], inputboxtext[2]);
			}
			else
			{
				shrink(inputbox[2], inputboxtext[2]);
			}

			if (finished && usernamestring.size() != 0 && passwordstring.size() != 0)
			{
				temp = checker(directory);
				if(temp==successfulluser)
					backtext.setString("Refresh");
				if ((temp == successfulluser || temp == successfulladministrator))
				{
					success.setString("Successfull, loading");
					if (clock.getElapsedTime().asSeconds() > .5)
					{
						authentication = false;
						loggedin = true;
					}
				}
				else if (temp == wrongpass)
				{
					success.setString("Wrong Password");
				}
				else if (temp == wrongusername)
				{
					success.setString("Wrong Username");
				}

			}
			else success.setString("");
		}
		if (loggedin && temp == successfulladministrator)
		{
			for (int i = 0; i < 6; i++)
				if (hover(administratoroptions[i], window))
				{
					enlarge(administratoroptions[i], adminboxtexts[i]);
				}
				else
				{
					shrink(administratoroptions[i], adminboxtexts[i]);
				}
		}
		
		if (state == updateuser ||state==insertuser)
		{
			if (insertupdatestrings[0] == "")
				insertupdatetext[0].setString("Enter Username");
			if (insertupdatestrings[1] == "")
				insertupdatetext[1].setString("Enter Password");
			if (insertupdatestrings[2] == "")
				insertupdatetext[2].setString("Enter Administrator(1) or User(0)");
			if (insertupdatestrings[3] == "")
				insertupdatetext[3].setString("Enter Position");
			if (insertupdatestrings[4] == "")
				insertupdatetext[4].setString("Enter Room Number");
			if (insertupdatestrings[5] == "")
				insertupdatetext[5].setString("Enter Mobile Phone");
			if (insertupdatestrings[6] == "")
				insertupdatetext[6].setString("Enter Office Phone");
		}
		else if (state == deleteuser || state == viewuser)
		{
			if (insertupdatestrings[0] == "")
				insertupdatetext[0].setString("Enter Username");

		}

		// Drawing
		window.clear(Color::White);
		window.draw(logosprite);
		window.draw(title);
		if(!authentication)
		
		if (loggedin && temp == successfulladministrator && !primary)
		{
			title.setString("Choose one of the administrative actions: ");
			title.setCharacterSize(20);
			window.draw(adminbox);
			for (int i = 0; i < 6; i++)
				window.draw(administratoroptions[i]);
			for (int i = 0; i < 6; i++)
				window.draw(adminboxtexts[i]);
		}
		if (loggedin && temp == successfulladministrator && primary&&state == savefile)
		{
			title.setString("SUCCESSFUL SAVE");
			title.setCharacterSize(30);

			if (clock2.getElapsedTime().asSeconds()>2)
			{
				primary = false;
				state = junk;
			}
		}
		if (loggedin && temp == successfulladministrator && (state == updateuser || state == insertuser|| state == viewuser|| state == viewlist))
		{
			window.draw(adminbox);
			if (state != viewlist && state != viewuser)
				window.draw(enter), window.draw(entertext);
			else if (state == viewlist)
				title.setString("Press right or left to navigate directory");
			else if (state == viewuser)
				title.setString("Enter username then press tab(keyboard) to view");
			if(state==insertuser)
				title.setString("");

			if (state == updateuser)
				title.setString("Enter username to view\nPress tab to view current information\nPress enter on screen to update info"), title.setCharacterSize(12);
			else title.setCharacterSize(20);
			window.draw(back);
			window.draw(backtext);
			for (int i = 0;i < 7;i++)
				window.draw(insertupdate[i]);
			for (int i = 0;i < 7;i++)
				window.draw(insertupdatetext[i]);
		}
		if (loggedin && temp == successfulladministrator && state == deleteuser)
		{
			title.setString("Enter username then press enter on screen to delete");
			window.draw(adminbox);
			window.draw(enter);
			window.draw(entertext);
			window.draw(back);
			window.draw(backtext);
			window.draw(insertupdate[0]);
			window.draw(insertupdatetext[0]);
		}

		if (loggedin && temp == successfulluser)
		{
			window.draw(adminbox);
			window.draw(back);
			window.draw(backtext);
			title.setString("Enter username and press tab to view the information");
			for (int i = 0;i < 7;i++)
				window.draw(insertupdate[i]);
			for (int i = 0;i < 7;i++)
				window.draw(insertupdatetext[i]);
		}

		if (authentication)
		{
			title.setString("Please enter login credentials");
			window.draw(title);
			window.draw(box);

			for (int i = 0; i < 3; i++)
				window.draw(inputbox[i]);

			for (int i = 0; i < 3; i++)
				window.draw(inputboxtext[i]);

			if (usernamestring != "")
				window.draw(username), inputboxtext[0].setString("");
			else inputboxtext[0].setString("Enter Username");

			if (passwordstring != "")
				window.draw(password), inputboxtext[1].setString("");
			else inputboxtext[1].setString("Enter Password");

			window.draw(success);
		}
		else
		{
			window.draw(logout);
			window.draw(logouttext);
		}
		window.display();
	}

} 

void loader()
{
	if (!logo.loadFromFile("drawing.png"))
		cout << "Logo not loaded" << endl;

	if (!font.loadFromFile("sansation.ttf"))
		cout << "Font not loaded" << endl;

	usernamestring= "";
	passwordstring = "";

	logosprite.setTexture(logo);
	logosprite.setPosition(windowwidth / 6, 50);
	logosprite.setScale(0.5, 0.5);

	box.setSize(Vector2f(windowwidth / 1.5, windowheight / 2.5));
	box.setPosition(logosprite.getPosition().x, logosprite.getPosition().y + windowheight / 4);
	box.setFillColor(Color(128, 128, 128));

	inputbox[0].setSize(Vector2f(box.getSize().x / 1.1, box.getSize().y / 7));
	inputbox[0].setPosition(box.getPosition().x + 20, box.getPosition().y + 40);
	inputbox[0].setFillColor(Color::White);

	inputbox[1].setSize(Vector2f(inputbox[0].getSize().x, inputbox[0].getSize().y));
	inputbox[1].setPosition(inputbox[0].getPosition().x, inputbox[0].getPosition().y + 34.29 + 40);
	inputbox[1].setFillColor(Color::White);

	inputbox[2].setSize(Vector2f(inputbox[1].getSize().x / 3.5, inputbox[1].getSize().y));
	inputbox[2].setPosition(inputbox[1].getPosition().x + inputbox[1].getSize().x - inputbox[1].getSize().x / 3.5, inputbox[1].getPosition().y + 60);
	inputbox[2].setFillColor(Color::White);

	title.setFont(font);
	title.setCharacterSize(20);
	title.setPosition(logosprite.getPosition().x, logosprite.getPosition().y + logosprite.getGlobalBounds().height + 30);
	title.setString("Please enter login credentials");
	title.setColor(Color::Red);

	inputboxtext[0].setFont(font);
	inputboxtext[0].setCharacterSize(20);
	inputboxtext[0].setPosition(inputbox[0].getPosition().x + 110, inputbox[0].getPosition().y + 4);
	inputboxtext[0].setString("Enter Username");
	inputboxtext[0].setColor(Color(128, 128, 128));

	username.setFont(font);
	username.setCharacterSize(20);
	username.setPosition(inputbox[0].getPosition().x + 5, inputbox[0].getPosition().y + 4);
	username.setString(usernamestring);
	username.setColor(Color::Black);

	inputboxtext[1].setFont(font);
	inputboxtext[1].setCharacterSize(20);
	inputboxtext[1].setPosition(inputbox[1].getPosition().x + 110, inputbox[1].getPosition().y + 4);
	inputboxtext[1].setString("Enter Password");
	inputboxtext[1].setColor(Color(128, 128, 128));

	password.setFont(font);
	password.setCharacterSize(20);
	password.setPosition(inputbox[1].getPosition().x + 5, inputbox[1].getPosition().y + 4);
	password.setString(passwordstring);
	password.setColor(Color::Black);

	success.setFont(font);
	success.setCharacterSize(25);
	success.setPosition(inputbox[1].getPosition().x, inputbox[1].getPosition().y + inputbox[1].getSize().y + 20);
	success.setString("");
	success.setColor(Color::Black);

	inputboxtext[2].setFont(font);
	inputboxtext[2].setCharacterSize(22);
	inputboxtext[2].setPosition(inputbox[2].getPosition().x + 20, inputbox[2].getPosition().y + 4);
	inputboxtext[2].setString("Login");
	inputboxtext[2].setColor(Color::Black);

	adminbox.setSize(Vector2f(windowwidth / 1.5, windowheight / 1.6));
	adminbox.setPosition(logosprite.getPosition().x, logosprite.getPosition().y + windowheight / 4);
	adminbox.setFillColor(Color(128, 128, 128));

	administratoroptions[0].setSize(Vector2f(box.getSize().x / 1.1, box.getSize().y / 7));
	administratoroptions[0].setPosition(inputbox[0].getPosition().x, inputbox[0].getPosition().y - 20);
	administratoroptions[0].setFillColor(Color::White);

	administratoroptions[1].setSize(Vector2f(inputbox[0].getSize().x, inputbox[0].getSize().y));
	administratoroptions[1].setPosition(administratoroptions[0].getPosition().x, administratoroptions[0].getPosition().y + 60);
	administratoroptions[1].setFillColor(Color::White);

	administratoroptions[2].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	administratoroptions[2].setPosition(administratoroptions[1].getPosition().x, administratoroptions[1].getPosition().y + 60);
	administratoroptions[2].setFillColor(Color::White);

	administratoroptions[3].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	administratoroptions[3].setPosition(administratoroptions[2].getPosition().x, administratoroptions[2].getPosition().y + 60);
	administratoroptions[3].setFillColor(Color::White);

	administratoroptions[4].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	administratoroptions[4].setPosition(administratoroptions[3].getPosition().x, administratoroptions[3].getPosition().y + 60);
	administratoroptions[4].setFillColor(Color::White);

	administratoroptions[5].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	administratoroptions[5].setPosition(administratoroptions[1].getPosition().x, administratoroptions[4].getPosition().y + 60);
	administratoroptions[5].setFillColor(Color::White);

	adminboxtexts[0].setFont(font);
	adminboxtexts[0].setCharacterSize(20);
	adminboxtexts[0].setPosition(administratoroptions[0].getPosition().x + 135, administratoroptions[0].getPosition().y + 4);
	adminboxtexts[0].setString("Add User");
	adminboxtexts[0].setColor(Color::Black);

	adminboxtexts[1].setFont(font);
	adminboxtexts[1].setCharacterSize(20);
	adminboxtexts[1].setPosition(administratoroptions[1].getPosition().x + 130, administratoroptions[1].getPosition().y + 4);
	adminboxtexts[1].setString("Delete User");
	adminboxtexts[1].setColor(Color::Black);

	adminboxtexts[2].setFont(font);
	adminboxtexts[2].setCharacterSize(20);
	adminboxtexts[2].setPosition(administratoroptions[2].getPosition().x + 95, administratoroptions[2].getPosition().y + 4);
	adminboxtexts[2].setString("Update User Data");
	adminboxtexts[2].setColor(Color::Black);

	adminboxtexts[3].setFont(font);
	adminboxtexts[3].setCharacterSize(20);
	adminboxtexts[3].setPosition(administratoroptions[3].getPosition().x + 95, administratoroptions[3].getPosition().y + 4);
	adminboxtexts[3].setString("View User Information");
	adminboxtexts[3].setColor(Color::Black);

	adminboxtexts[4].setFont(font);
	adminboxtexts[4].setCharacterSize(20);
	adminboxtexts[4].setPosition(administratoroptions[4].getPosition().x + 95, administratoroptions[4].getPosition().y + 4);
	adminboxtexts[4].setString("View Entire Directory");
	adminboxtexts[4].setColor(Color::Black);

	adminboxtexts[5].setFont(font);
	adminboxtexts[5].setCharacterSize(20);
	adminboxtexts[5].setPosition(administratoroptions[5].getPosition().x + 95, administratoroptions[5].getPosition().y + 4);
	adminboxtexts[5].setString("Save Directory to file");
	adminboxtexts[5].setColor(Color::Black);

	insertupdate[0].setSize(Vector2f(box.getSize().x / 1.1, box.getSize().y / 7));
	insertupdate[0].setPosition(administratoroptions[0].getPosition().x, administratoroptions[0].getPosition().y);
	insertupdate[0].setFillColor(Color::White);

	insertupdate[1].setSize(Vector2f(inputbox[0].getSize().x, inputbox[0].getSize().y));
	insertupdate[1].setPosition(insertupdate[0].getPosition().x, insertupdate[0].getPosition().y + 50);
	insertupdate[1].setFillColor(Color::White);

	insertupdate[2].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	insertupdate[2].setPosition(insertupdate[1].getPosition().x, insertupdate[1].getPosition().y + 50);
	insertupdate[2].setFillColor(Color::White);

	insertupdate[3].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	insertupdate[3].setPosition(insertupdate[2].getPosition().x, insertupdate[2].getPosition().y + 50);
	insertupdate[3].setFillColor(Color::White);

	insertupdate[4].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	insertupdate[4].setPosition(insertupdate[3].getPosition().x, insertupdate[3].getPosition().y + 50);
	insertupdate[4].setFillColor(Color::White);

	insertupdate[5].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	insertupdate[5].setPosition(insertupdate[4].getPosition().x, insertupdate[4].getPosition().y + 50);
	insertupdate[5].setFillColor(Color::White);

	insertupdate[6].setSize(Vector2f(inputbox[1].getSize().x, inputbox[1].getSize().y));
	insertupdate[6].setPosition(insertupdate[5].getPosition().x, insertupdate[5].getPosition().y + 50);
	insertupdate[6].setFillColor(Color::White);

	insertupdatetext[0].setFont(font);
	insertupdatetext[0].setCharacterSize(20);
	insertupdatetext[0].setPosition(insertupdate[0].getPosition().x + 5, insertupdate[0].getPosition().y + 4);
	insertupdatetext[0].setString("Username");
	insertupdatetext[0].setColor(Color::Black);

	insertupdatetext[1].setFont(font);
	insertupdatetext[1].setCharacterSize(20);
	insertupdatetext[1].setPosition(insertupdate[1].getPosition().x + 5, insertupdate[1].getPosition().y + 4);
	insertupdatetext[1].setString("");
	insertupdatetext[1].setColor(Color::Black);

	insertupdatetext[2].setFont(font);
	insertupdatetext[2].setCharacterSize(20);
	insertupdatetext[2].setPosition(insertupdate[2].getPosition().x + 5, insertupdate[2].getPosition().y + 4);
	insertupdatetext[2].setString("");
	insertupdatetext[2].setColor(Color::Black);

	insertupdatetext[3].setFont(font);
	insertupdatetext[3].setCharacterSize(20);
	insertupdatetext[3].setPosition(insertupdate[3].getPosition().x + 5, insertupdate[3].getPosition().y + 4);
	insertupdatetext[3].setString("");
	insertupdatetext[3].setColor(Color::Black);

	insertupdatetext[4].setFont(font);
	insertupdatetext[4].setCharacterSize(20);
	insertupdatetext[4].setPosition(insertupdate[4].getPosition().x + 5, insertupdate[4].getPosition().y + 4);
	insertupdatetext[4].setString("");
	insertupdatetext[4].setColor(Color::Black);

	insertupdatetext[5].setFont(font);
	insertupdatetext[5].setCharacterSize(20);
	insertupdatetext[5].setPosition(insertupdate[5].getPosition().x + 5, insertupdate[5].getPosition().y + 4);
	insertupdatetext[5].setString("");
	insertupdatetext[5].setColor(Color::Black);

	insertupdatetext[6].setFont(font);
	insertupdatetext[6].setCharacterSize(20);
	insertupdatetext[6].setPosition(insertupdate[6].getPosition().x + 5, insertupdate[6].getPosition().y + 4);
	insertupdatetext[6].setString("");
	insertupdatetext[6].setColor(Color::Black);

	enter.setSize(Vector2f(inputbox[2].getSize().x-30, inputbox[2].getSize().y));
	enter.setPosition(adminbox.getPosition().x+ adminbox.getSize().x+20, adminbox.getPosition().y+ adminbox.getSize().y-enter.getSize().y);
	enter.setFillColor(Color(128, 128, 128));

	entertext.setFont(font);
	entertext.setCharacterSize(20);
	entertext.setPosition(enter.getPosition().x + 5, enter.getPosition().y + 4);
	entertext.setString("Enter");
	entertext.setColor(Color::White);

	logout.setSize(enter.getSize());
	logout.setPosition( enter.getPosition().x, adminbox.getPosition().y );
	logout.setFillColor(Color(128, 128, 128));

	logouttext.setFont(font);
	logouttext.setCharacterSize(20);
	logouttext.setPosition(logout.getPosition().x + 5, logout.getPosition().y + 4);
	logouttext.setString("Logout");
	logouttext.setColor(Color::White);
	
	back.setSize(enter.getSize());
	back.setPosition(adminbox.getPosition().x-20-back.getSize().x, adminbox.getPosition().y);
	back.setFillColor(Color(128, 128, 128));

	backtext.setFont(font);
	backtext.setCharacterSize(20);
	backtext.setPosition(back.getPosition().x + 5, back.getPosition().y + 4);
	backtext.setString("Back");
	backtext.setColor(Color::White);
	
	for (int i = 0;i < 7;i++)
		insertupdatestrings[i] = "";

	passbool = false;
	userbool = false;
	finished = false;
	loggedin = false;
	authentication = true;
	primary = false;
	chosen = false;
}
bool hover(RectangleShape a, const RenderWindow & b)
{
	if (a.getGlobalBounds().contains(Mouse::getPosition(b).x, Mouse::getPosition(b).y))
		return true;
	else return false;
}
bool filetotable(hashTable< string, datasegment>& directory)
{
	ifstream copy("directory.txt");			// opening the file
	string name, password;
	bool flag;
	string Position;
	int Room;
	string Mobile;
	string OfficePhone;
	datasegment x;
	int y;
	int counter = 0;

	if (copy.fail())
	{
		cerr << "Error";
		system("pause");
		return 0;
	}
	else
	{
		copy >> y;
		while (!copy.eof())
		{
			if (copy >> name)
				counter++;
			if (copy >> password)
				counter++;
			x.password = password;							// file input of information into temp data segment
			if (copy >> flag)
				counter++;
			x.flag = flag;

			if (copy >> Position)
				counter++;
			x.data.Position = Position;

			if (copy >> Room)
				counter++;
			x.data.Room = Room;

			if (copy >> Mobile)
				counter++;
			x.data.Mobile = Mobile;

			if (copy >> OfficePhone)
				counter++;
			x.data.OfficePhone = OfficePhone;


			if (!directory.insert(name, x))										// inserting the information into hashtable
				cout << "Error!! Cannot insert the name into directory\n";

		}
	}
	copy.close();

	if (counter%y == 0)						// validating that the information provided is equal to the number of elements
		return true;
	else return false;
}
int amount()
{
	ifstream copy("directory.txt");
	int y;
	copy >> y;						//returning the number of elements of the directory
	return y;
}
loginbool checker(hashTable<string, datasegment> & m)
{
	datasegment temp;
	if (m.retrieveData(usernamestring, temp))			// searching for username and retrieving the datasegment in the temp if located
	{
		if (temp.password == passwordstring)				// validating the password
			if (temp.flag)
				return successfulladministrator;
			else return successfulluser;
		else return wrongpass;
	}
	else return wrongusername;
}
void enlarge(RectangleShape & boxt, Text & textt)
{
	boxt.setScale(1, 1.05);
	textt.setCharacterSize(25);
}
void shrink(RectangleShape & boxt, Text & textt)
{
	boxt.setScale(0.9523, 0.909);
	textt.setCharacterSize(20);
}
void userinfo(int pos, BinaryTree< string, datasegment>& bst)
{

	datasegment d;
	if (bst.search(kt[pos]))
	{

		insertupdatestrings[0] = kt[pos];
		insertupdatestrings[1] = dt[pos].password;
		if (dt[pos].flag)
			insertupdatestrings[2] = "1";
		else insertupdatestrings[2] = "0";
		insertupdatestrings[3] = dt[pos].data.Position;
		insertupdatestrings[4] = to_string(dt[pos].data.Room);
		insertupdatestrings[5] = dt[pos].data.Mobile;
		insertupdatestrings[6] = dt[pos].data.OfficePhone;

		insertupdatetext[0].setString(insertupdatestrings[0]);
		insertupdatetext[1].setString(insertupdatestrings[1]);
		insertupdatetext[2].setString(insertupdatestrings[2]);
		insertupdatetext[3].setString(insertupdatestrings[3]);
		insertupdatetext[4].setString(insertupdatestrings[4]);
		insertupdatetext[5].setString(insertupdatestrings[5]);
		insertupdatetext[6].setString(insertupdatestrings[6]);

	}
	else
		insertupdatetext[0].setString("Invalid User");



}
void inserttext()
{
	for (int i = 0; i < 7;i++)
		insertupdatestrings[i] = "";

	
	insertupdatetext[0].setString("Enter Username");
	insertupdatetext[1].setString("Enter Password");
	insertupdatetext[2].setString("Enter Administrator(1) or User(0)");
	insertupdatetext[3].setString("Enter Position");
	insertupdatetext[4].setString("Enter Room Number");
	insertupdatetext[5].setString("Enter Mobile Phone");
	insertupdatetext[6].setString("Enter Office Phone");

}
void updateusertext()
{
	for (int i = 0; i < 7;i++)
		insertupdatestrings[i] = "";

	insertupdatetext[0].setString("Enter Username");
	insertupdatetext[1].setString("");
	insertupdatetext[2].setString("");
	insertupdatetext[3].setString("");
	insertupdatetext[4].setString("");
	insertupdatetext[5].setString("");
	insertupdatetext[6].setString("");

}
bool finished2()
{
	for (int i = 0;i < 7;i++)
		if (insertupdatestrings[i] == "")
			return false;

	return true;
}

bool filetobst(BinaryTree< string, datasegment>& bst)
{

	ifstream copy("directory.txt");			// opening the file
	string name, password;
	bool flag;
	string Position;
	int Room;
	string Mobile;
	string OfficePhone;
	datasegment x;
	int y;
	int counter = 0;

	if (copy.fail())
	{
		cerr << "Error";
		system("pause");
		return 0;
	}
	else
	{
		copy >> y;
		while (!copy.eof())
		{
			if (copy >> name)
				counter++;
			if (copy >> password)
				counter++;
			x.password = password;							// file input of information into temp data segment
			if (copy >> flag)
				counter++;
			x.flag = flag;

			if (copy >> Position)
				counter++;
			x.data.Position = Position;

			if (copy >> Room)
				counter++;
			x.data.Room = Room;

			if (copy >> Mobile)
				counter++;
			x.data.Mobile = Mobile;

			if (copy >> OfficePhone)
				counter++;
			x.data.OfficePhone = OfficePhone;


			if (!bst.insert(name, x))										// inserting the information into hashtable
				cout << "Error!! Cannot insert the name into directory\n";

		}
	}
	copy.close();

	if (counter%y == 0)						// validating that the information provided is equal to the number of elements
		return true;
	else return false;

}
void inserttobst(BinaryTree<string, datasegment>& bst)
{
	string k;
	datasegment d;

	k = insertupdatestrings[0];
	d.password = insertupdatestrings[1];
	d.flag= stoi(insertupdatestrings[2]);
	d.data.Mobile = insertupdatestrings[5];
	d.data.Position = insertupdatestrings[3];
	d.data.Room = stoi(insertupdatestrings[4]);
	d.data.OfficePhone = insertupdatestrings[6];
	
	bst.remove(k);
	bst.insert(k, d);
	
}
void viewuserbst(BinaryTree<string, datasegment>& bst)
{

	datasegment d;
	if (bst.search(insertupdatestrings[0]))
	{
		
		bst.retrieve(insertupdatestrings[0], d);

		insertupdatestrings[1] = d.password;
		if(d.flag)
		insertupdatestrings[2] = "1";
		else insertupdatestrings[2] = "0";
		insertupdatestrings[3] = d.data.Position;
		insertupdatestrings[4] = to_string(d.data.Room);
		insertupdatestrings[5] = d.data.Mobile;
		insertupdatestrings[6] = d.data.OfficePhone;


		insertupdatetext[1].setString(insertupdatestrings[1]);
		insertupdatetext[2].setString(insertupdatestrings[2]);
		insertupdatetext[3].setString(insertupdatestrings[3]);
		insertupdatetext[4].setString(insertupdatestrings[4]);
		insertupdatetext[5].setString(insertupdatestrings[5]);
		insertupdatetext[6].setString(insertupdatestrings[6]);

	}
	else
		insertupdatetext[0].setString("Invalid User");


}
void savebst(BinaryTree<string, datasegment>& bst)
{
	ofstream copy("directory.txt");			// opening the file

	vector<string> k;
	vector<datasegment> d;

	bst.levelorder(k, d);

	if (copy.fail())
	{
		cerr << "Error";
		EXIT_FAILURE;
	}
	else
	{
		copy << bst.TotalNodes();
		int i = 0;
		copy << endl;

		while (i < bst.TotalNodes())
		{
			copy << k[i];
			copy << " ";
			copy << d[i].password;
			copy << " ";						// file input of information into temp data segment
			copy << d[i].flag;
			copy << " ";
			copy << d[i].data.Position;
			copy << " ";
			copy << d[i].data.Room;
			copy << " ";
			copy << d[i].data.Mobile;
			copy << " ";
			copy << d[i].data.OfficePhone;
			if (++i < bst.TotalNodes())
				copy << endl;
		}

	}
	//copy << endl << "DONE";
	copy.close();
}

